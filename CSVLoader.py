#!/usr/bin/env python3
"""
Generate a constexpr C++ header for *direct-index* cross solutions (FLBR indexing).

Assumptions:
- Dataset is for WHITE on Down and GREEN on Front.
- CSV columns contain GRBO positions (1..24):
    "Green piece position", "Red piece position",
    "Blue piece position",  "Orange piece position"
  (We also accept FLBR-ish aliases in case your header names differ.)
- "Solution" column is a space-separated move string (e.g., "R2 L2 F2 B2").

Mapping & indexing:
- We pack to **FLBR order** using base-24 mixed radix:
    F = Green, L = Orange, B = Blue, R = Red
    (convert each from 1-based to 0-based by subtracting 1)
    idx = F + 24 * (L + 24 * (B + 24 * R))
- We emit:
    - inline constexpr std::array<int32_t, 24^4> kIndex   // -1 if no entry, else index in kEntries
    - inline constexpr std::array<Entry,N> kEntries       // offsets into kMovesBlob
    - inline constexpr char kMovesBlob[...]               // concatenated move strings (no NUL)
- We store moves **without spaces** (e.g., "R2L2F2B2") so you can feed them to your parser.

Dedup:
- If multiple rows map to the same idx, we keep the one with *fewer tokens*.

Delimiters:
- Autodetect among {',',';','\\t','|'} with Sniffer, then validate.
- Fallback to scanning first line; final fallback ','.
- You can force delimiter via --delimiter.

Usage:
  python CSVLoader.py data/crossSolutions.csv -o include/CrossTable.generated.hpp
  # If your CSV stores solved->scrambled sequences, invert them at build time:
  python CSVLoader.py data/crossSolutions.csv -o include/CrossTable.generated.hpp --invert
  # Force delimiter if needed:
  python CSVLoader.py data/crossSolutions.csv -o include/CrossTable.generated.hpp --delimiter ';'
"""

import argparse
import csv
import datetime
import os
import re
import sys
from typing import Dict, List, Tuple

# ----------------- Move token helpers -----------------

MOVE_RE = re.compile(r"^[URFDLB](2|'|)?$")

def tokenize_moves(s: str) -> List[str]:
    toks = [t for t in s.strip().split() if t]
    for t in toks:
        if not MOVE_RE.match(t):
            raise ValueError(f"Unknown/invalid move token: '{t}'")
    return toks

def invert_token(tok: str) -> str:
    if tok.endswith("2"):
        return tok
    if tok.endswith("'"):
        return tok[0]
    return tok + "'"

def invert_sequence(tokens: List[str]) -> List[str]:
    return [invert_token(t) for t in reversed(tokens)]

# ----------------- CSV header helpers -----------------

def norm(s: str) -> str:
    return re.sub(r"\s+", " ", s.strip().lower())

# Accept GRBO and FLBR-ish aliases
ALIASES = {
    "green":  ["green piece position", "green", "g_pos", "g", "front piece position", "front", "f_pos", "f"],
    "red":    ["red piece position",   "red",   "r_pos", "r", "right piece position", "right", "rgt", "rt"],
    "blue":   ["blue piece position",  "blue",  "b_pos", "b", "back piece position",  "back",  "bk"],
    "orange": ["orange piece position","orange","o_pos", "o", "left piece position",  "left",  "lft", "lt"],
    "solution": ["solution", "alg", "moves", "sequence", "sol"],
    "movecount": ["no. of moves", "move count", "length", "len", "moves"],
}

def find_col(header: List[str], names: List[str]) -> int:
    H = [norm(h) for h in header]
    candidates = [norm(n) for n in names]
    for i, h in enumerate(H):
        if h in candidates:
            return i
    return -1

# ----------------- Key packing (FLBR; base 24) -----------------

BASE = 24

def pack_index(F0: int, L0: int, B0: int, R0: int) -> int:
    for tag, v in zip(("F","L","B","R"), (F0, L0, B0, R0)):
        if not (0 <= v < BASE):
            raise ValueError(f"{tag} out of range [0,{BASE-1}]: {v}")
    return F0 + BASE * (L0 + BASE * (B0 + BASE * R0))

# ----------------- Header template -----------------

