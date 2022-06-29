// googleTests.cpp
//

// For GoogleTest unit testing purposes.
//

#include "gtest/gtest.h"
#include <../src/headers/pokerCore.h>
#include <../src/headers/readFile.h>

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
    readFile(nonEmpty, validFile);
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

// pokerCore test object for testing
std::vector <std::string> testVectorHands = { "JH 7D 9S 3H 3C", 
                                              "QH AD TS JH KC" };
pokerCore poker(testVectorHands);
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
// trim function -- NEEDS FIXING
//
/*
TEST(util, trim) {
    std::string toFix = " A ";
    std::string correct = "A";
	trim(toFix);
    EXPECT_EQ(correct, toFix);
}
*/
// Create card variables for tests
//
std::string cardOneString = "3S";
card cardOne = poker.getCard(cardOneString);
std::string cardTwoString = "QD";
card cardTwo = poker.getCard(cardTwoString);
// compareCardMagnitude function
//
TEST(util, compareCardMagnitude) {
    ASSERT_TRUE(compareCardMagnitude(cardOne, cardTwo));
}
// printCardVector function - opposite way
//
TEST(util, compareCardMagnitude2) {
    ASSERT_FALSE(compareCardMagnitude(cardTwo, cardOne));
}
// sortByOccurencesThenByMagnitude function
//
TEST(util, sortByOccurencesThenByMagnitude) {
    std::vector <int> magnitudeTestSort = { 1, 2, 1, 1, 1, };
    sortByOccurencesThenByMagnitude(magnitudeTestSort);
    std::vector <int> correctSort = { 1, 1, 1, 1, 2 };
    ASSERT_EQ(correctSort, magnitudeTestSort);
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
        getLongFromMask(testBitset[VALUE_OCCURENCES_BITSET]);
    ASSERT_EQ(result, correct);
}

