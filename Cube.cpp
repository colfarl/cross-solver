#include "Cube.h"

Cube::Cube() {
    // Define standard color order for each face
    const char face_colors[6] = {'W', 'O', 'G', 'R', 'B', 'Y'};
    for (int f = 0; f < 6; ++f) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                cube[f][i][j] = face_colors[f];
    }
}

char Cube::getColorAtPosition(Face face, int row, int col) const {
    return this->cube[static_cast<int>(face)][row][col];
}

std::ostream& operator<<(std::ostream& out, const Cube& c){

    //print topside
    out << "         " << "_______" << std::endl;
    for(int i = 0; i < 3; i++){
	out << "         ";
	for(int j = 0; j < 3; j++){
	    out << "|" << c.getColorAtPosition(Face::UP, i, j);
	}
	out << "|" << std::endl;
    }

    //print middle strip
    out << "----------------------------------" << std::endl;
    for(int i = 0; i < 3; i++){
	for(Face f : {Face::LEFT, Face::FRONT, Face::RIGHT, Face::BACK}){
	    for(int k = 0; k < 3; k++){
		out << "|" << c.getColorAtPosition(f, i, k);
	    }
	    if(f == Face::BACK){
		continue;
	    }
	    out << "|  ";
	}
	out << "|" << std::endl;
    }
    out << "----------------------------------" << std::endl;

    //print bottom side
    for(int i = 0; i < 3; i++){
	out << "         ";
	for(int j = 0; j < 3; j++){
	    out << "|" << c.getColorAtPosition(Face::DOWN, i, j);
	}
	out << "|" << std::endl;
    }
    out << "         " << "-------" << std::endl;

    return out;
}
