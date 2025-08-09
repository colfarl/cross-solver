#include "SolvingLogic.h"
#include "Cube.h"
#include <unordered_map>

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

