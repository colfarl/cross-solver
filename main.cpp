#include <iostream>
#include "Cube.h"

int main (int argc, char** argv){
    Cube c;
    std::cout << "Cube pre rotation" << std::endl;
    std::cout << c << std::endl; 
    std::cout << "Cube post cross orientation" << std::endl;
    c.orient(Face::UP, Face::FRONT);
    std::cout << c << std::endl;
    std::cout << "Rotate once x" << std::endl;
    c.rotate_x();
    std::cout << c << std::endl;
    std::cout << "Rotate once y" << std::endl;
    c.rotate_y();
    std::cout << c << std::endl;
    std::cout << "Rotate once z" << std::endl;
    c.rotate_z();
    std::cout << c << std::endl;
    return 0;
}
