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
 * @file pokerHandsTests.cpp
 *
 * @brief uses Google Test Framework to perform unit tests on program. Files covered
 * are pokerCompare.cpp, util.cpp, and readFile.cpp. Note that print functions are not
 * covered here, they are implemented in PrintTests.cpp.
 *
 * @author Jack Cooper
 * Contact: Jack_cooper01@yahoo.com
 *
 */

#include <gtest/gtest.h>
#include "../Poker-Hands/pokerCompare.h"
#include "../Poker-Hands/readFile.h"

using namespace std;

// Note: printing unit tests will be performed in another file.
// Please see 'printTests.cpp'.
//

//
// Test readFile.h tests
//

char* validFile = "testBasicOriginal.txt";
char* noFile = "";
char* invalidSizeFile = "testBasicWrongSize.txt";
char* nonExistantFile = "FOO.txt";
int emptyFile = 1;
int nonEmpty = 2;

// successful file read.
//
TEST(readFile, readFileValid) {
SUCCEED(readFile(nonEmpty, validFile));
}
// unsuccessful file read - no file
//
TEST(readFile, readFileInvalidFileNone) {
	ASSERT_DEATH(readFile(emptyFile, noFile), "");
}
// unsuccessful file read - wrong file size
//
TEST(readFile, readFileInvalidFileSize) {
	ASSERT_DEATH(readFile(nonEmpty, noFile), "");
}
// unsuccessful file read - nonexistant file
//
TEST(readFile, readFileInvalidFileNoneExistant) {
	ASSERT_DEATH(readFile(nonEmpty, nonExistantFile), "");
}

//
// Test util.h tests
//

// pokerCompare test object for testing
std::vector <std::string> testVectorHands = { "JH 7D 9S 3H 3C", 
											  "QH AD TS JH KC" };
pokerCompare poker(testVectorHands);
// splitString function
//
TEST(util, splitString) {
	std::vector <std::string> correct = { "A", "B" };
	std::vector <std::string> result;
	std::string testString = "A B";
	splitString(testString, result);
	EXPECT_EQ(correct, result);
}
// convertUpper function
//
TEST(util, convertUpper) {
	std::vector <std::string> correct = { "a", "b" };
	convertUpper(correct);
	std::vector <std::string> result = { "A", "B" };
	EXPECT_EQ(correct, result);
}
// leftTrim function
//
TEST(util, leftTrim) {
	std::string toFix = " A";
	std::string correct = "A";
	leftTrim(toFix);
	EXPECT_EQ(correct, toFix);
}
// rightTrim function
//
TEST(util, rightTrim) {
	std::string toFix = "A ";
	std::string correct = "A";
	rightTrim(toFix);
	EXPECT_EQ(correct, toFix);
}
// trim function
//
TEST(util, trim) {
	std::string toFix = " A ";
	std::string correct = "A";
	trim(toFix);
	EXPECT_EQ(correct, toFix);
}
// Create card variables for tests
//
std::string cardOneString = "3S";
card cardOne = poker.getCard(cardOneString);
std::string cardTwoString = "QD";
card cardTwo = poker.getCard(cardTwoString);
// compareCardValue function
//
TEST(util, compareCardValue) {
	ASSERT_TRUE(compareCardValue(cardOne, cardTwo));
}
// printCardVector function - opposite way
//
TEST(util, compareCardValue2) {
	ASSERT_FALSE(compareCardValue(cardTwo, cardOne));
}
// sortByOccurencesAndValue function
//
TEST(util, sortByOccurencesAndValue) {
	std::vector <int> valueTestSort = { 1, 2, 1, 1, 1, };
	sortByOccurencesAndValue(valueTestSort);
	std::vector <int> correctSort = { 1, 1, 1, 1, 2 };
	ASSERT_EQ(correctSort, valueTestSort);
}
// sortHand function
//
TEST(util, sortHand) {
	std::vector <std::string> valueTestSortResult =
		{ "5H", "KH", "2D", "QH", "AC" };
	std::vector <card> result = poker.stringsToCards(valueTestSortResult);
	sortHand(result);
	valueTestSortResult = poker.cardsToStrings(result);
	std::vector <std::string> correctSort = { "AC", "KH", "QH", "5H", "2D" };
	ASSERT_EQ(valueTestSortResult, correctSort);
}
// vectorToString function
//
TEST(util, vectorToString) {
	std::vector <std::string> vector = { "AD" };
	std::string correct = "AD";
	std::string result = vectorToString(vector);
	ASSERT_EQ(correct, result);
}
// getBit function - true
//
TEST(util, getBit) {
	ASSERT_EQ(getBit(true), '1');
}
// getBit function - false
//
TEST(util, getBit2) {
	ASSERT_EQ(getBit(false), '0');
}
// bitsets for Test
//
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
// getLongFromMask function
//
TEST(util, getLongFromMask) {
	testBitset.clear();
	testBitset.push_back(bitSetOne);
	testBitset.push_back(bitSetTwo);
	unsigned long long correct = 1085367510196289536;
	unsigned long long result = 
		getLongFromMask(testBitset[FACE_OCCURENCES_BITSET]);
	ASSERT_EQ(result, correct);
}

