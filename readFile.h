/* Copyright 2021 Jack Alexander Cooper
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following
* conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
* this list of conditions and the following disclaimer in the documentation
* and/or other materials provided with the distribution.
*
* 3. Neither the name of the copyright holder nor the names of its contributors
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE 
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR 
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER 
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE 
* USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**/

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