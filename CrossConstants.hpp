#pragma once
#include <array>
#include <tuple>
#include "Cube.h"  // for Face enum

namespace cross {

    /*
     * This one is a bit weird but we are generalizing from this post on reddit
     * https://www.reddit.com/r/Cubers/comments/ur1ylk/the_complete_solutions_of_every_single_cross/
     * instead of green red blue orange we do front right back left 
     * the numbered positions stay in their same relative spot
     * edge pair is one ahead on even numbers and one behind on odd number indices
     */
    constexpr std::array<std::tuple<Face, int, int>, 24> EDGE_POSITIONS{{
	{Face::UP,    2, 1},  // 0 = UF: UP sticker
	{Face::FRONT, 0, 1},  // 1 = UF: FRONT sticker
	{Face::UP,    1, 0},  // 2 = UL: UP sticker
	{Face::LEFT,  0, 1},  // 3 = UL: LEFT sticker
	{Face::UP,    0, 1},  // 4 = UB: UP sticker
	{Face::BACK,  0, 1},  // 5 = UB: BACK sticker
	{Face::UP,    1, 2},  // 6 = UR: UP sticker
	{Face::RIGHT, 0, 1},  // 7 = UR: RIGHT sticker
	{Face::FRONT, 1, 2},  // 8 = FR: FRONT sticker
	{Face::RIGHT, 1, 0},  // 9 = FR: RIGHT sticker
	{Face::FRONT, 1, 0},  // 10 = FL: FRONT sticker
	{Face::LEFT, 1, 2},  // 11 = FL: LEFT sticker
	{Face::BACK, 1, 2},  // 12 = BL: BACK sticker
	{Face::LEFT, 1, 0},  // 13 = BL: LEFT sticker
	{Face::BACK, 1, 0},  // 14 = BR: BACK sticker
	{Face::RIGHT, 1, 2},  // 15 = BR: RIGHT sticker
	{Face::DOWN, 0, 1},  // 16 = DF: DOWN sticker
	{Face::FRONT, 2, 1},  // 17 = DF: FRONT sticker
	{Face::DOWN, 1, 0},  // 18 = DL: DOWN sticker
	{Face::LEFT, 2, 1},  // 19 = DL: LEFT sticker
	{Face::DOWN, 2, 1},  // 20 = DB: DOWN sticker
	{Face::BACK, 2, 1},  // 21 = DB: BACK sticker
	{Face::DOWN, 1, 2},  // 22 = DR: DOWN sticker
	{Face::RIGHT, 2, 1},  // 23 = DR: RIGHT sticker	 
    }};

}