// getBinaryFromMaskFirstBitset function
//
TEST(util, getBinaryFromMaskFirstBitset) {
	testBitset.clear();
	testBitset.push_back(bitSetOne);
	testBitset.push_back(bitSetTwo);
	std::bitset<FIRST_BITSET_SIZE> resultOne = 
		getBinaryFromMaskFirstBitset(testBitset[FACE_EXISTS_BITSET]);
	testBitset.clear();
	testBitset.push_back(bitSetOne);
	testBitset.push_back(bitSetTwo);
	std::bitset<FIRST_BITSET_SIZE> resultTwo =
		getBinaryFromMaskFirstBitset(testBitset[FACE_EXISTS_BITSET]);
	ASSERT_EQ(resultOne, resultTwo);
}
// getBinaryFromMaskSecondBitset function
//
TEST(util, getBinaryFromMaskSecondBitset) {
	testBitset.clear();
	testBitset.push_back(bitSetOne);
	testBitset.push_back(bitSetTwo);
	std::bitset<SECOND_BITSET_SIZE> resultOne =
		getBinaryFromMaskSecondBitset(testBitset[FACE_OCCURENCES_BITSET]);
	testBitset.clear();
	testBitset.push_back(bitSetOne);
	testBitset.push_back(bitSetTwo);
	std::bitset<SECOND_BITSET_SIZE> resultTwo =
		getBinaryFromMaskSecondBitset(testBitset[FACE_OCCURENCES_BITSET]);
	ASSERT_EQ(resultOne, resultTwo);
}
// getIntegerVector function
//
TEST(util, getIntegerVector) {
	std::vector <std::string> test = { "JH", "7D", "9S", "3H", "4C" };
	std::vector <card> cardHand = poker.stringsToCards(test);
	std::vector <int> result = getIntegerVector(cardHand);
	std::vector <int> correct = { 11, 7, 9, 3, 4 };
	ASSERT_EQ(result, correct);
}
// toBinary function
//
TEST(util, toBinary) {
	int decimal = 9;
	std::string result = toBinary(decimal);
	std::string correct = "1001";
	ASSERT_EQ(result, correct);
}

//
// Test pokerCompare.h tests
//

// pokerCompare test object for testing
std::vector <std::string> pokerHands = { "JH 7D 9S 3H 3C", 
										 "QH AD TS JH KC" };
