#include <iostream>
#include <vector>
#include <string>
#include "Cube.h"
#include "CubeManipulator.h"
#include "SolvingLogic.h"

std::vector<std::string> parseMoveString(std::string& moves){
    std::vector<std::string> parsedMoves;
    int n = moves.length(); 

    for(int i = 0; i < n; i++){
	if(i + 1 < n && (moves[i + 1] == '\'' || moves[i + 1] == '2')){
	    parsedMoves.push_back(moves.substr(i, 2)); 
	    i++;
	    continue;
	}
	parsedMoves.push_back(moves.substr(i, 1)); 
    }
    return parsedMoves;
}

int main (int argc, char** argv){
    if(argc != 2){
	std::cerr << "Usage: ./executable <mode (cross_solver or self_solve)> " << std::endl;
	exit(1);
    }
    
    std::string mode = argv[1];
    if(mode != "cross_solver" && mode != "self_solve"){
	std::cerr << "Usage: ./executable <mode (cross_solver or self_solve)> " << std::endl;
	exit(1);
    }
     
    Cube c;
    CubeManipulator manip(c);    
    SolvingLogic solver(c);
    
    if(mode == "cross_solver"){
	std::cerr << "Not Implemented" << std::endl;
	exit(1);
    }

    if (mode == "self_solve") {
	std::string scramble;
	std::cout << "Input Scramble: ";
	std::cin >> scramble; 
	std::vector<std::string> moves = parseMoveString(scramble);
	manip.applyManyMoves(moves);

	std::cout << "===== state of cube post scramble =====" << std::endl;
	std::cout << c << std::endl;
	std::cout << "==== input moves to try and solve the cube (q to quit) ===== " << std::endl;	
	while(!solver.isSolved()){
	    std::string input;
	    std::cin >> input;
	    if(input == "q"){
		std::cout << "better luck next time!" << std::endl;
		break;
	    }
	    std::vector<std::string> moves = parseMoveString(input);
	    manip.applyManyMoves(moves);
	    std::cout << c << std::endl;
	}

	if(solver.isSolved()){
	    std::cout << "======== CONGRATULATION YOU SOLVED A RUBIK'S CUBE IN THE TERMINAL !!!! ======= " << std::endl;
	}
    }
    return 0;
}
