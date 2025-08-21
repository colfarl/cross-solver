#ifndef SOLVING_LOGIC_H
#define SOLVING_LOGIC_H

#include "Cube.h"

class SolvingLogic {
private:
    Cube& cube;
public:
    
    //Constructor
   SolvingLogic(Cube& c);

   bool isSolved() const;
   std::vector<int> getCrossLocations();
};

#endif
