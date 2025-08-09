#ifndef CUBE_MANIPULATOR_H
#define CUBE_MANIPULATOR_H

#include "Cube.h"

class CubeManipulator {
private:
    Cube& cube;

public:
    
    //Constructor
    CubeManipulator(Cube& c);
    
    //Cube Manipulators
    void applyMove(const std::string& move); 
    void applyManyMoves(const std::vector<std::string>& moves);
    
    void r_norm();
    void r_prime();
    void r_two();
    
    void l_norm();
    void l_prime();
    void l_two();
    
    void u_norm();
    void u_prime();
    void u_two();
    
    void b_norm();
    void b_prime();
    void b_two();

    void f_norm();
    void f_prime();
    void f_two();

    void d_norm();
    void d_prime();
    void d_two();  

};
#endif
