#include "SolvingLogic.h"
#include "Cube.h"
#include <unordered_map>
#include "CrossConstants.hpp"

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

std::vector<int> SolvingLogic::getCrossLocations() { 
    int n = cross::EDGE_POSITIONS.size();   
    char cross_color = cube.getColorAtPosition(Face::DOWN, 1, 1); //center
    std::vector<int> res(4);

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

	if(other_color == front_color) res[0] = i;
	if(other_color == right_color) res[1] = i;
	if(other_color == back_color) res[2] = i;
	if(other_color == left_color) res[3] = i;
    }
    
    return res;
}
