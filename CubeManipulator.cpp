#include "CubeManipulator.h"
#include "Cube.h"
#include <array>

CubeManipulator::CubeManipulator(Cube& c) : cube(c) {}


void CubeManipulator::r_norm(){
    //chars on right side shift    

    auto up = cube.getCol(Face::UP, 2);
    auto back = cube.getCol(Face::BACK, 0, true);
    auto front = cube.getCol(Face::FRONT, 2);
    auto down = cube.getCol(Face::DOWN, 2);
    
    cube.setCol(Face::UP, 2, front);
    cube.setCol(Face::BACK, 0, up, true);
    cube.setCol(Face::DOWN, 2, back);
    cube.setCol(Face::FRONT, 2, down);

    cube.rotate_face_clockwise(Face::RIGHT);
}

void CubeManipulator::r_prime(){
    //chars on right side shift    
    auto up = cube.getCol(Face::UP, 2);
    auto back = cube.getCol(Face::BACK, 0, true);
    auto front = cube.getCol(Face::FRONT, 2);
    auto down = cube.getCol(Face::DOWN, 2);
    
    cube.setCol(Face::UP, 2, back);
    cube.setCol(Face::BACK, 0, down, true);
    cube.setCol(Face::DOWN, 2, front);
    cube.setCol(Face::FRONT, 2, up);

    cube.rotate_face_counter_clockwise(Face::RIGHT);
}

void CubeManipulator::r_two(){

    auto up = cube.getCol(Face::UP, 2);
    auto back = cube.getCol(Face::BACK, 0, true);
    auto front = cube.getCol(Face::FRONT, 2);
    auto down = cube.getCol(Face::DOWN, 2);
    
    cube.setCol(Face::UP, 2, down);
    cube.setCol(Face::BACK, 0, front, true);
    cube.setCol(Face::DOWN, 2, up);
    cube.setCol(Face::FRONT, 2, back);

    cube.rotate_face_180(Face::RIGHT);
}


void CubeManipulator::l_norm(){

    auto up = cube.getCol(Face::UP, 0);
    auto back = cube.getCol(Face::BACK, 2, true);
    auto front = cube.getCol(Face::FRONT, 0);
    auto down = cube.getCol(Face::DOWN, 0);
    
    cube.setCol(Face::UP, 0, back);
    cube.setCol(Face::BACK, 2, down, true);
    cube.setCol(Face::DOWN, 0, front);
    cube.setCol(Face::FRONT, 0, up);
    
    cube.rotate_face_clockwise(Face::LEFT);
}

void CubeManipulator::l_prime(){

    auto up = cube.getCol(Face::UP, 0);
    auto back = cube.getCol(Face::BACK, 2, true);
    auto front = cube.getCol(Face::FRONT, 0);
    auto down = cube.getCol(Face::DOWN, 0);
    
    cube.setCol(Face::UP, 0, front);
    cube.setCol(Face::BACK, 2, up, true);
    cube.setCol(Face::DOWN, 0, back);
    cube.setCol(Face::FRONT, 0, down);

    cube.rotate_face_counter_clockwise(Face::LEFT);
}

void CubeManipulator::l_two(){

    auto up = cube.getCol(Face::UP, 0);
    auto back = cube.getCol(Face::BACK, 2, true);
    auto front = cube.getCol(Face::FRONT, 0);
    auto down = cube.getCol(Face::DOWN, 0);
    
    cube.setCol(Face::UP, 0, down);
    cube.setCol(Face::BACK, 2, front, true);
    cube.setCol(Face::DOWN, 0, up);
    cube.setCol(Face::FRONT, 0, back);

    cube.rotate_face_180(Face::LEFT);
};
   

