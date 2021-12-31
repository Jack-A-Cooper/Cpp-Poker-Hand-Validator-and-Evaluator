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
 * @file util.cpp
 *
 * @brief Provides several utility functions/constants
 * to be used within the main program.
 *
 * @author Jack Cooper
 * Contact: Jack_cooper01@yahoo.com
 *
 */

#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <string>
#include <sstream>
#include <bitset>
#include <cctype>
#include <vector>
#include <map>
#include <algorithm>
#include <locale>
#include <array>
#include <unordered_map>

const int COMMAND_LINE_SELECT = 1;
const int CORRECT_HAND_SIZE = 5;
const int NUMBER_OF_CARDS = 13;
const int CARD_SIZE = 2;
const int FACE = 0;
const int SUIT = 1;
const int ACE = 14;
const int KING = 13;
const int QUEEN = 12;
const int JACK = 11;
const int TEN = 10;
const int FIRST_INDEX = 0;
const int START = 1;
const int FIVEOFKINDCHECK = 5;
const int VECTOR_POS_ONE = 0;
const int VECTOR_POS_TWO = 1;
const int HAND_ONE = 1;
const int HAND_TWO = 2;
const int TIE = 3;
const int NIBBLE = 3;
const int FIRST_BITSET_SIZE = 15;
const int SECOND_BITSET_SIZE = 60;
const int MODULO_FOR_ALGORITHM = 15;
const int FACE_EXISTS_BITSET = 0;
const int FACE_OCCURENCES_BITSET = 1;
const int STRAIGHT_FOUND = 31;
const int LOW_ACE_STRAIGHT_POS_ONE = 0;
const int LOW_ACE_STRAIGHT_POS_TWO = 9;
const int LOW_ACE_STRAIGHT_POS_THREE = 10;
const int LOW_ACE_STRAIGHT_POS_FOUR = 11;
const int LOW_ACE_STRAIGHT_POS_FIVE = 12;
const int MODULO_FOUR_KIND = 1;
const int MODULO_FULL_HOUSE = 10;
const int MODULO_THREE_KIND = 9;
const int MODULO_TWO_PAIR = 7;
const int MODULO_ONE_PAIR = 6;
const int MODULO_HIGH_CARD = 5;
const int SIZE_OF_BIT_REPRESENTATION = 5;
const int SLL_ALGO_FIRST_NUMBER = 16;
const int SLL_ALGO_SECOND_NUMBER = 12;
const int SLL_ALGO_THIRD_NUMBER = 8;
const int SLL_ALGO_FORTH_NUMBER = 4;
const int SLL_ALGO_FIFTH_NUMBER = 0;
const int BINARY_BASE = 2;
const char FACES_POSSIBLE[] =  {'A', 'K', 'Q', 'J', 'T', '9',
                                '8', '7', '6', '5', '4', '3', '2'};
struct card {
    char face;
    char suit;
    int value;
};
// Source: https://slaystudy.com/c-split-string-by-space-into-vector/
// Answer by: none specified
// Parses string into a string vector. Removes leading/trailing spaces.
//
void splitString(std::string &inputString, 
                 std::vector <std::string> &StringVector);
// Source: http://www.cplusplus.com/forum/beginner/89508/
// Answer by: vlad from moscow
// Makes all characters uppercase in a string vector.
//
void convertUpper(std::vector <std::string> &handStringVector);
// Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
// Answer by: Evan Teran
// Trim from start (in place).
//
static inline void leftTrim(std::string &s);
// Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
// Answer by: Evan Teran
// Trim from end (in place).
//
static inline void rightTrim(std::string &s);
// Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
// Answer by: Evan Teran
// Trim from both ends (in place).
//
static inline void trim(std::string &s);
// Prints entire string vector.
//
void printVector(std::vector <std::string> &vector);
// Prints entire card vector.
//
void printCardVector(std::vector <card> &vector);
bool compareCardValue(const card &cardOne, const card &cardTwo);
// Sorts vector by face value. High to low order.
// Example: ("5H KH 2D QH AC") becomes: ("AC KH QH 5H 2D").
//
void sortHand(std::vector <card> &vector);
// Source: https://codereview.stackexchange.com/questions/173382/sorting-elements-according-to-frequency-of-occurence-in-c
// Answer by: coderodde
// Sorts int vector by order of occurences.
// Used in tie breaking scenarios. Int vector used since by the time a tie is
// needing to be broken, only the face values are needed.
// 
void sortByOccurencesAndValue(std::vector<int> &vector);
std::string vectorToString(std::vector<std::string> &vector);
char getBit(bool input);
unsigned long long getLongFromMask(std::vector <std::vector<bool>> &vector);
std::bitset<FIRST_BITSET_SIZE> getBinaryFromMaskFirstBitset(std::vector <std::vector<bool>> &vector);
std::bitset<SECOND_BITSET_SIZE> getBinaryFromMaskSecondBitset(std::vector <std::vector<bool>> &vector);
std::vector <int> getIntegerVector(std::vector <card> &vector);
// Source: https://www.delftstack.com/howto/cpp/how-to-convert-decimal-number-to-binary-in-cpp/
// Answer by: none specified
// Converts decimal number to a binary string.
//
std::string toBinary(int &n);
int getRankValue(std::string &input);
#endif