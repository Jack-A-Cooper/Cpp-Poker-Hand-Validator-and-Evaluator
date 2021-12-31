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
 * @file printTests.cpp
 *
 * @brief tests printout results for functions not covered in 
 * 'pokerHandsTests.cpp'.
 *
 * @author Jack Cooper
 * Contact: Jack_cooper01@yahoo.com
 *
 */

#include "readFile.h"
#include "pokerCompare.h"

using namespace std;

int main(int argc, char* argv[]) {
    // pokerCompare.h tests
    //
    std::vector <std::string> pokerHands = { "JH 7D 9S 3H 3C",
                                         "QH AD TS JH KC" };
    pokerCompare objTest(pokerHands);
    std::vector<std::vector<std::vector<bool>>> testBitset;
    std::vector <std::vector<bool>> bitSetOne{
            {1}, {1}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
            {0}, {0},
    };
    std::vector <std::vector<bool>> bitSetTwo{
        {1, 1, 1, 1}, {0, 0, 0, 1}, {0, 0, 0, 0}, {0, 0, 0, 0},
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
    };
    vector <string> vectorStringOne = { "JH", "7D", "9S", "3H", "4C" };
    vector <string> vectorStringTwo = { "AC", "AS", "AD", "AH", "KH" };
    vector <string> vectorStringThree = { "3C", "AS", "AD", "2H", "KH" };
    vector <card> vectorCardOne = objTest.stringsToCards(vectorStringOne);
    vector <card> vectorCardTwo = objTest.stringsToCards(vectorStringTwo);
    vector <card> vectorCardThree = objTest.stringsToCards(vectorStringThree);
    int winnerOne = HAND_ONE;
    int winnerTwo = HAND_TWO;
    int winnerTie = TIE;
    testBitset.clear();
    testBitset.push_back(bitSetOne);
    testBitset.push_back(bitSetTwo);
    cout << "STARTING PRINT TESTS!" << endl << endl;
    cout << "util.h" << endl << endl;
    cout << "TESTING (printVector) [util.h]" << endl;
    cout << "EXPECTING: JH 7D 9S 3H 4C" << endl;
    cout << "GOT: ";
    printVector(vectorStringOne);
    cout << endl << endl;
    cout << "TESTING (printVector) [util.h]" << endl;
    cout << "EXPECTING: AC AS AD AD KH" << endl;
    cout << "GOT: ";
    printVector(vectorStringTwo);
    cout << endl << endl;
    cout << "TESTING (printVector) [util.h]" << endl;
    cout << "EXPECTING: 3C AS AD 2H KH" << endl;
    cout << "GOT: ";
    printVector(vectorStringThree);
    cout << endl << endl;
    cout << "TESTING (printCardVector) [util.h]" << endl;
    cout << "EXPECTING: JH 7D 9S 3H 4C" << endl;
    cout << "GOT: ";
    printCardVector(vectorCardOne);
    cout << endl << endl;
    cout << "TESTING (printCardVector) [util.h]" << endl;
    cout << "EXPECTING: AC AS AD AD KH" << endl;
    cout << "GOT: ";
    printCardVector(vectorCardTwo);
    cout << endl << endl;
    cout << "TESTING (printCardVector) [util.h]" << endl;
    cout << "EXPECTING: 3C AS AD 2H KH" << endl;
    cout << "GOT: ";
    printCardVector(vectorCardThree);
    cout << endl << endl;
    cout << "pokerCompare.h" << endl << endl;
    cout << "TESTING (print2DBoolVector) [pokerCompare.h]" << endl;
    cout << "EXPECTING: 110000000000000" << endl;
    cout << "GOT: ";
    objTest.print2DBoolVector(bitSetOne);
    cout << endl << endl;
    cout << "TESTING (print2DBoolVector) [pokerCompare.h]" << endl;
    cout << "EXPECTING: 111100010000000000000000000000000000000000000000000000000000" << endl;
    cout << "GOT: ";
    objTest.print2DBoolVector(bitSetTwo);
    cout << endl << endl;
    cout << "TESTING (printWinner) [pokerCompare.h]" << endl;
    cout << "EXPECTING: Hand 1 Wins!" << endl;
    cout << "GOT: ";
    objTest.printWinner(winnerOne);
    cout << endl << endl;
    cout << "TESTING (printWinner) [pokerCompare.h]" << endl;
    cout << "EXPECTING: Hand 2 Wins!" << endl;
    cout << "GOT: ";
    objTest.printWinner(winnerTwo);
    cout << endl << endl;
    cout << "TESTING (printWinner) [pokerCompare.h]" << endl;
    cout << "EXPECTING: Tie!" << endl;
    cout << "GOT: ";
    objTest.printWinner(winnerTie);
    cout << endl << endl;
    cout << "END OF PRINT TESTS!" << endl;
    exit(EXIT_SUCCESS);
    return 0;
}