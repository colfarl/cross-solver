#include "Cube.h"
#include <array>

Cube::Cube() {
    // Define standard color order for each face
    const char face_colors[6] = {'W', 'O', 'G', 'R', 'B', 'Y'};
    for (int f = 0; f < 6; ++f) {
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                cube[f][i][j] = face_colors[f];
    }
    
    orientation[Face::UP] = Face::UP;
    orientation[Face::DOWN] = Face::DOWN;
    orientation[Face::LEFT] = Face::LEFT;
    orientation[Face::BACK] = Face::BACK;
    orientation[Face::FRONT] = Face::FRONT;
    orientation[Face::RIGHT] = Face::RIGHT;
}

char Cube::getColorAtPosition(Face face, int row, int col) const {
    int face_index = static_cast<int>(orientation.at(face));
    return this->cube[face_index][row][col];
}

std::array<char,3> Cube::getCol(Face f, int col, bool reversed) const {
    int face = static_cast<int>(orientation.at(f));
    if(reversed){
	return {cube[face][2][col], cube[face][1][col], cube[face][0][col]};
    }
    return {cube[face][0][col], cube[face][1][col], cube[face][2][col]};
}

std::array<char,3> Cube::getRow(Face f, int row, bool reversed) const{
    int face = static_cast<int>(orientation.at(f));
    std::array<char, 3> r = cube[face][row];
    if(reversed){
	std::reverse(r.begin(), r.end());
    }
    return r;
}


void Cube::setColorAtPosition(Face face, int row, int col, char color){
    if (color != 'W' && color != 'O' && color != 'G' && color != 'R' && color != 'B' && color != 'Y'){
	return;
    }
    cube[static_cast<int>(orientation[face])][row][col] = color; 
}


void Cube::setCol(Face f, int col, const std::array<char,3>& vals, bool reversed){
    int face = static_cast<int>(orientation.at(f));
    if(reversed){
	cube[face][0][col] = vals[2];
	cube[face][1][col] = vals[1];
	cube[face][2][col] = vals[0];
	return;
    }
    cube[face][0][col] = vals[0];
    cube[face][1][col] = vals[1];
    cube[face][2][col] = vals[2];
}

void Cube::setRow(Face f, int row, const std::array<char,3>& vals, bool reversed){
    int face = static_cast<int>(orientation.at(f));
    if(reversed){
	cube[face][row][0] = vals[2];
	cube[face][row][1] = vals[1];
	cube[face][row][2] = vals[0];
	return;
    }
    cube[face][row][0] = vals[0];
    cube[face][row][1] = vals[1];
    cube[face][row][2] = vals[2];
}

// =========================== Cube Orientation Helpers =================================
void Cube::rotate_x(){
    Face old_up = orientation[Face::UP];
    orientation[Face::UP] = orientation[Face::FRONT];
    Face old_back = orientation[Face::BACK];
    orientation[Face::BACK]= old_up;
    Face old_down = orientation[Face::DOWN];
    orientation[Face::DOWN] = old_back;
    orientation[Face::FRONT] = old_down;
    rotate_face_clockwise(Face::RIGHT);
    rotate_face_counter_clockwise(Face::LEFT);
    rotate_face_180(Face::BACK);
    rotate_face_180(Face::DOWN);
}

//This is peak idc
void Cube::rotate_x_prime(){
    rotate_x();
    rotate_x();
    rotate_x();
}

void Cube::rotate_x_2(){
    rotate_x();
    rotate_x();
}

void Cube::rotate_y(){
    Face old_front = orientation[Face::FRONT];
    orientation[Face::FRONT] = orientation[Face::RIGHT];
    Face old_left = orientation[Face::LEFT];
    orientation[Face::LEFT]= old_front;
    Face old_back = orientation[Face::BACK];
    orientation[Face::BACK] = old_left;
    orientation[Face::RIGHT] = old_back;
    rotate_face_clockwise(Face::UP);
    rotate_face_counter_clockwise(Face::DOWN);
};

//More PEAK 
void Cube::rotate_y_prime(){
    rotate_y(); 
    rotate_y(); 
    rotate_y(); 
}

void Cube::rotate_y_2(){
    rotate_y();
    rotate_y();
}

void Cube::rotate_z(){
    Face old_right = orientation[Face::RIGHT];
    orientation[Face::RIGHT] = orientation[Face::UP];
    Face old_down = orientation[Face::DOWN];
    orientation[Face::DOWN]= old_right;
    Face old_left = orientation[Face::LEFT];
    orientation[Face::LEFT] = old_down;
    orientation[Face::UP] = old_left;
    rotate_face_clockwise(Face::FRONT);
    rotate_face_counter_clockwise(Face::BACK);
    rotate_face_clockwise(Face::UP);
    rotate_face_clockwise(Face::DOWN);
    rotate_face_clockwise(Face::LEFT);
    rotate_face_clockwise(Face::RIGHT);
    
}

