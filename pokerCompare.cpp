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
#include "pokerCompare.h"

using namespace std;
pokerCompare::pokerCompare(vector <string> inputHands) {
    setAllHands(inputHands);
    faces = {"A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2"};
    suits = {"S", "D", "C", "H"};
    ranks = { {"highCard", 1}, {"onePair", 2}, {"twoPair", 3},
              {"threeKind", 4}, {"straight", 5}, {"flush", 6},
              {"fullHouse", 7}, {"fourKind", 8}, 
              {"straightFlush", 9}, {"royalFlush", 10}
            };
}
void pokerCompare::setAllHands(vector <string> &fileInputHands) {
    allHands = fileInputHands;
    reverse(allHands.begin(), allHands.end());
}
void pokerCompare::setCurrentRound(vector <vector<string>> pair) {
    currentRound.clear();
    currentRound.push_back(pair.at(VECTOR_POS_ONE));
    currentRound.push_back(pair.at(VECTOR_POS_TWO));
}
void pokerCompare::setNumPairs(int &setPairNum) {
    numOfPairs = setPairNum;
}
void pokerCompare::setFaces(vector<string> &newFaces) {
    faces = newFaces;
}
void pokerCompare::setSuits(vector<string> &newSuits){
    suits = newSuits;
}
void pokerCompare::setRanks(map<string, int> &newRanks) {
    ranks = newRanks;
}
vector<string> pokerCompare::getFaces() {
    return faces;
}
vector<string> pokerCompare::getSuits() {
    return suits;
}
map<string, int> pokerCompare::getRanks() {
    return ranks;
}
vector <vector<string>> pokerCompare::getCurrentRound() {
    return currentRound;
}
vector <string> pokerCompare::getAllHands() {
    return allHands;
}
int pokerCompare::getNumPairs() {
    return numOfPairs;
}
void pokerCompare::validateHand(vector <string> &hand)
{
    convertUpper(hand);
    string key;
    if(hand.size() != CORRECT_HAND_SIZE){
        cout << "ERROR: Invalid hand - Incorrect hand size!" << endl;
        exit(EXIT_FAILURE);
    }
    for (auto& element : hand) {
        if(element.size() != CARD_SIZE) {
            cout << "ERROR: Invalid hand - Found invalid card size!" << endl;
            exit(EXIT_FAILURE);
        }
        key = element[FACE];
        if(find(faces.begin(), faces.end(), key) == faces.end()){
            cout << "ERROR: Invalid hand - Found invalid face value!" << endl;
            exit(EXIT_FAILURE);
        }
        key = element[SUIT]; 
        if(find(suits.begin(), suits.end(), key) == suits.end()){
            cout << "ERROR: Invalid hand - Found invalid suit value!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    string fiveFaceCheck = vectorToString(hand);
    char faceToCheck = fiveFaceCheck[BEGINNING];
    int countFiveCheck = count(fiveFaceCheck.begin(),
                               fiveFaceCheck.end(), faceToCheck);
    if(countFiveCheck == FIVEOFKINDCHECK){
        cout << "ERROR: Invalid hand - cannot have five of the same face value!"
          << endl;
        exit(EXIT_FAILURE);
    }
}
vector <vector<string>> pokerCompare::getNextPair() {
    vector <vector<string>> nextPairVector;
    vector <string> firstHandVector;
    vector <string> secondHandVector;
    splitString(allHands.back(), firstHandVector);
    allHands.pop_back();
    splitString(allHands.back(), secondHandVector);
    allHands.pop_back();
    validateHand(firstHandVector);
    validateHand(secondHandVector);
    nextPairVector.push_back(firstHandVector);
    nextPairVector.push_back(secondHandVector);
    return nextPairVector;
}
vector<vector<vector<bool>>> pokerCompare::getHandMask(vector <card> &inputHand) {
    vector<vector<vector<bool>>> handMasked = maskHandBinary(inputHand);
    return handMasked;
}
int pokerCompare::compareHands(vector <string> &handOne, 
                               vector <string> &handTwo) {
    int firstHandScore = getHandRank(handOne);
    int secondHandScore = getHandRank(handTwo);
    if(firstHandScore > secondHandScore){
        return HAND_ONE;
    } else if(firstHandScore < secondHandScore){
        return HAND_TWO;
    } else {
        vector<card> cardsVectorOne = stringsToCards(handOne);
        vector<card> cardsVectorTwo = stringsToCards(handTwo);
        int tieBreakFirstScore = getTieBreakScore(cardsVectorOne);
        int tieBreakSecondScore = getTieBreakScore(cardsVectorTwo);
        if(tieBreakFirstScore > tieBreakSecondScore){
            return HAND_ONE;
        } else if(tieBreakFirstScore < tieBreakSecondScore){
            return HAND_TWO;
        } else {
            return TIE;
        }
    }
}
int pokerCompare::getHandRank(vector <string> &hand) {
    string rank;
    unsigned long long moduloScore;
    vector<card> cardsVector = stringsToCards(hand);
    sortHand(cardsVector);
    vector<vector<vector<bool>>> handMask = getHandMask(cardsVector);
    if(checkStraight(handMask) && checkFlush(cardsVector)){
        if(checkRoyalFlush(cardsVector)){
            rank = "royalFlush";
            return getRankScore(rank);
        } else {
            rank = "straightFlush";
            return getRankScore(rank);
        }
    } else if(checkFlush(cardsVector)){
        rank = "flush";
        return getRankScore(rank);
    } else if(checkStraight(handMask)){
        rank = "straight";
        return getRankScore(rank);;
    } else {
        moduloScore = (moduloResult(handMask[FACE_OCCURENCES_BITSET]));
        string rankScored = getRankFromModulo(moduloScore);
        return getRankScore(rankScored);
    }
}
string pokerCompare::getRankFromModulo(unsigned long long &moduloScore) {
    if(moduloScore == MODULO_FOUR_KIND){
        return "fourKind";
    } else if(moduloScore == MODULO_FULL_HOUSE){
        return "fullHouse";
    } else if(moduloScore == MODULO_THREE_KIND){
        return "threeKind";
    } else if(moduloScore == MODULO_TWO_PAIR){
        return "twoPair";
    } else if(moduloScore == MODULO_ONE_PAIR){
        return "onePair";
    } else if (moduloScore == MODULO_HIGH_CARD){
        return "highCard";
    } else {
        return "ERROR";
    }
}
void pokerCompare::compareAll() {
    int currentRound = START;
    int result;
    while (!(this->empty())) {
        cout << "Round " << currentRound << ":" << endl;
        this->setCurrentRound(this->getNextPair());
        vector <vector<string>> currentPair = this->getCurrentRound();
        cout << "Hand One: ";
        printVector(currentPair.at(VECTOR_POS_ONE));
        cout << "Hand Two: ";
        printVector(currentPair.at(VECTOR_POS_TWO));
        result = compareHands(currentPair.at(VECTOR_POS_ONE),
                              currentPair.at(VECTOR_POS_TWO));
        printWinner(result);
        currentRound++;
    }
}
bool pokerCompare::empty() {
    if(allHands.size() == 0){
        return true;
    } else {
        return false;
    }
}
void pokerCompare::printWinner(int &result) {
    if(result == HAND_ONE){
        cout << "Player 1/Hand 1 Wins!" << endl;
    } else if(result == HAND_TWO){
        cout << "Player 2/Hand 2 Wins!" << endl;
    } else {
        cout << "Tie!" << endl;
    }
}
void pokerCompare::print2DBoolVector(vector<vector<bool>> &vector) {
    for (int i = 0; i < vector.size(); i++)
    {
        for (int j = 0; j < vector[i].size(); j++)
        {
            cout << vector[i][j];
        }
    }
    cout << endl;
}
card pokerCompare::getCard(string &input) {
    card conversion;
    conversion.face = input[FACE];
    conversion.suit = input[SUIT];
    switch(conversion.face) {
        case 'A' :
            conversion.value = ACE;
            break;
        case 'K' :
            conversion.value = KING;
            break;
        case 'Q' :
            conversion.value = QUEEN;
            break;
        case 'J' :
            conversion.value = JACK;
            break;
        case 'T' :
            conversion.value = TEN;
            break;
        default:
            conversion.value = conversion.face - '0';
            break;
    }
    return conversion;
}
string pokerCompare::getStringFromCard(card &input) {
    string cardString;
    cardString.push_back(input.face);
    cardString.push_back(input.suit);
    return cardString;
}
vector <string> pokerCompare::cardsToStrings(vector<card> &cards) {
    vector<string> stringHand;
    string cardToAdd;
    for (auto i : cards)
    {
        cardToAdd = getStringFromCard(i);
        stringHand.push_back(cardToAdd);
    }
    return stringHand;
}
vector<card> pokerCompare::stringsToCards(vector <string> &vector) {
    card cardToAdd;
    std::vector<card> cards;
    for (auto i : vector)
    {
        cardToAdd = getCard(i);
        cards.push_back(cardToAdd);
    }
    return cards;
}
string pokerCompare::vectorToString(vector<string> &vector) {
    string result;
    for (std::vector<std::string>::const_iterator iter = vector.begin(); 
         iter != vector.end(); ++iter) {
        result += *iter;
    }
    return result;
}
int pokerCompare::countOccurences(vector <string> &vector, char &key) {
    string hand = vectorToString(vector);
    int occurs = std::count(hand.begin(), hand.end(), key);
    return occurs;
}
bool pokerCompare::occurs(vector <string> &vector, char &key) {
    for(int element = 0; element < vector.size(); element++) {
        for(int stringCheck = 0; stringCheck < vector[element].size(); 
            stringCheck++) {
            if(vector[element][FACE] == key) {
                return true;
            }
        }
    }
    return false;
}
unsigned long long pokerCompare::moduloResult(vector <vector<bool>> &input) {
    return getLongFromMask(input) % MODULO_FOR_ALGORITHM;
}
vector<vector<vector<bool>>> pokerCompare::maskHandBinary(vector <card> &input) {
    int faceCheckPosition = 0;
    int occurences;
    bool exists;
    char faceToCheck;
    vector<std::string> stringCardVector = cardsToStrings(input);
    std::vector <std::vector<bool>> handFaceValuesOfHand {
        {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, 
        {0}, {0},
    };
    std::vector <std::vector<bool>> handCountOfFaceValues {
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
        {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
    };
    for (int faceValue = 0; faceValue < NUMBER_OF_CARDS; 
         faceValue++)
    {
        faceToCheck = facesPossible[faceCheckPosition];
        exists = occurs(stringCardVector, faceToCheck);
        if (exists == true) {
            handFaceValuesOfHand[faceValue].at(BEGINNING) = true;
        }
        faceCheckPosition++;
    }
    faceCheckPosition = 0;
    for (int nibble = 0; nibble < NUMBER_OF_CARDS; nibble++)
    {
        faceToCheck = facesPossible[faceCheckPosition];
        occurences = countOccurences(stringCardVector, faceToCheck);
        for (int bits = NIBBLE; bits >= 0; bits--)
        {
            if(occurences != 0) {
                handCountOfFaceValues[nibble][bits] = true;
                occurences--;
            } else {
                handCountOfFaceValues[nibble][bits] = false;
            }
        }
        faceCheckPosition++;
    }
    vector<vector<vector<bool>>> maskedResult;
    maskedResult.push_back(handFaceValuesOfHand);
    maskedResult.push_back(handCountOfFaceValues);
    return maskedResult;
}
bool pokerCompare::checkStraight(vector<vector<vector<bool>>> &input) {
    bitset<FIRST_BITSET_SIZE> firstBitset = 
        getBinaryFromMaskFirstBitset(input[FACE_EXISTS_BITSET]);
    bitset<SECOND_BITSET_SIZE> secondBitset = 
        getBinaryFromMaskSecondBitset(input[FACE_EXISTS_BITSET]);
    string aceLowStringCheck = firstBitset.to_string();
    // Check for ace-low straight (Special Case).
    // Check first bitset string for '100000000111100' as this is that hand.
    if(aceLowStringCheck[LOW_ACE_STRAIGHT_POS_ONE] == '1'){
        if(aceLowStringCheck[LOW_ACE_STRAIGHT_POS_TWO] == '1'){
            if(aceLowStringCheck[LOW_ACE_STRAIGHT_POS_THREE] == '1'){
                if(aceLowStringCheck[LOW_ACE_STRAIGHT_POS_FOUR] == '1'){
                    if(aceLowStringCheck[LOW_ACE_STRAIGHT_POS_FIVE] == '1'){
                        return true;
                    }  
                }   
            }
        }
    }
    // Check for straight.
    long divisor = (secondBitset.to_ulong() & -secondBitset.to_ulong());
    long result = secondBitset.to_ulong() / divisor;
    if (result != STRAIGHT_FOUND){
        return false;
    }
    return true;
}
bool pokerCompare::checkFlush(vector <card> &input) {
    char suitToCheck = input[BEGINNING].suit;
    for(auto& i : input) {
        if(i.suit != suitToCheck){
            return false;
        }
    }
    return true;
}
bool pokerCompare::checkRoyalFlush(vector <card> &input) {
    int faceCheck = 0;
    char faceToCheck;
    for(auto& i : input) {
        faceToCheck = facesPossible[faceCheck];
        if(i.face != faceToCheck){
            return false;
        }
        faceCheck++;
    }
    return true;
}
int pokerCompare::getTieBreakScore(vector <card> &input) {
    int score;
    vector <int> handFacesInts = getIntegerVector(input);
    sort(handFacesInts.begin(), handFacesInts.end());
    sortByOccurencesAndValue(handFacesInts);
    reverse(handFacesInts.begin(), handFacesInts.end());
    int first = handFacesInts.back();
    handFacesInts.pop_back();
    int second = handFacesInts.back();
    handFacesInts.pop_back();
    int third = handFacesInts.back();
    handFacesInts.pop_back();
    int forth = handFacesInts.back();
    handFacesInts.pop_back();
    int fifth = handFacesInts.back();
    handFacesInts.pop_back();
    int firstShift;
    int secondShift;
    int thirdShift;
    int forthShift;
    int fifthShift;
    firstShift = first << 16;
    secondShift = second << 12;
    thirdShift = third << 8;
    forthShift = forth << 4;
    fifthShift = fifth << 0;
    int firstBinaryNumber =  stoi(toBinary(firstShift), 0, 2);
    int secondBinaryNumber =  stoi(toBinary(secondShift), 0, 2);
    int thirdBinaryNumber =  stoi(toBinary(thirdShift), 0, 2);
    int forthBinaryNumber =  stoi(toBinary(forthShift), 0, 2);
    int fifthBinaryNumber =  stoi(toBinary(fifthShift), 0, 2);
    score = firstBinaryNumber + secondBinaryNumber + thirdBinaryNumber +
            forthBinaryNumber + fifthBinaryNumber;
    return score;
}
int pokerCompare::getRankScore(string &input) {
    int score;
    auto it = ranks.find(input);
    if(it == ranks.end()) {
        cout << "ERROR: Rank not found!" << endl;
        exit(EXIT_FAILURE);
    } else {
        score = it->second;
        return score;
    }
}