void CubeManipulator::u_norm(){

    auto right = cube.getRow(Face::RIGHT, 0);
    auto back = cube.getRow(Face::BACK, 0);
    auto front = cube.getRow(Face::FRONT, 0);
    auto left = cube.getRow(Face::LEFT, 0);
    
    cube.setRow(Face::FRONT, 0, right);
    cube.setRow(Face::BACK, 0, left);
    cube.setRow(Face::LEFT, 0, front);
    cube.setRow(Face::RIGHT, 0, back);
    
    cube.rotate_face_clockwise(Face::UP);
}

void CubeManipulator::u_prime(){

    auto right = cube.getRow(Face::RIGHT, 0);
    auto back = cube.getRow(Face::BACK, 0);
    auto front = cube.getRow(Face::FRONT, 0);
    auto left = cube.getRow(Face::LEFT, 0);

    cube.setRow(Face::FRONT, 0, left);
    cube.setRow(Face::BACK, 0, right);
    cube.setRow(Face::LEFT, 0, back);
    cube.setRow(Face::RIGHT, 0, front);
     
    cube.rotate_face_counter_clockwise(Face::UP);
}


void CubeManipulator::u_two(){

    auto right = cube.getRow(Face::RIGHT, 0);
    auto back = cube.getRow(Face::BACK, 0);
    auto front = cube.getRow(Face::FRONT, 0);
    auto left = cube.getRow(Face::LEFT, 0);

    cube.setRow(Face::FRONT, 0, back);
    cube.setRow(Face::BACK, 0, front);
    cube.setRow(Face::LEFT, 0, right);
    cube.setRow(Face::RIGHT, 0, left);
     
    cube.rotate_face_180(Face::UP);
};

void CubeManipulator::d_prime(){

    auto right = cube.getRow(Face::RIGHT, 2);
    auto back = cube.getRow(Face::BACK, 2);
    auto front = cube.getRow(Face::FRONT, 2);
    auto left = cube.getRow(Face::LEFT, 2);
    
    cube.setRow(Face::FRONT, 2, right);
    cube.setRow(Face::BACK, 2, left);
    cube.setRow(Face::LEFT, 2, front);
    cube.setRow(Face::RIGHT, 2, back);
    
    cube.rotate_face_counter_clockwise(Face::DOWN);
}

void CubeManipulator::d_norm(){

    auto right = cube.getRow(Face::RIGHT, 2);
    auto back = cube.getRow(Face::BACK, 2);
    auto front = cube.getRow(Face::FRONT, 2);
    auto left = cube.getRow(Face::LEFT, 2);

    cube.setRow(Face::FRONT, 2, left);
    cube.setRow(Face::BACK, 2, right);
    cube.setRow(Face::LEFT, 2, back);
    cube.setRow(Face::RIGHT, 2, front);
     
    cube.rotate_face_clockwise(Face::DOWN);
}


void CubeManipulator::d_two(){

    auto right = cube.getRow(Face::RIGHT, 2);
    auto back = cube.getRow(Face::BACK, 2);
    auto front = cube.getRow(Face::FRONT, 2);
    auto left = cube.getRow(Face::LEFT, 2);

    cube.setRow(Face::FRONT, 2, back);
    cube.setRow(Face::BACK, 2, front);
    cube.setRow(Face::LEFT, 2, right);
    cube.setRow(Face::RIGHT, 2, left);
     
    cube.rotate_face_180(Face::DOWN);
};
   
void CubeManipulator::f_norm() {

    auto right = cube.getCol(Face::RIGHT, 0);
    auto up = cube.getRow(Face::UP, 2);
    auto down = cube.getRow(Face::DOWN, 0);
    auto left = cube.getCol(Face::LEFT, 2);

    cube.setRow(Face::UP, 2, left, true);
    cube.setRow(Face::DOWN, 0, right, true);
    cube.setCol(Face::RIGHT, 0, up);
    cube.setCol(Face::LEFT, 2, down);
     
    cube.rotate_face_clockwise(Face::FRONT);
}

