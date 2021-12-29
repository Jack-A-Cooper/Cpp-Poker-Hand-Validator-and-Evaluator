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
 * @file pokerCompare.cpp
 *
 * @brief Provides the core of the implementation. Functionality 
 * is encapsulated in a class.
 *
 * @author Jack Cooper
 * Contact: Jack_cooper01@yahoo.com
 *
 */

#ifndef POKERCOMPARE_H
#define POKERCOMPARE_H
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bitset>
#include <cctype>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "util.h"

/**
 * pokerCompare Class (core of program).
 *
 * This class handles the validating and evaluating
 * of poker hands. It is initialized with a string vector
 * that contains an even amount of hands to compare (a whole file's worth).
 * Each pair compared is known as a 'round'. Comparisons
 * are continued until the vector "allHands" is depleted, thus
 * no more pairs are left to be conmpared in the text file.
 * Simple usage of the class is as follows:
 * instantiate with pokerCompare <nameOfObj>(vector <string> pokerHands).
 * To use, simply call <nameOfObj>.compareAll(). If using with a text file,
 * be sure that it pulls from the commandline and utilizes my own readFile.cpp
 * implementation so that is may correctly validate, and use the file.
 * Lastly, popping back and getting back operations are used. Please
 * note that the vector containing all hands (all pairs) will be reversed
 * for this reason.
 * 
 * Example (given a text file called 'test.txt'): 
 *  pokerCampare myPokerObj(readFile("test.txt"));
 *  myPokerObj.compareAll();
 * 
 * A command line implementation is utilized in main.cpp of this program.
 */
class pokerCompare {
    private:
     int numOfPairs;
     // Stores all string lines from a file input.
     // Every 'round' pops two strings off of this vector.
     std::vector <std::string> allHands;
     // Stores the two string vectors that each contain a poker hand.
     // These two string vectors are then used in evaluations
     std::vector <std::vector<std::string>> currentRound;
     // Stores the valid face values that a poker hand may have.
     // Default is vanilla poker faces without wild cards (e.g., jokers).
     // Note that face card '10' is 'T'.
     std::vector <std::string> faces;
     // Stores the valid suit values that a poker hand may have.
     // Default is vanilla poker suits - H,C,S,D.
     std::vector <std::string> suits;
     std::map <std::string, int> ranks;
    public:
     // Instantiates a pokerCompare object for use, it
     // has a single input which is a vector <string> 
     // which contains all poker hand pairs to be compared.
     //
     pokerCompare(std::vector <std::string> inputHands);
     // Sets the object's allHands vector. Also reverses this
     // vector so that the back of the vector becomes the front.
     // This is for pop back and back operations to work.
     //
     void setAllHands(std::vector <std::string> &fileInputHands);
     void setCurrentRound(std::vector <std::vector<std::string>> pair);
     void setNumPairs(int &setPairNum);
     void setFaces(std::vector<std::string> &newFaces);
     void setSuits(std::vector<std::string> &newSuits);
     void setRanks(std::map<std::string, int> &newRanks);
     std::vector<std::string> getFaces();
     std::vector<std::string> getSuits();
     std::map<std::string, int> getRanks();
     std::vector <std::vector<std::string>> getCurrentRound();
     std::vector <std::string> getAllHands();
     int getNumPairs();
     // Validates a string input, will crash program.
     // If the string violates a proper poker hand.
     //
     void validateHand(std::vector <std::string> &hand);
     // Grabs next pair to compare. Performs validation/sorting on each.
     // Modifies object's allHands by reducing its size by 2 each function call.
     //
     std::vector <std::vector<std::string>> getNextPair();
     // Evaluates a poker hand inputted as a card vector.
     // Returns a vector of vectors containing the masked bitsets
     // of faces existing in hand and face occurences.
     //
     std::vector<std::vector<std::vector<bool>>> getHandMask(std::vector <card> &inputHand);
     // Evaluates two poker hands inputted as a string vectors.
     // Returns an integer of who won, or if a tie was found
     // 1 - first hand won, 2 - second hand won, 3 - tie
     // calls further functions when a tie is found to
     // determine a winner or if the hands match exactly,
     // thus being a tie. Sorts hands to help with comparison.
     //
     int compareHands(std::vector <std::string> &handOne,
                      std::vector <std::string> &handTwo);
     int getHandRank(std::vector <std::string> &hand);
     std::string getRankFromModulo(unsigned long long &moduloScore);
     // Compares and evaluates a winner for  entire object's 
     // allHands vector (all hands in file).
     //
     void compareAll();
     // Determines if all pairs have been processed/evaluated.
     // returns true if allHands is empty, and false otherwise.
     //             
     bool empty();
     // Displays winner to console based off results from compareHands().
     //      
     void printWinner(int &result);
     // Prints the 2D vectors for the binary masking.
     //
     void print2DBoolVector(std::vector<std::vector<bool>> &vector);
     card getCard(std::string &input);
     std::string getStringFromCard(card &input);
     std::vector <std::string> cardsToStrings(std::vector<card> &cards);
     std::vector<card> stringsToCards(std::vector <std::string> &vector);
     std::string vectorToString(std::vector<std::string> &vector);
     int countOccurences(std::vector <std::string> &vector, char &key);
     bool occurs(std::vector <std::string> &vector, char &key);
     unsigned long long moduloResult(std::vector <std::vector<bool>> &input);
     std::vector<std::vector<std::vector<bool>>> maskHandBinary(std::vector <card> &vector);
     bool checkStraight(std::vector<std::vector<std::vector<bool>>> &input);
     bool checkFlush(std::vector <card> &input);
     bool checkRoyalFlush(std::vector <card> &input);
     int getTieBreakScore(std::vector <card> &input);
     int getRankScore(std::string &input);
};
#endif