// getBinaryFromMaskFirstBitset function
//
TEST(util, getBinaryFromMaskFirstBitset) {
    testBitset.clear();
    testBitset.push_back(bitSetOne);
    testBitset.push_back(bitSetTwo);
    std::bitset<FIRST_BITSET_SIZE> resultOne = 
        getBinaryFromMaskFirstBitset(testBitset[VALUE_EXISTS_BITSET]);
    testBitset.clear();
    testBitset.push_back(bitSetOne);
    testBitset.push_back(bitSetTwo);
    std::bitset<FIRST_BITSET_SIZE> resultTwo =
        getBinaryFromMaskFirstBitset(testBitset[VALUE_EXISTS_BITSET]);
    ASSERT_EQ(resultOne, resultTwo);
}
// getBinaryFromMaskSecondBitset function
//
TEST(util, getBinaryFromMaskSecondBitset) {
    testBitset.clear();
    testBitset.push_back(bitSetOne);
    testBitset.push_back(bitSetTwo);
    std::bitset<SECOND_BITSET_SIZE> resultOne =
        getBinaryFromMaskSecondBitset(testBitset[VALUE_OCCURENCES_BITSET]);
    testBitset.clear();
    testBitset.push_back(bitSetOne);
    testBitset.push_back(bitSetTwo);
    std::bitset<SECOND_BITSET_SIZE> resultTwo =
        getBinaryFromMaskSecondBitset(testBitset[VALUE_OCCURENCES_BITSET]);
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
// Test pokerCore.h tests
//

// pokerCore test object for testing
std::vector <std::string> pokerHands = { "JH 7D 9S 3H 3C", 
                                         "QH AD TS JH KC" };
pokerCore objTest(pokerHands);
// setAllHands function
//
TEST(pokerCore, setAllHands) {
    objTest.setAllHands(pokerHands);
    int correct = 1;
    size_t pairsUpdate = pokerHands.size() / 2;
    int size = (int) pairsUpdate;
    objTest.setNumPairs(size);
    ASSERT_EQ(objTest.getNumPairs(), correct);
}
// setCurrentRound function
//
TEST(pokerCore, setCurrentRound) {
    std::vector <std::vector <std::string>> round = { {"QD 7D 9S 3H 6C"},
                                                      {"QH 8D TS JH KC"} };
    objTest.setCurrentRound(round);
    ASSERT_EQ(objTest.getCurrentRound(), round);
}
// setNumPairs function
//
TEST(pokerCore, setNumPairs) {
    int correct = 4;
    objTest.setNumPairs(correct);
    ASSERT_EQ(objTest.getNumPairs(), correct);
}
// getCurrentRound function
//
TEST(pokerCore, getCurrentRound) {
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
TEST(pokerCore, getNumPairs) {
    int set = 8;
    objTest.setNumPairs(set);
    int correct = 8;
    int result = objTest.getNumPairs();
    ASSERT_EQ(result, correct);
}
// validateHand function - correct
//
TEST(pokerCore, validateHand) {
    std::vector <std::string> hand = { "JH", "7D", "9S", "3H", "3C" };
    poker.validateHand(hand);
}
// validateHand function - incorrect hand size
//
TEST(pokerCore, validateHandIncorrectHandSize) {
    std::vector <std::string> hand = { "JH" "7D" "9S" "3H" "3C", "3C" };
    ASSERT_DEATH(poker.validateHand(hand), "");
}
// validateHand function - incorrect card size
//
TEST(pokerCore, validateHandIncorrectCardSize) {
    std::vector <std::string> hand = { "JH" "7D" "9S" "3H" "555555" };
    ASSERT_DEATH(poker.validateHand(hand), "");
}
// validateHand function - incorrect VALUE
//
TEST(pokerCore, validateHandIncorrectFace) {
    std::vector <std::string> hand = { "CH" "7D" "9S" "3H" "Y5" };
    ASSERT_DEATH(poker.validateHand(hand), "");
}
// validateHand function - incorrect suit
//
TEST(pokerCore, validateHandIncorrectSuit) {
    std::vector <std::string> hand = { "6P" "7D" "9S" "3H" "40" };
    ASSERT_DEATH(poker.validateHand(hand), "");
}
// validateHand function - repeated card 5 times
//
TEST(pokerCore, validateHandRepeatedCardsFive) {
    std::vector <std::string> hand = { "5D" "5C" "5S" "5H" "5D" };
    ASSERT_DEATH(poker.validateHand(hand), "");
}
// getNextPair function
//
TEST(pokerCore, getNextPair) {
    objTest.setAllHands(pokerHands);
    std::vector <std::vector<std::string>> pair = objTest.getNextPair();
    objTest.setCurrentRound(pair);
    std::vector <std::vector<std::string>> next = objTest.getCurrentRound();
    ASSERT_EQ(pair, objTest.getCurrentRound());
}
// getHandMask function
//
TEST(pokerCore, getHandMask) {
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
TEST(pokerCore, compareHandsOneWin) {
    std::vector<std::string> stringHandOne = { "AC", "AS", "AD", "AH", "KH" };
    std::vector<std::string> stringHandTwo = { "3C", "AS", "AD", "2H", "KH" };
    int winner = 1;
    int result = objTest.compareHands(stringHandOne, stringHandTwo);
    ASSERT_EQ(winner, result);
}
// compareHands function - 2 wins
//
TEST(pokerCore, compareHandsTwoWin) {
    std::vector<std::string> stringHandTwo = { "AC", "AS", "AD", "AH", "KH" };
    std::vector<std::string> stringHandOne = { "3C", "AS", "AD", "2H", "KH" };
    int winner = 2;
    int result = objTest.compareHands(stringHandOne, stringHandTwo);
    ASSERT_EQ(winner, result);
}
// compareHands function - tie
//
TEST(pokerCore, compareHandsTie) {
    std::vector<std::string> stringHandOne = { "AC", "AS", "AD", "AH", "KH" };
    std::vector<std::string> stringHandTwo = { "AC", "AS", "AD", "AH", "KH" };
    int winner = 3;
    int result = objTest.compareHands(stringHandOne, stringHandTwo);
    ASSERT_EQ(winner, result);
}
// getHandRank function
//
TEST(pokerCore, getHandRank) {
    std::vector<std::string> hand = { "AC", "QC", "JC", "TC", "KC" };
    int handRankCorrect = 10;
    int result = objTest.getHandRank(hand);
    ASSERT_EQ(handRankCorrect, result);
}
// getRankFromModulo function
//
TEST(pokerCore, getRankFromModulo) {
    unsigned long long moduloResult = 5;
    std::string correctResult = "highCard";
    std::string result = objTest.getRankFromModulo(moduloResult);
    ASSERT_EQ(correctResult, result);
}
// compareAll function
//
TEST(pokerCore, compareAll) {
    objTest.compareAll();
}
// empty function - true
//
TEST(pokerCore, emptyTrue) {
    objTest.compareAll();
    ASSERT_TRUE(objTest.empty());
}
// empty function - false
//
TEST(pokerCore, emptyFalse) {
    objTest.setAllHands(pokerHands);
    ASSERT_FALSE(objTest.empty());
}
// getCard function
//
TEST(pokerCore, getCard) {
    card correct;
    correct.value = '4';
    correct.suit = 'S';
    correct.magnitude = 4;
    std::string cardToBe = "4S";
    card result = objTest.getCard(cardToBe);
    ASSERT_EQ(correct.value, result.value);
    ASSERT_EQ(correct.suit, result.suit);
    ASSERT_EQ(correct.magnitude, result.magnitude);
}
// getStringFromCard function
//
TEST(pokerCore, getStringFromCard) {
    card card;
    card.value = '4';
    card.suit = 'S';
    card.magnitude = 4;
    std::string cardToBe = "4S";
    std::string result = objTest.getStringFromCard(card);
    ASSERT_EQ(result, cardToBe);
}
// cardsToStrings function
//
TEST(pokerCore, cardsToStrings) {
    std::vector <std::string> test = { "JH", "7D", "9S", "3H", "4C" };
    std::vector <card> cardHand = objTest.stringsToCards(test);
    std::vector <std::string> result = objTest.cardsToStrings(cardHand);
    ASSERT_EQ(test, result);
}
// stringsToCards function
//
TEST(pokerCore, stringsToCards) {
    std::vector <std::string> toConvert = { "3S" };
    card cardOne;
    cardOne.value = '3';
    cardOne.suit = 'S';
    cardOne.magnitude = 3;
    std::vector <card> result = objTest.stringsToCards(toConvert);
    std::vector <std::string> stringHandToCards = {"3S"};
    std::vector <std::string> resultOne = objTest.cardsToStrings(result);
    ASSERT_EQ(resultOne, stringHandToCards);
}
// vectorToString function
//
TEST(pokerCore, vectorToString) {
    std::string correct = "3S";
    std::vector <std::string> vector = { "3S" };
    std::string result = objTest.vectorToString(vector);
    ASSERT_EQ(correct, result);
}
// countOccurences function
//
TEST(pokerCore, countOccurences) {
    int correct = 2;
    char key = '3';
    std::vector <std::string> vector = { "3S", "3C", "5S", "2S", "AS"};
    int result = objTest.countOccurences(vector, key);
    ASSERT_EQ(correct, result);
}
// occurs function
//
TEST(pokerCore, occurs) {
    bool correct = true;
    char key = 'A';
    std::vector <std::string> vector = { "3S", "3C", "5S", "2S", "AS" };
    bool result = objTest.occurs(vector, key);
    ASSERT_EQ(correct, result);
}
// moduloResult function
//
TEST(pokerCore, moduloResult) {
    testBitset.clear();
    testBitset.push_back(bitSetOne);
    testBitset.push_back(bitSetTwo);
    unsigned long long correct = 1085367510196289536 % 15;
    unsigned long long result = 
        objTest.moduloResult(testBitset[VALUE_OCCURENCES_BITSET]);
    ASSERT_EQ(correct, result);
}
// maskHandBinary function
//
TEST(pokerCore, maskHandBinary) {
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
TEST(pokerCore, checkStraight) {
    std::vector <std::string> hand = { "2S", "3C", "4D", "5H", "6S" };
    std::vector <card> cards = objTest.stringsToCards(hand);
    std::vector<std::vector<std::vector<bool>>> mask = 
        objTest.getHandMask(cards);
    bool result = objTest.checkStraight(mask);
    bool correct = true;
    ASSERT_EQ(correct, result);
}
// checkStraight function - false
//
TEST(pokerCore, checkStraightFalse) {
    std::vector <std::string> hand = { "9S", "3C", "2D", "4H", "5S" };
    std::vector <card> cards = objTest.stringsToCards(hand);
    std::vector<std::vector<std::vector<bool>>> mask = 
        objTest.getHandMask(cards);
    bool result = objTest.checkStraight(mask);
    bool correct = false;
    ASSERT_EQ(correct, result);
}
// checkAceLowStraight function - true
//
TEST(pokerCore, checkAceLowStraightTrue) {
    std::vector <std::string> hand = { "AS", "3C", "2D", "4H", "5S" };
    std::vector <card> cards = objTest.stringsToCards(hand);
    std::vector<std::vector<std::vector<bool>>> mask =
        objTest.getHandMask(cards);
    bool result = objTest.checkAceLowStraight(mask);
    bool correct = true;
    ASSERT_EQ(correct, result);
}
// checkAceLowStraight function - false
//
TEST(pokerCore, checkAceLowStraightFalse) {
    std::vector <std::string> hand = { "AS", "KC", "QD", "JH", "TS" };
    std::vector <card> cards = objTest.stringsToCards(hand);
    std::vector<std::vector<std::vector<bool>>> mask =
        objTest.getHandMask(cards);
    bool result = objTest.checkAceLowStraight(mask);
    bool correct = false;
    ASSERT_EQ(correct, result);
}
// checkFlush function - true
//
TEST(pokerCore, checkFlushTrue) {
    std::vector <std::string> hand = { "9C", "3C", "2C", "4C", "5C" };
    std::vector <card> cards = objTest.stringsToCards(hand);
    bool result = objTest.checkFlush(cards);
    bool correct = true;
    ASSERT_EQ(correct, result);
}
// checkStraight function - false
//
TEST(pokerCore, checkFlushFalse) {
    std::vector <std::string> hand = { "9S", "3C", "2D", "4H", "5S" };
    std::vector <card> cards = objTest.stringsToCards(hand);
    bool result = objTest.checkFlush(cards);
    bool correct = false;
    ASSERT_EQ(correct, result);
}
// checkRoyalFlush function - true
//
TEST(pokerCore, checkRoyalFlushTrue) {
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
TEST(pokerCore, checkRoyalFlushFalse) {
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
// getDeepEvaluationScore function
//
TEST(pokerCore, getDeepEvaluationScore) {
    std::vector<std::string> stringHandOne = { "AC", "AS", "AD", "AH", "KH" };
    std::vector<std::string> stringHandTwo = { "AC", "AS", "AD", "AH", "KH" };
    std::vector<card> cards = objTest.stringsToCards(stringHandOne);
    std::vector<card> cardsTwo = objTest.stringsToCards(stringHandTwo);
    int result = objTest.getDeepEvaluationScore(cards);
    int resultTwo = objTest.getDeepEvaluationScore(cardsTwo);
    int correct = 978669;
    int correctTwo = 978669;
    ASSERT_EQ(correct, result);
    ASSERT_EQ(correctTwo, resultTwo);
}
// getRankScore function
//
TEST(pokerCore, getRankScore) {
    std::string rank = "straightFlush";
    int correct = 9;
    int result = objTest.getRankScore(rank);
    ASSERT_EQ(correct, result);
}