HEADER_TEMPLATE = """\
// ============================================================================
//  GENERATED FILE — DO NOT EDIT
//  Source: {src_path}
//  Generated: {timestamp}
//  Rows (unique): {rows}
//  Indexing: FLBR in base-24, idx = F + 24*(L + 24*(B + 24*R)), positions 0..23
//  Data direction: {direction}
//  Moves stored without spaces (e.g., 'R2L2F2B2').
// ============================================================================

#pragma once
#include <array>
#include <cstdint>

namespace cross_table {{

inline constexpr std::uint32_t kBase = 24;

struct Entry {{
  std::uint32_t str_offset;  // offset into kMovesBlob
  std::uint16_t str_len;     // length (no trailing NUL)
  std::uint16_t move_count;  // number of tokens
}};

// Concatenated move strings, NOT NUL-terminated; use str_len.
inline constexpr char kMovesBlob[{blob_size}] = {{
{blob_data}
}};

// Entries referenced by kIndex.
inline constexpr std::array<Entry, {rows}> kEntries = {{
{entries}
}};

// Direct-index table: size = 24^4 = 331,776
// -1 means no entry for that (F,L,B,R) combination.
// Otherwise value is an index into kEntries.
inline constexpr std::array<int32_t, {table_size}> kIndex = {{
{index_table}
}};

}} // namespace cross_table
"""

def c_char_literal(ch: str) -> str:
    if ch == '\\':
        return "'\\\\'"
    if ch == "'":
        return "'\\''"
    if ch == '"':
        return "'\"'"
    if ch == '\n':
        return "'\\n'"
    if ch == '\r':
        return "'\\r'"
    if ch == '\t':
        return "'\\t'"
    o = ord(ch)
    if 32 <= o <= 126:
        return f"'{ch}'"
    return f"0x{o:02x}"

# ----------------- Main -----------------

