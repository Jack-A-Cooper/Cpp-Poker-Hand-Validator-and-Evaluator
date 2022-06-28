// writeFile.h
//

#ifndef WRITEFILE_H
#define WRITEFILE_H

#include <iostream>
#include <fstream>
#include <string>
// Depends on pokerCore
//
#include <../src/headers/pokerCore.h>

// Writes results of a pokerObj's comparisons to an output file.
// The format is similar to how pokerCore's compareAll function
// prints to the console while running.
//
void writeToFile(pokerCore& pokerObj);
// Compares and evaluates a winner for entire object's 
// allHands vector (all hands in file). The alternate main driver of the program.
// Should only be used on a pokerCore object that has be initialized,
// and is in the main driver file 'main.cpp'.
// Outputs winners of each round to an int vector.
// Each element stores the winner between the two pairs for that round.
//
void compareAllWrite(pokerCore& pokerObj, std::ofstream& outputFile);
// Writes winner to an output file based off results from the compareHands
// function.
// 
// Input is an integer determined in compareAllWrite round by round.
//      
void writeWinner(int& result, std::ofstream& outputFile);
void printStringVector(std::vector<std::string >& vector, std::ofstream& outputFile);
#endif