//yeah I did it three times 
void Cube::rotate_z_prime(){
    rotate_z();
    rotate_z();
    rotate_z();
}

void Cube::rotate_z_2(){
    rotate_z();
    rotate_z();
}

void Cube::rotate_face_clockwise(Face face) {   
    int f = static_cast<int>(orientation[face]);
    for(int i = 0; i < 3; i++){
	for(int j = i + 1; j < 3; j++){
	    std::swap(cube[f][i][j], cube[f][j][i]); 
	}
    }

    for(int i = 0; i < 3; i++){
	std::swap(cube[f][i][0], cube[f][i][2]);
    }
}

void Cube::rotate_face_180(Face face){
    int f = static_cast<int>(orientation.at(face));
    for(int i = 0; i < 3; i++){
	std::swap(cube[f][i][0], cube[f][i][2]);
    }
    for(int i = 0; i < 3; i++){
	std::swap(cube[f][2][i], cube[f][0][i]);
    }
}

void Cube::rotate_face_counter_clockwise(Face face) {   
    int f = static_cast<int>(orientation[face]);
    for(int i = 0; i < 3; i++){
	for(int j = i + 1; j < 3; j++){
	    std::swap(cube[f][i][j], cube[f][j][i]);
	}
    }
    for(int i = 0; i < 3; i++){
	std::swap(cube[f][2][i], cube[f][0][i]);
    }
}


void Cube::orient(Face new_down, Face new_front){

    if(new_down == orientation[Face::UP] && new_front == orientation[Face::FRONT]){	
	rotate_z_2();
    } else if (new_down == orientation[Face::UP] && new_front == orientation[Face::LEFT]){
	rotate_z_2();
	rotate_y();
    } else if (new_down == orientation[Face::UP] && new_front == orientation[Face::RIGHT]){
	rotate_z_2();
	rotate_y_prime();
    } else if (new_down == orientation[Face::UP] && new_front == orientation[Face::BACK]){
	rotate_x_2();
    } else if(new_down == orientation[Face::FRONT] && new_front == orientation[Face::UP]){	
	rotate_x_prime();
    } else if (new_down == orientation[Face::FRONT] && new_front == orientation[Face::RIGHT]){
	rotate_x_prime();
	rotate_y();
    } else if (new_down == orientation[Face::FRONT] && new_front == orientation[Face::LEFT]){
	rotate_x_prime();
	rotate_y_prime();
    } else if (new_down == orientation[Face::FRONT] && new_front == orientation[Face::DOWN]){
	rotate_x_prime();
	rotate_y_2();
    } else if (new_down == orientation[Face::DOWN] && new_front == orientation[Face::RIGHT]){	
	rotate_y();
    } else if (new_down == orientation[Face::DOWN] && new_front == orientation[Face::LEFT]){
	rotate_y_prime();
    } else if (new_down == orientation[Face::DOWN] && new_front == orientation[Face::BACK]){
	rotate_y_2();
    } else if (new_down == orientation[Face::LEFT] && new_front == orientation[Face::FRONT]){	
	rotate_z_prime();
    } else if (new_down == orientation[Face::LEFT] && new_front == orientation[Face::UP]){
	rotate_z_prime();
	rotate_y_prime();
    } else if (new_down == orientation[Face::LEFT] && new_front == orientation[Face::BACK]){
	rotate_z_prime();
	rotate_y_2();
    } else if (new_down == orientation[Face::LEFT] && new_front == orientation[Face::DOWN]){
	rotate_z_prime();
	rotate_y();
    } else if (new_down == orientation[Face::RIGHT] && new_front == orientation[Face::FRONT]){	
	rotate_z();
    } else if (new_down == orientation[Face::RIGHT] && new_front == orientation[Face::UP]){
	rotate_z();
	rotate_y();
    } else if (new_down == orientation[Face::RIGHT] && new_front == orientation[Face::BACK]){
	rotate_z();
	rotate_y_2();
    } else if (new_down == orientation[Face::RIGHT] && new_front == orientation[Face::DOWN]){
	rotate_z();
	rotate_y_prime();
    } else if(new_down == orientation[Face::BACK] && new_front == orientation[Face::UP]){	
	rotate_x_prime();
	rotate_z_2();
    } else if (new_down == orientation[Face::BACK] && new_front == orientation[Face::RIGHT]){
	rotate_x();
	rotate_y();
    } else if (new_down == orientation[Face::BACK] && new_front == orientation[Face::LEFT]){
	rotate_x();
	rotate_y_prime();
    } else if (new_down == orientation[Face::BACK] && new_front == orientation[Face::DOWN]){
	rotate_x();
    } else if (new_down == orientation[Face::DOWN] && new_front == orientation[Face::FRONT]){
	; // do nothing current orientation
    } else {
	std::cerr << "this orientation does not exist or was missed in implementation" << std::endl;
    }
}

// =========================== ========================= =================================

/* Global/Friend Functions*/
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