void CubeManipulator::f_prime(){

    auto right = cube.getCol(Face::RIGHT, 0);
    auto up = cube.getRow(Face::UP, 2);
    auto down = cube.getRow(Face::DOWN, 0);
    auto left = cube.getCol(Face::LEFT, 2);

    cube.setRow(Face::UP, 2, right);
    cube.setRow(Face::DOWN, 0, left);
    cube.setCol(Face::RIGHT, 0, down, true);
    cube.setCol(Face::LEFT, 2, up, true);
     
    cube.rotate_face_counter_clockwise(Face::FRONT);
}

void CubeManipulator::f_two(){
    
    auto right = cube.getCol(Face::RIGHT, 0);
    auto up = cube.getRow(Face::UP, 2);
    auto down = cube.getRow(Face::DOWN, 0);
    auto left = cube.getCol(Face::LEFT, 2);

    cube.setRow(Face::UP, 2, down, true);
    cube.setRow(Face::DOWN, 0, up, true);
    cube.setCol(Face::RIGHT, 0, left, true);
    cube.setCol(Face::LEFT, 2, right, true);
     
    cube.rotate_face_180(Face::FRONT);
}

void CubeManipulator::b_norm(){

    auto right = cube.getCol(Face::RIGHT, 2);
    auto up = cube.getRow(Face::UP, 0);
    auto down = cube.getRow(Face::DOWN, 2);
    auto left = cube.getCol(Face::LEFT, 0);

    cube.setRow(Face::UP, 0, right);
    cube.setRow(Face::DOWN, 2, left);
    cube.setCol(Face::RIGHT, 2, down, true);
    cube.setCol(Face::LEFT, 0, up, true);
    
    cube.rotate_face_clockwise(Face::BACK);
}

void CubeManipulator::b_prime(){
    
    auto right = cube.getCol(Face::RIGHT, 2);
    auto up = cube.getRow(Face::UP, 0);
    auto down = cube.getRow(Face::DOWN, 2);
    auto left = cube.getCol(Face::LEFT, 0);

    cube.setRow(Face::UP, 0, left, true);
    cube.setRow(Face::DOWN, 2, right, true);
    cube.setCol(Face::RIGHT, 2, up);
    cube.setCol(Face::LEFT, 0, down);
    
    cube.rotate_face_counter_clockwise(Face::BACK);
}

void CubeManipulator::b_two(){
    
    auto right = cube.getCol(Face::RIGHT, 2);
    auto up = cube.getRow(Face::UP, 0);
    auto down = cube.getRow(Face::DOWN, 2);
    auto left = cube.getCol(Face::LEFT, 0);

    cube.setRow(Face::UP, 0, down, true);
    cube.setRow(Face::DOWN, 2, up, true);
    cube.setCol(Face::RIGHT, 2, left, true);
    cube.setCol(Face::LEFT, 0, right, true);
    
    cube.rotate_face_180(Face::BACK);
}

void CubeManipulator::applyMove(const std::string& move){
    if (move == "R"){
	r_norm();
    } else if (move == "R'"){
	r_prime();
    } else if (move == "R2"){
	r_two();
    } else if (move == "L"){
	l_norm();
    } else if (move == "L'"){
	l_prime();
    } else if (move == "L2"){
	l_two();
    } else if (move == "U"){
	u_norm();
    } else if (move == "U'"){
	u_prime();
    } else if (move == "U2"){
	u_two();
    } else if (move == "D"){
	d_norm();
    } else if (move == "D'"){
	d_prime();
    } else if (move == "D2"){
	d_two();
    } else if (move == "F"){
	f_norm();
    } else if (move == "F'"){
	f_prime();
    } else if (move == "F2"){
	f_two();
    } else if (move == "B"){
	b_norm();
    } else if (move == "B'"){
	b_prime();
    } else if (move == "B2"){
	b_two();
    } else {
	std::cerr << "UNKNOWN MOVE: " << move << std::endl;
    }
}

void CubeManipulator::applyManyMoves(const std::vector<std::string>& moves){
    for(const std::string& move : moves){
	applyMove(move);
    }
}

