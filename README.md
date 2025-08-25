# Cross Solver (Color-Neutral) 🧩

A fast, terminal-based **Rubik’s Cube cross solver** written in C++.  
Given a scramble, it evaluates **all 24 cube orientations** (six cross colors × four possible front faces each) and prints an **optimal cross** solution for every orientation using a precomputed lookup table. It’s handy for CFOP beginners and for training color-neutral inspection.

> **Scope:** This finds **optimal crosses only**. It does **not** try to build an X-cross, preserve pairs, or optimize for specific finger-trick ergonomics beyond trying all orientations.

## Inspiration

I built this to practice **CFOP cross inspection** and help with **color-neutrality**. During inspection it’s easy to miss a faster cross or a more ergonomic orientation. This tool shows the **optimal cross** for **every orientation** so you can compare move counts and see “what you missed,” then transfer those patterns into your own inspection.

## Recommended Usage

1. **Generate a scramble** from your favorite timer (csTimer, etc.).  
   Paste it into the program (Singmaster notation; spaces optional).

2. **Scan the 24 outputs**:
   - Read the orientation label (e.g., *White Cross, Red in front*).
   - Consider both **move count** and **ergonomics**: try the ones that feel best in your hands, not just the absolute shortest.
   - Look at the **“After Cross Solution”** cube net to spot potential **free pairs** or friendly F2L starts.

3. **Training ideas**:
   - **Single-color focus**: only read lines for your cross color to compare fronts.
   - **Color-neutral practice**: pick the best across all colors; repeat until your mental inspection finds the same (or nearly the same) plan.
   - **Time-boxed drills**: give yourself 15s to pick the best orientation, then check what the tool suggests.

4. **Notes**:
   - If a cross is already solved for a given orientation, the move string may be **empty** (0 moves).
   - Inputs ignore any characters outside `R L U D F B ' 2`, so feel free to add spaces.
---

## Features

- **Color-neutral:** checks White, Yellow, Red, Orange, Blue, and Green crosses.
- **All orientations:** 24 (Down × Front) combinations.
- **Optimal solutions:** pulled from a compiled lookup table (`include/CrossTable.generated.hpp`).
- **Readable output:** orientation label, move string, move count, and unfolded cube after applying the solution.
---

## Build

### Requirements

- A C++17 compiler (`g++` or `clang++`) (I use g++)
- `make`

### Build Commands

```bash
# Clone repository
git clone https://github.com/<your-username>/cross-solver.git
cd cross-solver

# Release build (optimized) -> ./cross-solver
make

# Debug build with sanitizers
make debug

# Clean build artifacts
make clean

# Run
./cross-solver

```
## How It Works (High-Level)

- **`Cube`**  
  Holds the 6×3×3 state, supports orientation changes and pretty-printing.

- **`CubeManipulator`**  
  Applies face moves (`R/R'/R2`, `U/U'/U2`, `F/F'/F2`, `L/L'/L2`, `B/B'/B2`, `D/D'/D2`).

- **`SolvingLogic`**  
  - Detects the **current positions** of the four down-face edges (relative to the current orientation).
  - Packs those into a **base-24 index** representing Front/Left/Back/Right edge locations.
  - Looks up the **optimal cross** from a **constexpr table** (`include/CrossTable.generated.hpp`).

- **Orientation Sweep**  
  Tries all `(Down, Front)` pairs (24 total), so you can compare every cross color and orientation choice.
---

## Notation

- **Singmaster**
  - Faces: `R L U D F B`
  - Modifiers: `'` (counterclockwise), `2` (double)
- No wide/slice moves (`Rw`, `M`, etc.) in inputs or outputs.
- Unrecognized characters are ignored; you may include spaces.
---
## Tips

- **Color-neutral practice:** scan the 24 outputs, choose your favorite orientation/move set.
- **Single-color focus:** read only the lines with your cross color (e.g., “White Cross, … in front”).
- The post-solution cube net can help you eyeball **free pairs** or **nice F2L starts**, even though the solver doesn’t optimize for those.
- My personal workflow is copy and paste a scramble from whatever scramble generator I am using, and then examine to see if my cross solution matches the programs
- For a given color, cross solutions will be very similar the orientations are provided for the user to focus on finger-trickability 
---

### Limitations / Future Ideas

#### Not included:
- X-cross
- F2L setup or preservation
- Detailed ergonomics (beyond trying all orientations)

#### Potential extensions:
- Rank by different turn metrics or user grip preferences
- Filter to a subset of cross colors or fronts
- Show top N solutions only

## Acknowledgement
- cross solutions derived from https://www.reddit.com/r/Cubers/comments/ur1ylk/the_complete_solutions_of_every_single_cross/
- 
