// util.h
//

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

// Selects the text file for running the main program in 'main.cpp'.
// Will select the input file correctly from the commandline.
//
const int COMMAND_LINE_SELECT = 1;
// The correct size of a hand. Used in the validator 
// to reject wrong hand sizes.
//
const int CORRECT_HAND_SIZE = 5;
// The correct number of cards that exist in legal poker
// used primarily in masking loops to correctly mask the hand.
//
const int NUMBER_OF_CARDS = 13;
// Every card size must equal two. Used in the hand validator
// to reject wrong card sizes.
//
const int CARD_SIZE = 2;
// Positions of the value or suit of a card in string form
// used to check the value or suit of a string.
//
const int VALUE = 0;
const int SUIT = 1;
// True values of cards. Since letters do not have value,
// these are used when determining what kind of card it is
// so correct magnitude can be assigned. Note that aces are high.
// 
const int ACE = 14;
const int KING = 13;
const int QUEEN = 12;
const int JACK = 11;
const int TEN = 10;
// First Index of container.
// Used to get the first element.
//
const int FIRST_INDEX = 0;
// Used for correctly printing the current round of comparison
// in the compareAll function in 'pokerCore.cpp'. Round number start at 1.
//
const int START = 1;
// Guard for hand validation. If five of the same
// same value appear, the validator rejects the hand.
//
const int FIVEOFKINDCHECK = 5;
// First index of vector and second
// index of vector respectively.
//
const int VECTOR_POS_ONE = 0;
const int VECTOR_POS_TWO = 1;
// Used in return of printWinner function 'pokerCore.cpp'
// prints correct winner depending on results of comparison
//
const int HAND_ONE = 1;
const int HAND_TWO = 2;
const int TIE = 3;
// Nibble is 4 bits. This is used when masking the second bitset
// for value value occurences so that only 4 bits are modified corresponding
// to each value value. Loop is 3 >= 0 so must be set to 3 for 4 iterations.
//
const int NIBBLE = 3;
// Sizes for each bit set as stated by the algorithm
//
const int FIRST_BITSET_SIZE = 15;
const int SECOND_BITSET_SIZE = 60;
// Taking the second bitset and modding by 15
// always results in the same numbers for the specified hand ranks
// the first bitset is of size 15 as well.
//
const int MODULO_FOR_ALGORITHM = 15;
// The first bitset contains what values appear in hand.
// The second bitset contains how many of each value denomination
// appears in the hand.
//
const int VALUE_EXISTS_BITSET = 0;
const int VALUE_OCCURENCES_BITSET = 1;
// Value found by algorithm that determines
// if a straight exists (since 11111 -> 31 in binary).
// It is used in the first bitset that identifies what hands exist
// so if the mask looks like: '000111110000000', a straight exists.
//
const int STRAIGHT_FOUND = 31;
// Positions that highlight an Ace-low straight
// in the first bitset
// if all of these positions are true or '1',
// then an ace-low straight is found
//
const int LOW_ACE_STRAIGHT_POS_ONE = 0;
const int LOW_ACE_STRAIGHT_POS_TWO = 9;
const int LOW_ACE_STRAIGHT_POS_THREE = 10;
const int LOW_ACE_STRAIGHT_POS_FOUR = 11;
const int LOW_ACE_STRAIGHT_POS_FIVE = 12;
// Expected results from taking mod 15
// from a modulo result (function in pokerCore.cpp).
// values are used here for proper identification of the hand
// to then be converted to its real value.
//
const int MODULO_FOUR_KIND = 1;
const int MODULO_FULL_HOUSE = 10;
const int MODULO_THREE_KIND = 9;
const int MODULO_TWO_PAIR = 7;
const int MODULO_ONE_PAIR = 6;
const int MODULO_HIGH_CARD = 5;
// Positions dictated by the algorithm
// for shift-logical-left operations
//
const int SLL_ALGO_FIRST_NUMBER = 16;
const int SLL_ALGO_SECOND_NUMBER = 12;
const int SLL_ALGO_THIRD_NUMBER = 8;
const int SLL_ALGO_FORTH_NUMBER = 4;
const int SLL_ALGO_FIFTH_NUMBER = 0;
// Binary base used for converting a string to a decimal
// used in tie breaking
//
const int BINARY_BASE = 2;
// Defines the possible value types allowed.
// Example:
//    if a value type is found that does not appear in this array
//    it is tossed out in the hand validator. Used primarily to check
//    a given string or card for its magnitude value.
//    the magnitude is the actual integer value of the card's symbol (char) value
//
const char VALUES_POSSIBLE[] =  {'A', 'K', 'Q', 'J', 'T', '9',
                                '8', '7', '6', '5', '4', '3', '2'};
