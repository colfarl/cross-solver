#ifndef SOLVING_LOGIC_H
#define SOLVING_LOGIC_H

#include "Cube.h"

class SolvingLogic {
private:
    Cube& cube;
    static std::size_t crossIndex_(std::uint8_t F, std::uint8_t L, std::uint8_t B, std::uint8_t R) noexcept;
    static std::string_view lookupFLBR_(std::uint8_t F, std::uint8_t L, std::uint8_t B, std::uint8_t R) noexcept;
    
public:
    
    //Constructor
   SolvingLogic(Cube& c);

   bool isSolved() const;
   std::array<int, 4> getCrossLocations();
   std::string getCrossSolutions(const std::array<int, 4>& positions);
};

#endif
