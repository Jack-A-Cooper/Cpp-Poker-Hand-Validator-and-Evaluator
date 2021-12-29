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
 * @brief Provides several utility functions/definitions
 * to be used within the main program.
 *
 * @author Jack Cooper
 * Contact: Jack_cooper01@yahoo.com
 *
 */

#ifndef UTIL_H
#define UTIL_H

#define CORRECT_HAND_SIZE 5
#define NUMBER_OF_CARDS 13
#define FACE_CARDS "23456789TJQKA"
#define SUITS "SDCH"
#define FACE 0
#define SUIT 1
#define CARD_SIZE 2
#define BEGINNING 0
#define FIVEOFKINDCHECK 5
#define START 1
#define VECTOR_POS_ONE 0
#define VECTOR_POS_TWO 1
#define HAND_ONE 1
#define HAND_TWO 2
#define TIE 3
#define NIBBLE 3
#define FIRST_BITSET_SIZE 15
#define SECOND_BITSET_SIZE 60
#define MODULO_FOR_ALGORITHM 15
#define FACE_EXISTS_BITSET 0
#define FACE_OCCURENCES_BITSET 1
#define STRAIGHT_FOUND 31
#define LOW_ACE_STRAIGHT_POS_ONE 0
#define LOW_ACE_STRAIGHT_POS_TWO 9
#define LOW_ACE_STRAIGHT_POS_THREE 10
#define LOW_ACE_STRAIGHT_POS_FOUR 11
#define LOW_ACE_STRAIGHT_POS_FIVE 12
#define ACE 14
#define KING 13
#define QUEEN 12
#define JACK 11
#define TEN 10
#define ROYAL_HOUSE 10
#define STRAIGHT_FLUSH 9
#define FOUR_OF_A_KIND 8
#define FULL_HOUSE 7
#define FLUSH 6
#define STRAIGHT 5
#define THREE_OF_A_KIND 4
#define TWO_PAIR 3
#define ONE_PAIR 2
#define HIGH_CARD 1
#define MODULO_FOUR_KIND 1
#define MODULO_FULL_HOUSE 10
#define MODULO_THREE_KIND 9
#define MODULO_TWO_PAIR 7
#define MODULO_ONE_PAIR 6
#define MODULO_HIGH_CARD 5
#define SIZE_OF_BIT_REPRESENTATION 5

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

struct card {
    char face;
    char suit;
    int value;
};

const char facesPossible[] =  {'A', 'K', 'Q', 'J', 'T', '9',
                       '8', '7', '6', '5', '4', '3', '2'};
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