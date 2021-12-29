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

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "readFile.h"

using namespace std;

#define FILE_INPUT 1
#define ONLY_ONE_FILE 2

vector <string> readFile(int &argCount, char* &inputFileName) {
    ifstream inputFile;
    if(argCount != ONLY_ONE_FILE){
        cout << "ERROR: No file specified!" << endl;
        exit(EXIT_FAILURE);
    }
    inputFile.open(inputFileName);
    vector <string> handsOfFile;
    if(inputFile.is_open()){
        string line;
        while (getline(inputFile, line)) {
            handsOfFile.push_back(line);
        }
        inputFile.close();
        if(handsOfFile.size() % 2 != 0 || 
           handsOfFile.empty()){
            cout <<
                "ERROR: Invalid file - not an even amount of hands or empty!"
                 << endl;
            exit(EXIT_FAILURE);
        } else {
            return handsOfFile;
        }
    } else {
        cout << "ERROR: file failed to load!" << endl;
        exit(EXIT_FAILURE);
    }
}