// readFile.h
//

/**
 * @file readFile.cpp
 *
 * @brief Used to read a whole .txt file and return a string vector
 *
 * @author Jack Cooper
 * Contact: Jack_cooper01@yahoo.com
 *
 */

#ifndef READFILE_H
#define READFILE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

// Grabs the correct element from the command line.
// Specifically, the text file input
//
const int FILE_INPUT = 1;
// Specifies the amount of elements allowed in the command line which is only
// two: the exe and the single text file with poker hands to compare.
// Any less (no file specified) or more than one will be rejected.
//
const int ONLY_ONE_FILE = 2;
// Reads a file (.txt) and returns a string vector containing all lines.
// Also handles errors resulting from invalid files.
// 
// First input is the command-line argument count, and the second
// input is a char pointer which specifies the filename of the file
// to be used.
//
std::vector <std::string> readFile(int &argCount, char* &inputFileName);
#endif
