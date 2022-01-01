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
#include "readFile.h"

using namespace std;
vector <string> readFile(int &argCount, char* &inputFileName) {
    ifstream inputFile;
    // Check for less than one file or more than one file.
    // Must have one, and only one, file in command-line.
    //
    if(argCount != ONLY_ONE_FILE){
        cout << "ERROR: No file specified or more than one specified!" << endl;
        exit(EXIT_FAILURE);
    }
    inputFile.open(inputFileName);
    vector <string> handsOfFile;
    // Grab all lines from file as strings.
    // Deposit them line by line into a string vector.
    //
    if(inputFile.is_open()){
        string line;
        while (getline(inputFile, line)) {
            handsOfFile.push_back(line);
        }
        inputFile.close();
        if(handsOfFile.size() % 2 != 0 || 
           handsOfFile.empty()){
            // File contains an odd amount of hands.
            // Must be even for comparing purposes.
            //
            cout <<
                "ERROR: Invalid file - not an even amount of hands or empty!"
                 << endl;
            exit(EXIT_FAILURE);
        } else {
            return handsOfFile;
        }
    } else {
        // Cannot find file.
        //
        cout << "ERROR: file failed to load!" << endl;
        exit(EXIT_FAILURE);
    }
}