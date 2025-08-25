#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Cube.h"
#include "CubeManipulator.h"
#include "SolvingLogic.h"

std::array<std::pair<Face, Face>, 24> faces = {{
    {Face::UP, Face::RIGHT},
    {Face::UP, Face::BACK},
    {Face::UP, Face::LEFT},
    {Face::UP, Face::FRONT},
    {Face::DOWN, Face::RIGHT},
    {Face::DOWN, Face::BACK},
    {Face::DOWN, Face::LEFT},
    {Face::DOWN, Face::FRONT},
    {Face::RIGHT, Face::UP},
    {Face::RIGHT, Face::BACK},
    {Face::RIGHT, Face::DOWN},
    {Face::RIGHT, Face::FRONT},
    {Face::LEFT, Face::UP},
    {Face::LEFT, Face::BACK},
    {Face::LEFT, Face::DOWN},
    {Face::LEFT, Face::FRONT},
    {Face::BACK, Face::UP},
    {Face::BACK, Face::LEFT},
    {Face::BACK, Face::DOWN},
    {Face::BACK, Face::RIGHT},
    {Face::FRONT, Face::UP},
    {Face::FRONT, Face::LEFT},
    {Face::FRONT, Face::DOWN},
    {Face::FRONT, Face::RIGHT}
}}; 

bool validMove(char move){
    return move == 'R' || move == 'U' || move == 'D' || move == 'L' || move == 'F' || move == 'B';
}
std::vector<std::string> parseMoveString(std::string& moves){
    std::vector<std::string> parsedMoves;
    int n = moves.length(); 
    
    for(int i = 0; i < n; i++){
	if(!validMove(moves[i])) continue;
	if(i + 1 < n && (moves[i + 1] == '\'' || moves[i + 1] == '2')){
	    parsedMoves.push_back(moves.substr(i, 2)); 
	    i++;
	    continue;
	}
	parsedMoves.push_back(moves.substr(i, 1)); 
    }
    return parsedMoves;
}

void printMoveString(const std::vector<std::string>& moves){
    int n = moves.size();
    for(int i = 0; i < n; i++){
	std::cout << moves[i] << " ";
    }
    std::cout << std::endl;
}

int numMoves(const std::string& sol){
    int res = 0;
    int n = sol.length();
    for(int i = 0; i < n; i++){
	if (validMove(sol[i])) ++res;
    }
    return res;
}

std::string getOrientation(Cube c){

    char f = c.getColorAtPosition(Face::FRONT, 1, 1);
    char d = c.getColorAtPosition(Face::DOWN, 1, 1);

    std::string front;
    std::string down;

    if(f == 'W') front = "White";
    if(d == 'W') down = "White";
    if(f == 'R') front = "Red";
    if(d == 'R') down = "Red";
    if(f == 'B') front = "Blue";
    if(d == 'B') down = "Blue";
    if(f == 'G') front = "Green";
    if(d == 'G') down = "Green";
    if(f == 'O') front = "Orange";
    if(d == 'O') down = "Orange";
    if(f == 'Y') front = "Yellow";
    if(d == 'Y') down = "Yellow";

    return down + " Cross, " + front + " in front";
}

void printSolutions(const std::vector<std::pair<std::string, std::string>>& sol, const Cube& c){
    int n = sol.size();
    for(int i = 0; i < n; i++){
	std::cout << "Solution: " << std::setw(20) << std::left << sol[i].first;
	std::cout << std::setw(45) << std::left << sol[i].second;
	Cube temp = c;
	temp.orient(faces[i].first, faces[i].second);
	CubeManipulator manip(temp);
	std::string unparsed_moves = sol[i].first;
	std::vector<std::string> moves = parseMoveString(unparsed_moves);
	manip.applyManyMoves(moves);
	std::cout << "Move Count: " << std::setw(10) << std::left << moves.size() << std::endl;
	std::cout << "After Cross Solution: " << std::endl << temp << std::endl;
    }
}

int main (){

    Cube c;
    CubeManipulator scrambler(c);
    std::string scramble;

    std::cout << "Input Scramble: ";
    std::getline(std::cin, scramble);

    std::vector<std::string> parsed_scramble = parseMoveString(scramble);
    scrambler.applyManyMoves(parsed_scramble);
    
    std::cout << "Initital State" << std::endl;
    std::cout << std::endl << c << std::endl;
    
    std::vector<std::pair<std::string, std::string>> solutions;
    
    for(int i = 0; i < 24; i++){
	Cube temp = c;
	SolvingLogic solver(temp);
	temp.orient(faces[i].first, faces[i].second);
	std::array<int, 4> pos =  solver.getCrossLocations();
	std::string sol = solver.getCrossSolutions(pos);
	std::string orientation = getOrientation(temp);
	solutions.push_back({sol, orientation});
    }
    
    printSolutions(solutions, c);
}