// Defines a card.
// Example:
//    Given a string "3S", the magnitude will become 3
//    the value will become '3', and the suit will
//    become 'S'. Struct is used extensively to
//    properly evaluate card values and for checking
//    what kind of rank the given hand is (e.g., a flush).
//
struct card {
    char value;
    char suit;
    int magnitude;
};
// Source: https://slaystudy.com/c-split-string-by-space-into-vector/
// Answer by: none specified
// Parses string into a string vector. Removes leading/trailing spaces.
// 
// The first input is a string to use to populate the vector, and the second
// input is the specified vector to populate.
//
void splitString(std::string &inputString, 
                 std::vector <std::string> &stringVector);
// Source: http://www.cplusplus.com/forum/beginner/89508/
// Answer by: vlad from moscow
// Makes all characters uppercase in a string vector.
// 
// Input is a string vector that will be modified to be all caps.
//
void convertUpper(std::vector <std::string> &handStringVector);
// Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
// Answer by: Evan Teran
// Trim from start (in place). Whitespace to left is removed.
// 
// Input is a string to trim left whitespace.
//
inline void leftTrim(std::string &s);
// Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
// Answer by: Evan Teran
// Trim from end (in place). Whitespace to right is removed.
// 
// Input is a string to trim right whitespace.
//
inline void rightTrim(std::string &s);
// Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
// Answer by: Evan Teran
// Trim from both ends (in place). Whitespace left and right is removed.
// 
// Input is a string to trim both left and right whitespace.
//
inline void trim(std::string &s);
// Prints entire string vector.
// 
// Input is a string vector.
//
void printVector(std::vector <std::string> &vector);
// Prints entire card vector.
// 
// Input is a vector of cards.
//
void printCardVector(std::vector <card> &vector);
// Compares card values based on their magnitude value.
// Returns true if card one has a larger magnitude value than card two.
// False otherwise.
// 
// First input is the first card, and the second input is the second card.
//
bool compareCardMagnitude(const card &cardOne, const card &cardTwo);
// Sorts vector by magnitude value. High to low order.
// Example: ("5H KH 2D QH AC") becomes: ("AC KH QH 5H 2D").
// 
// Input is a card vector.
//
void sortHand(std::vector <card> &vector);
// Source: https://codereview.stackexchange.com/questions/173382/sorting-elements-according-to-frequency-of-occurence-in-c
// Answer by: coderodde
// Sorts an int vector first by the frequency of the int, and then by the magnitude.
// Used in Deep Evaluation Process. Only magnitude values required - which since magnitudes
// are used to compare values between cards.
// 
// Input is an integer vector.
// 
void sortByOccurencesThenByMagnitude(std::vector<int> &vector);
// Converts a vector string into a string. Returns the converted string.
// 
// Input is a string vector.
//
std::string vectorToString(std::vector<std::string> &vector);
// Returns a char of '0' or '1' representing false/true respectively.
// 
// Input is simply a boolean. Used in getting true/false from bitmasks.
//
char getBit(bool input);
// Returns the value from the mask specified (value existing in a hand or value 
// occurences in a hand). Used for a comparison value for the algorithm.
// 
// Input is a vector of vectors containing booleans.
//
unsigned long long getLongFromMask(std::vector <std::vector<bool>> &vector);
// Returns the first bitset mask (what values occur in the hand).
// Used in algorithm to determine hands.
// 
// Input is a vector of vectors containing booleans.
//
std::bitset<FIRST_BITSET_SIZE> getBinaryFromMaskFirstBitset(std::vector <std::vector<bool>> &vector);
// Returns the second bitset mask (how many of each value occurs in the hand).
// Used in algorithm to determine hands.
// 
// Input is a vector of vectors containing booleans.
//
std::bitset<SECOND_BITSET_SIZE> getBinaryFromMaskSecondBitset(std::vector <std::vector<bool>> &vector);
// Returns an integer vector from a card vector. Strips aways suits for use in bitwise
// operations. Used to help break ties if they occur.
// 
// Input is a vector of cards.
//
std::vector <int> getIntegerVector(std::vector <card> &vector);
// Source: https://www.delftstack.com/howto/cpp/how-to-convert-decimal-number-to-binary-in-cpp/
// Answer by: none specified
// Converts decimal number to a binary string.
// 
// Input is a decimal number.
//
std::string toBinary(int &n);
#endif