// pokerCompare.h
//

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
 * for this reason. Please note that the bitmasking algorithm was
 * implemented for the hand evaluation. Please refer to the 'Readme.txt'
 * for an in-depth explination of how this algorithm works. Some notes
 * are commented regarding aspects of the program that are following
 * the algorithm.
 * 
 * Example (given a text file called 'test.txt'): 
 *  pokerCampare myPokerObj(readFile("test.txt"));
 *  myPokerObj.compareAll();
 * 
 * A command line implementation is utilized in main.cpp of this program.
 */
class pokerCompare {
    private:
     // Stores the number of pairs to be evaluated.
     // Used to determine when rounds can stop.
     //
     int numOfPairs;
     // Stores all string lines from a file input.
     // Every 'round' pops two strings off of this vector.
     //
     std::vector <std::string> allHands;
     // Stores all the poker hands (strings)
     // that have yet to be evaluated/compared.
     // Each element is a string representing a poker hand.
     // Will have the first two elements removed for use
     // in the next round of comparisons.
     //
     // Note: all strings will require validation conforming to
     // a valid hand. Validation is done when the next round is
     // processed. This is done by the function "validateHand".
     // Refer to that function's comment block for the hand validation.
     //
     std::vector <std::vector<std::string>> currentRound;
     // Stores the valid face values that a poker hand may have.
     // Legal poker faces without wild cards (e.g., jokers).
     // Note that face card '10' is 'T'.
     //
     std::vector <std::string> faces;
     // Stores the valid suit values that a poker hand may have.
     // Legal poker suits are: H,C,S,D.
     //
     std::vector <std::string> suits;
     // Stores the possible hand ranks that a hand could be.
     // Used to determine what a returned string is converted
     // into a rank with a score.
     //
     std::map <std::string, int> ranks;
    public:
     // Instantiates a pokerCompare object for use, it
     // has a single input which is a vector <string> 
     // which contains all poker hand pairs to be compared.
     // 
     // Input is a vector containing all hands to be compared.
     // Note that the size of the vector must be even.
     //
     pokerCompare(std::vector <std::string> inputHands);
     // Sets the object's allHands vector. Also reverses this
     // vector so that the back of the vector becomes the front.
     // This is for pop_back() and back() operations to work.
     // 
     // Input is taken from an input text file from specified on the command line.
     //
     void setAllHands(std::vector <std::string> &fileInputHands);
     // Updates the current rounds. This round is the next two hands to be validated,
     // and then compared.
     // 
     // Input is a vector of vector containing strings. Corresponds to the next pair,
     // where each hand is a string vector.
     //
     void setCurrentRound(std::vector <std::vector<std::string>> pair);
     // Sets the number of pairs left to be compared.
     // 
     // Input is an integer, and should be even.
     //
     void setNumPairs(int &setPairNum);
     // Returns the current round as a vector of vectors containing strings. Each vector
     // contained in a hand to be evaluated.
     //
     std::vector <std::vector<std::string>> getCurrentRound();
     // Returns the number of pairs of hands left to be evaluated as an integer.
     // 
     int getNumPairs();
     // Validates a string input, will crash program.
     // If the string violates a proper poker hand.
     // 
     // Input is a string vector where each card is an element.
     //
     void validateHand(std::vector <std::string> &hand);
     // Grabs next pair to compare. Performs validation/sorting on each.
     // Modifies object's allHands by reducing its size by 2 each function call.
     // 
     // Returns a vector of vector of strings where each element vector is a hand to
     // be evaluated/compared next.
     //
     std::vector <std::vector<std::string>> getNextPair();
     // Evaluates a poker hand inputted as a card vector.
     // Returns a vector of vectors containing the masked bitsets
     // of faces existing in hand and face occurences.
     // Used to follow the implemented algorithm.
     // 
     // Returns a vector of vector of vectors containing boolean values '0' - false
     // '1' - true.
     //
     std::vector<std::vector<std::vector<bool>>> getHandMask(std::vector <card> &inputHand);
     // Evaluates two poker hands inputted as a string vectors.
     // Returns an integer of who won, or if a tie was found
     // 1 - first hand won, 2 - second hand won, 3 - tie
     // calls further functions when a tie is found to
     // determine a winner or if the hands match exactly,
     // thus being a tie. Sorts hands to help with comparison.
     // 
     // Input is two string vectors corresponding to handOne and handTwo Respectively.
     //
     int compareHands(std::vector <std::string> &handOne,
                      std::vector <std::string> &handTwo);
     // Returns an integer specifying the rank of the hand. This integer is then used
     // to get the correct value from the pokerCompare's rank map.
     //
     // Input is a string vector that is a hand.
     //
     int getHandRank(std::vector <std::string> &hand);
     // Returns a string specifying the rank of the hand found from using modulo division
     // that determines what kind of hand was found. This is used further to assign a
     // correct value to the hand given the modulo score obtained. This uses the pokerCompare's
     // rank map to do so.
     // 
     // Input is an unsigned long long that is a number obtained from a modulo score.
     //
     std::string getRankFromModulo(unsigned long long &moduloScore);
     // Compares and evaluates a winner for  entire object's 
     // allHands vector (all hands in file). The main driver of the program.
     // Should only be used on a pokerCompare object that has be initialized,
     // and is in the main driver file 'main.cpp'.
     //
     void compareAll();
     // Determines if all pairs have been processed/evaluated.
     // returns true if allHands is empty, and false otherwise.
     //             
     bool empty();
     // Displays winner to console based off results from the compareHands
     // function.
     // 
     // Input is an integer determined in compareHands.
     //      
     void printWinner(int &result);
     // Prints the 2D vectors for the binary masking.
     // 
     // Input is one of the selected bitset's as a vector of vectors
     // containing booleans.
     //
     void print2DBoolVector(std::vector<std::vector<bool>> &vector);
     // Returns a card. This card is given a face, suit, and value
     // Note that the value is the correct value of the face (if
     // the face were an 'A' the value would be 14).
     //
     // Input is a string that is in the form of "AS".
     //
     card getCard(std::string &input);
     // Returns a string given a card. Where its face, suit, and value are
     // converted back into string form.
     // Example: card 'TC'
     //     its face = 'T', suit = 'C', and value = 10, then "TC" is returned.
     //
     // Input is a card.
     //
     std::string getStringFromCard(card &input);
     // Converts a card  vector into a string vector.
     //
     // Input is a card vector to be converted back into a string vector.
     //
     std::vector <std::string> cardsToStrings(std::vector<card> &cards);
     // Converts a string vector into a card vector. Card vectors are used for
     // actual comparing, and checking card ranks. It's necessary to convert the input
     // string vectors originally obtained from the input file into useable card 
     // structures to be compared or evaluate a hand's rank/value/
     //
     // Input is a vector of strings.
     //
     std::vector<card> stringsToCards(std::vector <std::string> &vector);
     // Converts a vector into a string, and then returns the string.
     // Used when calling countOccurences to determine the second bitset mask.
     //
     // Input is a vector of strings
     //
     std::string vectorToString(std::vector<std::string> &vector);
     // Returns an integer specifying how many times a face value occurs
     // in a given hand. Used for the second bitset mask for occurences.
     //
     // Input is a vector of strings (the hand) and a char specifying what
     // face to count.
     //
     int countOccurences(std::vector <std::string> &vector, char &key);
     // Returns a boolean if the specified face cards occurs in the hand.
     //
     // Input is a vector of strings (the hand) and a char specifying what face
     // to search for.
     //
     bool occurs(std::vector <std::string> &vector, char &key);
     // Returns an unsigned long long number that is obtained using the algorithm's
     // modulos division (mod by 15). This result is used for determining six of the
     // ten hands possible.
     //
     // Input is a vector of vectors containing booleans (uses the second bitset mask).
     //
     unsigned long long moduloResult(std::vector <std::vector<bool>> &input);
     // Masks the provided vector of cards for use in the algorthim for comparison.
     // This mask (a vector of vectors of vectors containing booleans) is returned.
     // Two bitsets containing booleans are put into a vector. The first bitset
     // holds what face values occur, and the second bitset holds how many of each face
     // value occurs in the hand. This is then used for the entire algorithm to determine
     // the hand's rank, and thus, how it compares to another hand, and also to break ties.
     //
     // Input is a card vector that will be masked.
     //
     std::vector<std::vector<std::vector<bool>>> maskHandBinary(std::vector <card> &vector);
     // Returns true or false depending on if a straight is found using the algorithm.
     //  Used in combination with
     // checkFlush to determine if a stright-flush exists.
     //
     // Input is a vector of vector of vectors containing booleans (the mask
     // obtained from masking a card vector). The second bitset of the mask
     // (face value occurences in hand) is used. Searches for a pattern of
     // grouped 'trues' or '1' [11111] to determine if a straight exists.
     //
     bool checkStraight(std::vector<std::vector<std::vector<bool>>> &input);
     // Returns true or false depending on if a ace-low straight exists. 
     // Acts as special check for an 'Ace-Low Straight' which is the lowest straight.
     // This is required as it is lowest valued straight, but high enough to be
     // ranked as a kind of straight. Given a score lower than a regular straight,
     // but a score higher than the next lower rank, a three-of-a-kind.
     //
     // Input is a vector of vector of vectors containing booleans (the mask
     // obtained from masking a card vector). Searches for special case for the
     // Check for ace-low straight (Special Case) which is when
     // the first bitset string is '100000000111100' for the hand.
     //
     bool checkAceLowStraight(std::vector<std::vector<std::vector<bool>>> &input);
     // Returns true or false depending on if a flush exists. It sets the suit
     // to the first card in the hand, and scans all remaining cards to see if 
     // they have the same suit. If so, then a flush exists, else no flush exists.
     //
     // Input is a vector of cards to scan.
     //
     bool checkFlush(std::vector <card> &input);
     // Returns true if a royal-flush exists. This is a special case of all cards being
     // an ace, king, queen, jack, and 10 while all having the same suit.
     // This hand can never lose, but can tie. This function requires both
     // checkStraight and checkFlush return true before calling. Since a flush is
     // already checked, it simply checks if all of the cards are the high values.
     //
     // Input is a vector to check for a royal-flush.
     //
     bool checkRoyalFlush(std::vector <card> &input);
     // Returns an integer from applying the algorithm's tie breaking method.
     // Uses bitwise operations to give a definitive value to a hand. Only
     // called if two hands have the same rank.
     //
     // Input is a card vector to determine a definitive hand score based
     // on all cards.
     //
     int getTieBreakScore(std::vector <card> &input);
     // Returns an integer corresponding to a rank in pokerCompare's rank map.
     // Also performs a final check in case an invalid hand rank is used.
     //
     // Input is a string that is one of the ten possible legal poker hands.
     //
     int getRankScore(std::string &input);
};
#endif
