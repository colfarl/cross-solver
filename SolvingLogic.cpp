#include <string_view>
#include <unordered_map>

#include "SolvingLogic.h"
#include "Cube.h"
#include "CrossConstants.hpp"
#include "CrossTable.generated.hpp"

SolvingLogic::SolvingLogic(Cube& c) : cube(c) {}

bool SolvingLogic::isSolved() const{
    for(Face f : {Face::BACK, Face::UP, Face::DOWN, Face::RIGHT, Face::LEFT, Face::FRONT}){
	std::unordered_map<char, bool> seen;
	for(int j = 0; j < 3; j++){
	    for(int k = 0; k < 3; ++k){
		seen[cube.getColorAtPosition(f, j, k)] = true;
		if(seen.size() >= 2) {
		    return false;
		}
	    }
	}
    }
    return true;
}

/*
 * This one is a bit weird but we are generalizing from this post on reddit
 * https://www.reddit.com/r/Cubers/comments/ur1ylk/the_complete_solutions_of_every_single_cross/
 * instead of green red blue orange we do front right back left 
 * the numbered positions stay in their same relative spot
 */

std::array<int, 4> SolvingLogic::getCrossLocations() { 
    int n = cross::EDGE_POSITIONS.size();   
    char cross_color = cube.getColorAtPosition(Face::DOWN, 1, 1); //center
    std::array<int, 4> res;

    for(int i = 0; i < n; i++){

	Face f = std::get<0>(cross::EDGE_POSITIONS[i]);	
	int r = std::get<1>(cross::EDGE_POSITIONS[i]);	
	int c = std::get<2>(cross::EDGE_POSITIONS[i]);	
	char edge_color = cube.getColorAtPosition(f, r, c);

	if(edge_color != cross_color) continue;	

	std::tuple<Face, int, int> other = (i % 2 == 0) ? cross::EDGE_POSITIONS[i + 1] : cross::EDGE_POSITIONS[i - 1];
	f = std::get<0>(other);	
	r = std::get<1>(other);	
	c = std::get<2>(other);	
	char other_color = cube.getColorAtPosition(f, r, c);
	
	char front_color = cube.getColorAtPosition(Face::FRONT, 1, 1);
	char right_color = cube.getColorAtPosition(Face::RIGHT, 1, 1);
	char back_color = cube.getColorAtPosition(Face::BACK, 1, 1);
	char left_color = cube.getColorAtPosition(Face::LEFT, 1, 1);
	
	//changed to front left back right because 
	if(other_color == front_color) res[0] = i;
	if(other_color == right_color) res[1] = i;
	if(other_color == back_color) res[2] = i;
	if(other_color == left_color) res[3] = i;
    }
    
    return res;
}

std::size_t SolvingLogic::crossIndex_(uint8_t F, uint8_t L, uint8_t B, uint8_t R) noexcept {
  return F + cross_table::kBase * (L + cross_table::kBase * (B + cross_table::kBase * R));
}

std::string_view SolvingLogic::lookupFLBR_(uint8_t F, uint8_t L, uint8_t B, uint8_t R) noexcept {
  auto idx = crossIndex_(F, L, B, R);
  int entry = cross_table::kIndex[idx];
  if (entry < 0) return {}; // no moves needed or missing
  const auto &e = cross_table::kEntries[static_cast<std::size_t>(entry)];
  return std::string_view{cross_table::kMovesBlob + e.str_offset, e.str_len};
}

std::string SolvingLogic::getCrossSolutions(const std::array<int, 4>& pos) {
    std::string_view sv = lookupFLBR_(static_cast<uint8_t>(pos[0]), static_cast<uint8_t>(pos[1]), static_cast<uint8_t>(pos[2]), static_cast<uint8_t>(pos[3]));
    std::string str(sv);
    return str;
}

