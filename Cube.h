#ifndef CUBE_H
#define CUBE_H

#include <iostream>
#include <unordered_map>

enum class Face {
    UP = 0,
    LEFT,
    FRONT,
    RIGHT,
    BACK,
    DOWN
};

namespace std {
    template <>
    struct hash<Face> {
        std::size_t operator()(const Face& f) const noexcept {
            return static_cast<std::size_t>(f);
        }
    };
}

class Cube {
private:
    //internal cube represenation
    std::array<std::array<std::array<char, 3>, 3>, 6> cube;
    std::unordered_map<Face, Face> orientation;

public:	
    //Constructor
    Cube();
     
    //Getters
    char getColorAtPosition(Face face, int row, int col) const; 
    std::array<char,3> getCol(Face f, int col, bool reversed=false) const;
    std::array<char,3> getRow(Face f, int row, bool reversed=false) const;
  
    //Setter
    void setColorAtPosition(Face face, int row, int col, char color);
    void setCol(Face f, int col, const std::array<char,3>& vals, bool reversed=false);
    void setRow(Face f, int row, const std::array<char,3>& vals, bool reversed=false);

    //Adjust Orientation
    void orient(Face new_down, Face new_front);
    void rotate_x(); 							//Rotate the cube so that "front" becomes "up"
    void rotate_y(); 							//Rotate the cube so that "right" becomes "front"
    void rotate_z(); 							//Rotate the cube so that "up" becomes "right"
    void rotate_x_prime(); 						//Rotate the cube so that "up" becomes "front"
    void rotate_y_prime(); 						//Rotate the cube so that "front" becomes "right"
    void rotate_z_prime(); 						//Rotate the cube so that "right" becomes "up"
    void rotate_x_2(); 							//Rotate the cube so that "front" becomes "back"
    void rotate_y_2(); 							//Rotate the cube so that "right" becomes "left"
    void rotate_z_2(); 							//Rotate the cube so that "Up" becomes "down"
    void rotate_face_clockwise(Face face);
    void rotate_face_180(Face face);
    void rotate_face_counter_clockwise(Face face);
};

std::ostream& operator<<(std::ostream& out, const Cube& c);
#endif

