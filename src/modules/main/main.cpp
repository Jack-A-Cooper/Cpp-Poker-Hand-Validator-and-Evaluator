// main.cpp
//

#include <../src/headers/pokerCore.h>
#include <../src/headers/readFile.h>
#include <../src/headers/writeFile.h>

using namespace std;

int main(int argc, char* argv[]) {
	// Execution through console (std out).
	//
    pokerCore pokerExecute((readFile(argc, argv[COMMAND_LINE_SELECT])));
	pokerExecute.compareAll();
	// Execution through writing to file.
    //
	pokerCore pokerWrite((readFile(argc, argv[COMMAND_LINE_SELECT])));
	writeToFile(pokerWrite);
    exit(EXIT_SUCCESS);
    return 0;
}