pokerCompare objTest(pokerHands);
// setAllHands function
//
TEST(pokerCompare, setAllHands) {
	objTest.setAllHands(pokerHands);
	int correct = 1;
    int pairsUpdate = pokerHands.size() / 2;
	objTest.setNumPairs(pairsUpdate);
	ASSERT_EQ(objTest.getNumPairs(), correct);
}
// setCurrentRound function
//
TEST(pokerCompare, setCurrentRound) {
	std::vector <std::vector <std::string>> round = { {"QD 7D 9S 3H 6C"},
													  {"QH 8D TS JH KC"} };
	objTest.setCurrentRound(round);
	ASSERT_EQ(objTest.getCurrentRound(), round);
}
// setNumPairs function
//
TEST(pokerCompare, setNumPairs) {
	int correct = 4;
	objTest.setNumPairs(correct);
	ASSERT_EQ(objTest.getNumPairs(), correct);
}
// getCurrentRound function
//
TEST(pokerCompare, getCurrentRound) {
	std::vector <std::vector <std::string>> round = { {"QD 7D 9S 3H 6C"}, 
													  {"QH 8D TS JH KC"} };
	objTest.setCurrentRound(round);
	std::vector <std::vector <std::string>> correct = { {"QD 7D 9S 3H 6C"}, 
														{"QH 8D TS JH KC"} };
	std::vector <std::string> correctOne = correct[0];
	std::vector <std::string> correctTwo = correct[0];
	std::vector <std::vector <std::string>> result = objTest.getCurrentRound();
	std::vector <std::string> resultOne = result[0];
	std::vector <std::string> resultTwo = result[0];
	ASSERT_EQ(resultOne, correctOne);
	ASSERT_EQ(resultTwo, correctTwo);
}
// getNumPairs function
//
TEST(pokerCompare, getNumPairs) {
	int set = 8;
	objTest.setNumPairs(set);
	int correct = 8;
	int result = objTest.getNumPairs();
	ASSERT_EQ(result, correct);
}
// validateHand function - correct
//
TEST(pokerCompare, validateHand) {
	std::vector <std::string> hand = { "JH" "7D" "9S" "3H" "3C" };
	SUCCEED(poker.validateHand(hand));
}
// validateHand function - incorrect hand size
//
TEST(pokerCompare, validateHandIncorrectHandSize) {
	std::vector <std::string> hand = { "JH" "7D" "9S" "3H" "3C", "3C" };
	ASSERT_DEATH(poker.validateHand(hand), "");
}
// validateHand function - incorrect card size
//
TEST(pokerCompare, validateHandIncorrectCardSize) {
	std::vector <std::string> hand = { "JH" "7D" "9S" "3H" "555555" };
	ASSERT_DEATH(poker.validateHand(hand), "");
}
// validateHand function - incorrect face
//
TEST(pokerCompare, validateHandIncorrectFace) {
	std::vector <std::string> hand = { "CH" "7D" "9S" "3H" "Y5" };
	ASSERT_DEATH(poker.validateHand(hand), "");
}
// validateHand function - incorrect suit
//
TEST(pokerCompare, validateHandIncorrectSuit) {
	std::vector <std::string> hand = { "6P" "7D" "9S" "3H" "40" };
	ASSERT_DEATH(poker.validateHand(hand), "");
}
// validateHand function - repeated card 5 times
//
TEST(pokerCompare, validateHandRepeatedCardsFive) {
	std::vector <std::string> hand = { "5D" "5C" "5S" "5H" "5D" };
	ASSERT_DEATH(poker.validateHand(hand), "");
}
// getNextPair function
//
TEST(pokerCompare, getNextPair) {
	objTest.setAllHands(pokerHands);
	std::vector <std::vector<std::string>> pair = objTest.getNextPair();
	objTest.setCurrentRound(pair);
	std::vector <std::vector<std::string>> next = objTest.getCurrentRound();
	ASSERT_EQ(pair, objTest.getCurrentRound());
}
// getHandMask function
//
TEST(pokerCompare, getHandMask) {
	testBitset.clear();
	testBitset.push_back(bitSetOne);
	testBitset.push_back(bitSetTwo);
	std::vector<std::vector<std::vector<bool>>> correctMask = testBitset;
	std::vector<std::string> stringHand = {"AC", "AS", "AD", "AH", "KH"};
	std::vector<card> cardHand = objTest.stringsToCards(stringHand);
	std::vector<std::vector<std::vector<bool>>> resultMask = 
		objTest.getHandMask(cardHand);
	ASSERT_EQ(correctMask, resultMask);
}
// compareHands function - 1 wins
//
TEST(pokerCompare, compareHandsOneWin) {
	std::vector<std::string> stringHandOne = { "AC", "AS", "AD", "AH", "KH" };
	std::vector<std::string> stringHandTwo = { "3C", "AS", "AD", "2H", "KH" };
	int winner = 1;
	int result = objTest.compareHands(stringHandOne, stringHandTwo);
	ASSERT_EQ(winner, result);
}
// compareHands function - 2 wins
//
TEST(pokerCompare, compareHandsTwoWin) {
	std::vector<std::string> stringHandTwo = { "AC", "AS", "AD", "AH", "KH" };
	std::vector<std::string> stringHandOne = { "3C", "AS", "AD", "2H", "KH" };
	int winner = 2;
	int result = objTest.compareHands(stringHandOne, stringHandTwo);
	ASSERT_EQ(winner, result);
}
// compareHands function - tie
//
TEST(pokerCompare, compareHandsTie) {
	std::vector<std::string> stringHandOne = { "AC", "AS", "AD", "AH", "KH" };
	std::vector<std::string> stringHandTwo = { "AC", "AS", "AD", "AH", "KH" };
	int winner = 3;
	int result = objTest.compareHands(stringHandOne, stringHandTwo);
	ASSERT_EQ(winner, result);
}
// getHandRank function
//
TEST(pokerCompare, getHandRank) {
	std::vector<std::string> hand = { "AC", "QC", "JC", "TC", "KC" };
	int handRankCorrect = 10;
	int result = objTest.getHandRank(hand);
	ASSERT_EQ(handRankCorrect, result);
}
// getRankFromModulo function
//
TEST(pokerCompare, getRankFromModulo) {
	unsigned long long moduloResult = 5;
	std::string correctResult = "highCard";
	std::string result = objTest.getRankFromModulo(moduloResult);
	ASSERT_EQ(correctResult, result);
}
// compareAll function
//
TEST(pokerCompare, compareAll) {
	SUCCEED(objTest.compareAll());
}
// empty function - true
//
TEST(pokerCompare, emptyTrue) {
	objTest.compareAll();
	ASSERT_TRUE(objTest.empty());
}
// empty function - false
//
TEST(pokerCompare, emptyFalse) {
	objTest.setAllHands(pokerHands);
	ASSERT_FALSE(objTest.empty());
}
// getCard function
//
TEST(pokerCompare, getCard) {
	card correct;
	correct.face = '4';
	correct.suit = 'S';
	correct.value = 4;
	std::string cardToBe = "4S";
	card result = objTest.getCard(cardToBe);
	ASSERT_EQ(correct.face, result.face);
	ASSERT_EQ(correct.suit, result.suit);
	ASSERT_EQ(correct.value, result.value);
}
// getStringFromCard function
//
TEST(pokerCompare, getStringFromCard) {
	card card;
	card.face = '4';
	card.suit = 'S';
	card.value = 4;
	std::string cardToBe = "4S";
	std::string result = objTest.getStringFromCard(card);
	ASSERT_EQ(result, cardToBe);
}
// cardsToStrings function
//
TEST(pokerCompare, cardsToStrings) {
	std::vector <std::string> test = { "JH", "7D", "9S", "3H", "4C" };
	std::vector <card> cardHand = objTest.stringsToCards(test);
	std::vector <std::string> result = objTest.cardsToStrings(cardHand);
	ASSERT_EQ(test, result);
}
// stringsToCards function
//
TEST(pokerCompare, stringsToCards) {
	std::vector <std::string> toConvert = { "3S" };
	card cardOne;
	cardOne.face = '3';
	cardOne.suit = 'S';
	cardOne.value = 3;
	std::vector <card> result = objTest.stringsToCards(toConvert);
	std::vector <std::string> stringHandToCards = {"3S"};
	std::vector <std::string> resultOne = objTest.cardsToStrings(result);
	ASSERT_EQ(resultOne, stringHandToCards);
}
// vectorToString function
//
TEST(pokerCompare, vectorToString) {
	std::string correct = "3S";
	std::vector <std::string> vector = { "3S" };
	std::string result = objTest.vectorToString(vector);
	ASSERT_EQ(correct, result);
}
// countOccurences function
//
TEST(pokerCompare, countOccurences) {
	int correct = 2;
	char key = '3';
	std::vector <std::string> vector = { "3S", "3C", "5S", "2S", "AS"};
	int result = objTest.countOccurences(vector, key);
	ASSERT_EQ(correct, result);
}
// occurs function
//
TEST(pokerCompare, occurs) {
	bool correct = true;
	char key = 'A';
	std::vector <std::string> vector = { "3S", "3C", "5S", "2S", "AS" };
	bool result = objTest.occurs(vector, key);
	ASSERT_EQ(correct, result);
}
// moduloResult function
//
TEST(pokerCompare, moduloResult) {
	testBitset.clear();
	testBitset.push_back(bitSetOne);
	testBitset.push_back(bitSetTwo);
	unsigned long long correct = 1085367510196289536 % 15;
	unsigned long long result = 
		objTest.moduloResult(testBitset[FACE_OCCURENCES_BITSET]);
	ASSERT_EQ(correct, result);
}
// maskHandBinary function
//
TEST(pokerCompare, maskHandBinary) {
	testBitset.clear();
	testBitset.push_back(bitSetOne);
	testBitset.push_back(bitSetTwo);
	std::vector <std::string> hand = { "AS", "AC", "AD", "AH", "KS" };
	std::vector <card> cards = objTest.stringsToCards(hand);
	std::vector<std::vector<std::vector<bool>>> result = 
		objTest.maskHandBinary(cards);
	std::vector<std::vector<std::vector<bool>>> correct = testBitset;
	ASSERT_EQ(correct, result);
}
// checkStraight function - true
//
TEST(pokerCompare, checkStraight) {
	std::vector <std::string> hand = { "2S", "3C", "4D", "5H", "6S" };
	std::vector <card> cards = objTest.stringsToCards(hand);
	std::vector<std::vector<std::vector<bool>>> mask = 
		objTest.getHandMask(cards);
	bool result = objTest.checkStraight(mask);
	bool correct = true;
	ASSERT_EQ(correct, result);
}
// checkStraight function - true for ace-low straight
//
TEST(pokerCompare, checkStraightAceLow) {
	std::vector <std::string> hand = { "AS", "3C", "2D", "4H", "5S" };
	std::vector <card> cards = objTest.stringsToCards(hand);
	std::vector<std::vector<std::vector<bool>>> mask = 
		objTest.getHandMask(cards);
	bool result = objTest.checkStraight(mask);
	bool correct = true;
	ASSERT_EQ(correct, result);
}
// checkStraight function - false
//
TEST(pokerCompare, checkStraightFalse) {
	std::vector <std::string> hand = { "9S", "3C", "2D", "4H", "5S" };
	std::vector <card> cards = objTest.stringsToCards(hand);
	std::vector<std::vector<std::vector<bool>>> mask = 
		objTest.getHandMask(cards);
	bool result = objTest.checkStraight(mask);
	bool correct = false;
	ASSERT_EQ(correct, result);
}
// checkFlush function - true
//
TEST(pokerCompare, checkFlushTrue) {
	std::vector <std::string> hand = { "9C", "3C", "2C", "4C", "5C" };
	std::vector <card> cards = objTest.stringsToCards(hand);
	bool result = objTest.checkFlush(cards);
	bool correct = true;
	ASSERT_EQ(correct, result);
}
// checkStraight function - false
//
TEST(pokerCompare, checkFlushFalse) {
	std::vector <std::string> hand = { "9S", "3C", "2D", "4H", "5S" };
	std::vector <card> cards = objTest.stringsToCards(hand);
	bool result = objTest.checkFlush(cards);
	bool correct = false;
	ASSERT_EQ(correct, result);
}
// checkRoyalFlush function - true
//
TEST(pokerCompare, checkRoyalFlushTrue) {
	std::vector <std::string> hand = { "KD", "QD", "TD", "AD", "JD" };
	std::vector <card> cards = objTest.stringsToCards(hand);
	bool resultFlush = objTest.checkFlush(cards);
	bool correctFlush = true;
	std::vector<std::vector<std::vector<bool>>> mask =
		objTest.getHandMask(cards);
	bool resultStraight = objTest.checkStraight(mask);
	bool correctStraight = true;
	ASSERT_EQ(resultFlush, correctFlush);
	ASSERT_EQ(resultStraight, correctStraight);
}
// checkRoyalFlush function - false
//
TEST(pokerCompare, checkRoyalFlushFalse) {
	std::vector <std::string> hand = { "TD", "QD", "TD", "AD", "JD" };
	std::vector <card> cards = objTest.stringsToCards(hand);
	bool resultFlush = objTest.checkFlush(cards);
	bool correctFlush = true;
	std::vector<std::vector<std::vector<bool>>> mask = 
		objTest.getHandMask(cards);
	bool resultStraight = objTest.checkStraight(mask);
	bool correctStraight = false;
	ASSERT_EQ(resultFlush, correctFlush);
	ASSERT_EQ(resultStraight, correctStraight);
}
// getTieBreakScore function
//
TEST(pokerCompare, getTieBreakScoreTie) {
	std::vector<std::string> stringHandOne = { "AC", "AS", "AD", "AH", "KH" };
	std::vector<std::string> stringHandTwo = { "AC", "AS", "AD", "AH", "KH" };
	std::vector<card> cards = objTest.stringsToCards(stringHandOne);
	std::vector<card> cardsTwo = objTest.stringsToCards(stringHandTwo);
	int result = objTest.getTieBreakScore(cards);
	int resultTwo = objTest.getTieBreakScore(cardsTwo);
	int correct = 978669;
	int correctTwo = 978669;
	ASSERT_EQ(correct, result);
	ASSERT_EQ(correctTwo, resultTwo);
}
// getRankScore function
//
TEST(pokerCompare, getRankScore) {
	std::string rank = "straightFlush";
	int correct = 9;
	int result = objTest.getRankScore(rank);
	ASSERT_EQ(correct, result);
}