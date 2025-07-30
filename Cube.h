#ifndef CUBE_H
#define CUBE_H

#include <iostream>

enum class Face {
    UP = 0,
    LEFT,
    FRONT,
    RIGHT,
    BACK,
    DOWN
};

class Cube {
private:
    //internal cube represenation
    std::array<std::array<std::array<char, 3>, 3>, 6> cube;

public:	
    //Constructor
    Cube();
    
    //Getters
    char getColorAtPosition(Face face, int row, int col) const; 
};

std::ostream& operator<<(std::ostream& out, const Cube& c);
#endif