def main():
    ap = argparse.ArgumentParser(description="Generate constexpr FLBR cross table header")
    ap.add_argument("csv", help="Input CSV path")
    ap.add_argument("-o", "--output", required=True, help="Output header path")
    ap.add_argument("--invert", action="store_true",
                    help="Reverse+invert each move sequence (use if CSV stores solved->scrambled)")
    ap.add_argument("--delimiter",
                    help="Force CSV delimiter (e.g., ',', ';', '\\t', '|'). If omitted, auto-detect.")
    args = ap.parse_args()

    # Read CSV with robust delimiter selection
    try:
        with open(args.csv, "r", newline="", encoding="utf-8-sig") as f:
            sample = f.read(8192)
            f.seek(0)

            delimiter = args.delimiter
            if not delimiter:
                try:
                    sniffed = csv.Sniffer().sniff(sample, delimiters=",;\t|")
                    d = getattr(sniffed, "delimiter", None)
                    if not d or len(d) != 1:
                        raise csv.Error("sniffer produced invalid delimiter")
                    delimiter = d
                except csv.Error:
                    header_line = sample.splitlines()[0] if sample else ""
                    for cand in (",", ";", "\t", "|"):
                        if cand in header_line:
                            delimiter = cand
                            break
                    else:
                        delimiter = ","

            reader = csv.reader(f, delimiter=delimiter)
            rows = list(reader)
    except FileNotFoundError:
        print(f"ERROR: file not found: {args.csv}", file=sys.stderr)
        sys.exit(1)
    except ValueError as e:
        print(f"ERROR: bad delimiter value; try --delimiter ',' (details: {e})", file=sys.stderr)
        sys.exit(1)

    if not rows:
        print("ERROR: CSV is empty", file=sys.stderr)
        sys.exit(1)

    header = rows[0]
    data_rows = rows[1:]

    # Resolve columns
    g_col = find_col(header, ALIASES["green"])
    r_col = find_col(header, ALIASES["red"])
    b_col = find_col(header, ALIASES["blue"])
    o_col = find_col(header, ALIASES["orange"])
    sol_col = find_col(header, ALIASES["solution"])
    mv_col  = find_col(header, ALIASES["movecount"])  # optional

    missing = [(name, col) for name, col in (("Green", g_col), ("Red", r_col),
                                             ("Blue", b_col), ("Orange", o_col),
                                             ("Solution", sol_col)) if col < 0]
    if missing:
        for name, _ in missing:
            print(f"ERROR: Missing required column: {name}", file=sys.stderr)
        print("Header seen:\n  " + " | ".join(header), file=sys.stderr)
        sys.exit(1)

    # Parse & dedup: idx -> (joined_moves_without_spaces, token_count)
    parsed: Dict[int, Tuple[str, int]] = {}
    max_positions = 0

    for line_no, row in enumerate(data_rows, start=2):
        if not row or all(not c.strip() for c in row):
            continue

        try:
            G = int(row[g_col].strip())  # 1..24
            R = int(row[r_col].strip())  # 1..24
            B = int(row[b_col].strip())  # 1..24
            O = int(row[o_col].strip())  # 1..24
        except (IndexError, ValueError):
            print(f"WARNING: skipping row {line_no} (bad GRBO integers)", file=sys.stderr)
            continue

        # Convert to 0-based and map to FLBR: F=G, L=O, B=B, R=R
        F0 = G - 1
        L0 = O - 1
        B0 = B - 1
        R0 = R - 1

        if not (0 <= F0 < BASE and 0 <= L0 < BASE and 0 <= B0 < BASE and 0 <= R0 < BASE):
            print(f"WARNING: skipping row {line_no} (position out of 1..24)", file=sys.stderr)
            continue

        try:
            idx = pack_index(F0, L0, B0, R0)
        except ValueError as e:
            print(f"WARNING: skipping row {line_no} ({e})", file=sys.stderr)
            continue

        try:
            sol_raw = row[sol_col]
        except IndexError:
            print(f"WARNING: skipping row {line_no} (missing Solution)", file=sys.stderr)
            continue

        try:
            tokens = tokenize_moves(sol_raw)
        except ValueError as e:
            print(f"WARNING: skipping row {line_no} (bad token): {e}", file=sys.stderr)
            continue

        if args.invert:
            tokens = invert_sequence(tokens)

        joined = "".join(tokens)
        tok_count = len(tokens)

        if mv_col >= 0:
            try:
                csv_cnt = int(row[mv_col].strip())
                if csv_cnt != tok_count:
                    print(f"NOTE: row {line_no} move count mismatch: csv={csv_cnt} parsed={tok_count}",
                          file=sys.stderr)
            except Exception:
                pass

        prev = parsed.get(idx)
        if prev is None or tok_count < prev[1]:
            parsed[idx] = (joined, tok_count)

        max_positions = max(max_positions, G, R, B, O)

    if not parsed:
        print("ERROR: no valid rows parsed.", file=sys.stderr)
        sys.exit(1)

    # Deterministic order: sort by idx ascending
    items = sorted(parsed.items(), key=lambda kv: kv[0])

    # Build blobs and tables
    blob_chars: List[str] = []
    entries_cpp: List[str] = []
    offset = 0

    TABLE_SIZE = BASE ** 4  # 331,776
    index_table = [-1] * TABLE_SIZE

    for entry_index, (idx, (joined, tok_count)) in enumerate(items):
        index_table[idx] = entry_index

        # Append move string (no spaces) to blob
        length = len(joined)
        if length > 0:
            for ch in joined:
                blob_chars.append(c_char_literal(ch))

        entries_cpp.append(f"  {{ {offset}u, {length}u, {tok_count}u }}")
        offset += length

    # Format blob data into lines (16 chars per line)
    blob_lines = []
    line = []
    for i, lit in enumerate(blob_chars, start=1):
        line.append(lit)
        if i % 16 == 0:
            blob_lines.append("  " + ", ".join(line) + ",")
            line = []
    if line:
        blob_lines.append("  " + ", ".join(line) + ",")

    # Format index table in lines of 16 ints
    idx_lines = []
    line = []
    for i, v in enumerate(index_table, start=1):
        line.append(str(v))
        if i % 16 == 0:
            idx_lines.append("  " + ", ".join(line) + ",")
            line = []
    if line:
        idx_lines.append("  " + ", ".join(line) + ",")

    header_text = HEADER_TEMPLATE.format(
        src_path=os.path.abspath(args.csv),
        timestamp=datetime.datetime.now().isoformat(timespec="seconds"),
        rows=len(items),
        blob_size=max(1, offset),
        blob_data="\n".join(blob_lines) if blob_lines else "  /* empty */",
        entries=",\n".join(entries_cpp),
        table_size=TABLE_SIZE,
        index_table="\n".join(idx_lines),
        direction=("SCRAMBLED->CROSS" if not args.invert else "SOLVED->SCRAMBLED (INVERTED AT BUILD)"),
    )

    out_path = args.output
    os.makedirs(os.path.dirname(out_path), exist_ok=True)
    with open(out_path, "w", encoding="utf-8") as f:
        f.write(header_text)

    print(f"Generated {out_path}")
    print(f"  unique entries: {len(items)}")
    print(f"  blob size     : {offset} bytes")
    print(f"  table size    : {TABLE_SIZE} ints (~{TABLE_SIZE*4/1024:.1f} KiB)")
    print(f"  max CSV pos   : {max_positions} (should be <= 24)")
    print(f"  delimiter     : {repr(args.delimiter) if args.delimiter else 'auto'}")

if __name__ == "__main__":
    main()

