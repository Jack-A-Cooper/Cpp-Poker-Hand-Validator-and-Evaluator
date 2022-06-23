// main.cpp
//

#include "readFile.h"
#include "pokerCompare.h"

using namespace std;

int main(int argc, char* argv[]) {
    pokerCompare pokerComparer((readFile(argc, argv[COMMAND_LINE_SELECT])));
    pokerComparer.compareAll();
    exit(EXIT_SUCCESS);
    return 0;
}
