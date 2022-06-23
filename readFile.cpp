// readFile.cpp
//

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
