// pokerCore.cpp
//

#include <../src/headers/pokerCore.h>

using namespace std;

pokerCore::pokerCore(vector <string> inputHands) {
	setAllHands(inputHands);
	values = { "A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2" };
	suits = { "S", "D", "C", "H" };
	ranks = { {"highCard", 0}, {"onePair", 1}, {"twoPair", 2},
			     {"threeKind", 3},  {"aceLowStraight", 4}, {"straight", 5}, {"flush", 6},
			     {"fullHouse", 7}, {"fourKind", 8}, {"straightFlush", 9}, {"royalFlush", 10}
	};
}
void pokerCore::setAllHands(vector <string>& fileInputHands) {
	allHands = fileInputHands;
	// Reverse to start at the beginning of the inputted file.
	//
	reverse(allHands.begin(), allHands.end());
}
void pokerCore::setCurrentRound(vector <vector<string>> pair) {
	// Flush out previous round.
	//
	currentRound.clear();
	// Populate next round.
	//
	currentRound.push_back(pair.at(VECTOR_POS_ONE));
	currentRound.push_back(pair.at(VECTOR_POS_TWO));
}
void pokerCore::setNumPairs(int& setPairNum) {
	numOfPairs = setPairNum;
}
vector <vector<string>> pokerCore::getCurrentRound() {
	return currentRound;
}
int pokerCore::getNumPairs() {
	return numOfPairs;
}
void pokerCore::validateHand(vector <string>& hand)
{
	convertUpper(hand);
	string key;
	// Check hand size.
	//
	if (hand.size() != CORRECT_HAND_SIZE) {
		cout << "ERROR: Invalid hand - Incorrect hand size!" << endl;
		exit(EXIT_FAILURE);
	}
	for (auto& element : hand) {
		// Check card size.
		//
		if (element.size() != CARD_SIZE) {
			cout << "ERROR: Invalid hand - Found invalid card size!" << endl;
			exit(EXIT_FAILURE);
		}
		key = element[VALUE];
		// Check for invalid values.
		//
		if (find(values.begin(), values.end(), key) == values.end()) {
			cout << "ERROR: Invalid hand - Found invalid card value!" << endl;
			exit(EXIT_FAILURE);
		}
		key = element[SUIT];
		// Check for invalid suits.
		//
		if (find(suits.begin(), suits.end(), key) == suits.end()) {
			cout << "ERROR: Invalid hand - Found invalid suit value!" << endl;
			exit(EXIT_FAILURE);
		}
	}
	string fiveValueCheck = vectorToString(hand);
	char valueToCheck = fiveValueCheck[FIRST_INDEX];
	int countFiveCheck = (int)count(fiveValueCheck.begin(),
		fiveValueCheck.end(), valueToCheck);
	// Check for five of the same value.
	//
	if (countFiveCheck == FIVEOFKINDCHECK) {
		cout << "ERROR: Invalid hand - cannot have five of the same card value!"
			<< endl;
		exit(EXIT_FAILURE);
	}
}
vector <vector<string>> pokerCore::getNextPair() {
	vector <vector<string>> nextPairVector;
	vector <string> firstHandVector;
	vector <string> secondHandVector;
	// Grab next two hands from allHands.
	//
	splitString(allHands.back(), firstHandVector);
	allHands.pop_back();
	splitString(allHands.back(), secondHandVector);
	allHands.pop_back();
	// Perform validation on both hands.
	//
	validateHand(firstHandVector);
	validateHand(secondHandVector);
	nextPairVector.push_back(firstHandVector);
	nextPairVector.push_back(secondHandVector);
	return nextPairVector;
}
vector<vector<vector<bool>>> pokerCore::getHandMask(vector <card>& inputHand) {
	vector<vector<vector<bool>>> handMasked = maskHandBinary(inputHand);
	return handMasked;
}
int pokerCore::compareHands(vector <string>& handOne,
	vector <string>& handTwo) {
	int firstHandScore = getHandRank(handOne);
	int secondHandScore = getHandRank(handTwo);
	if (firstHandScore > secondHandScore) {
		// Hand One is winner - no tie found.
		//
		return HAND_ONE;
	}
	else if (firstHandScore < secondHandScore) {
		// Hand Two is winner - no tie found.
		//
		return HAND_TWO;
	}
	else {
		// Tie found as ranks are the same. 
		// Determine actual value of hands
		// using algorithm's method. Then compare.
		//
		vector<card> cardsVectorOne = stringsToCards(handOne);
		vector<card> cardsVectorTwo = stringsToCards(handTwo);
		int tieBreakFirstScore = getDeepEvaluationScore(cardsVectorOne);
		int tieBreakSecondScore = getDeepEvaluationScore(cardsVectorTwo);
		if (tieBreakFirstScore > tieBreakSecondScore) {
			// Hand One is winner of the tie.
			//
			return HAND_ONE;
		}
		else if (tieBreakFirstScore < tieBreakSecondScore) {
			// Hand Two is winner of the tie.
			//
			return HAND_TWO;
		}
		else {
			// Tie. Both hands are exactly the same.
			//
			return TIE;
		}
	}
}
int pokerCore::getHandRank(vector <string>& hand) {
	string rank;
	unsigned long long moduloScore;
	vector<card> cardsVector = stringsToCards(hand);
	sortHand(cardsVector);
	vector<vector<vector<bool>>> handMask = getHandMask(cardsVector);
	// Check highest valued hands first, and
	// rely on modulo division method last.
	//
	if (checkStraight(handMask) && checkFlush(cardsVector)) {
		if (checkRoyalFlush(cardsVector)) {
			// Royal-Flush Found.
			//
			rank = "royalFlush";
			return getRankScore(rank);
		}
		else {
			// Straight-Flush Found.
			//
			rank = "straightFlush";
			return getRankScore(rank);
		}
	}
	else if (checkFlush(cardsVector)) {
		// Flush Found.
		//
		rank = "flush";
		return getRankScore(rank);
	}
	else if (checkStraight(handMask)) {
		// Straight Found.
		//
		rank = "straight";
		return getRankScore(rank);
	}
	else if (checkAceLowStraight(handMask)) {
		// Ace-low Straight Found.
		// Special check.
		//
		rank = "aceLowStraight";
		return getRankScore(rank);
	}
	else {
		// Use modulo division method to determine hand rank.
		//
		moduloScore = (moduloResult(handMask[VALUE_OCCURENCES_BITSET]));
		string rankScored = getRankFromModulo(moduloScore);
		return getRankScore(rankScored);
	}
}
string pokerCore::getRankFromModulo(unsigned long long& moduloScore) {
	if (moduloScore == MODULO_FOUR_KIND) {
		// Four-Of-A-Kind Found.
		//
		return "fourKind";
	}
	else if (moduloScore == MODULO_FULL_HOUSE) {
		// Full-House Found.
		//
		return "fullHouse";
	}
	else if (moduloScore == MODULO_THREE_KIND) {
		// Three-Of-A-Kind Found.
		//
		return "threeKind";
	}
	else if (moduloScore == MODULO_TWO_PAIR) {
		// Two-Pair Found.
		//
		return "twoPair";
	}
	else if (moduloScore == MODULO_ONE_PAIR) {
		// One-Pair Found.
		//
		return "onePair";
	}
	else if (moduloScore == MODULO_HIGH_CARD) {
		// High-Card Found.
		//
		return "highCard";
	}
	else {
		// Guard for invalid hand.
		//
		return "ERROR";
	}
}
void pokerCore::compareAll() {
	int currentRound = START;
	int result;
	while (!(this->empty())) {
		// Display current round.
		//
		cout << "Round " << currentRound << ":" << endl;
		this->setCurrentRound(this->getNextPair());
		vector <vector<string>> currentPair = this->getCurrentRound();
		cout << "Hand One: ";
		printVector(currentPair.at(VECTOR_POS_ONE));
		cout << "Hand Two: ";
		printVector(currentPair.at(VECTOR_POS_TWO));
		// Compare hands.
		//
		result = compareHands(currentPair.at(VECTOR_POS_ONE),
			currentPair.at(VECTOR_POS_TWO));
		// Print winner or tie.
		//
		printWinner(result);
		cout << "------------------------" << endl;
		// Update round.
        //
		currentRound++;
	}
}
bool pokerCore::empty() {
	if (allHands.size() == 0) {
		return true;
	}
	else {
		return false;
	}
}
void pokerCore::printWinner(int& result) {
	if (result == HAND_ONE) {
		cout << "Hand 1 Wins!" << endl;
	}
	else if (result == HAND_TWO) {
		cout << "Hand 2 Wins!" << endl;
	}
	else {
		cout << "Tie!" << endl;
	}
}
int pokerCore::returnWinner(int& result) {
	if (result == HAND_ONE) {
		return HAND_ONE;
	}
	else if (result == HAND_TWO) {
		return HAND_TWO;
	}
	else {
		return TIE;
	}
}
void pokerCore::print2DBoolVector(vector<vector<bool>>& vector) {
	for (int i = 0; i < vector.size(); i++)
	{
		for (int j = 0; j < vector[i].size(); j++)
		{
			cout << vector[i][j];
		}
	}
	cout << endl;
}
card pokerCore::getCard(string& input) {
	card conversion;
	// Determine magnitude (int value of card) from card's value 
	//(the symbol representation of the card as a char)
	// First update value and suit, then determine magnitude.
	//
	conversion.value = input[VALUE];
	conversion.suit = input[SUIT];
	switch (conversion.value) {
	case 'A':
		conversion.magnitude = ACE;
		break;
	case 'K':
		conversion.magnitude = KING;
		break;
	case 'Q':
		conversion.magnitude = QUEEN;
		break;
	case 'J':
		conversion.magnitude = JACK;
		break;
	case 'T':
		conversion.magnitude = TEN;
		break;
	default:
		conversion.magnitude = conversion.value - '0';
		break;
	}
	return conversion;
}
string pokerCore::getStringFromCard(card& input) {
	string cardString;
	cardString.push_back(input.value);
	cardString.push_back(input.suit);
	return cardString;
}
vector <string> pokerCore::cardsToStrings(vector<card>& cards) {
	vector<string> stringHand;
	string cardToAdd;
	for (auto i : cards)
	{
		cardToAdd = getStringFromCard(i);
		stringHand.push_back(cardToAdd);
	}
	return stringHand;
}
vector<card> pokerCore::stringsToCards(vector <string>& vector) {
	card cardToAdd;
	std::vector<card> cards;
	for (auto i : vector)
	{
		cardToAdd = getCard(i);
		cards.push_back(cardToAdd);
	}
	return cards;
}
string pokerCore::vectorToString(vector<string>& vector) {
	string result;
	for (std::vector<std::string>::const_iterator iter = vector.begin();
		iter != vector.end(); ++iter) {
		result += *iter;
	}
	return result;
}
int pokerCore::countOccurences(vector <string>& vector, char& key) {
	string hand = vectorToString(vector);
	int occurs = (int)std::count(hand.begin(), hand.end(), key);
	return occurs;
}
bool pokerCore::occurs(vector <string>& vector, char& key) {
	for (int element = 0; element < vector.size(); element++) {
		for (int stringCheck = 0; stringCheck < vector[element].size();
			stringCheck++) {
			if (vector[element][VALUE] == key) {
				// Key Occurs.
				//
				return true;
			}
		}
	}
	return false;
}
unsigned long long pokerCore::moduloResult(vector <vector<bool>>& input) {
	// Modulo mask conversion by 15 following the algorithm, and then return.
	//
	return getLongFromMask(input) % MODULO_FOR_ALGORITHM;
}
vector<vector<vector<bool>>> pokerCore::maskHandBinary(vector <card>& input) {
	int valueCheckPosition = 0;
	int occurences;
	bool exists;
	char valueToCheck;
	vector<std::string> stringCardVector = cardsToStrings(input);
	std::vector <std::vector<bool>> valuesOfHand{
		{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0},
		{0}, {0},
	};
	std::vector <std::vector<bool>> valueOccurencesOfHand{
		{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
		{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
		{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
		{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0},
	};
	// Determine what values exist in hand.
	// Update corresponding bit accordingly.
	//
	for (int cardValue = 0; cardValue < NUMBER_OF_CARDS;
		cardValue++)
	{
		valueToCheck = VALUES_POSSIBLE[valueCheckPosition];
		exists = occurs(stringCardVector, valueToCheck);
		if (exists == true) {
			valuesOfHand[cardValue].at(FIRST_INDEX) = true;
		}
		valueCheckPosition++;
	}
	// Determine how many of each value card exist in hand.
	// Update corresponding bits accordingly.
	//
	valueCheckPosition = 0;
	for (int nibble = 0; nibble < NUMBER_OF_CARDS; nibble++)
	{
		valueToCheck = VALUES_POSSIBLE[valueCheckPosition];
		occurences = countOccurences(stringCardVector, valueToCheck);
		for (int bits = NIBBLE; bits >= 0; bits--)
		{
			if (occurences != 0) {
				valueOccurencesOfHand[nibble][bits] = true;
				occurences--;
			}
			else {
				valueOccurencesOfHand[nibble][bits] = false;
			}
		}
		valueCheckPosition++;
	}
	// Return the hand's bit masking.
	//
	vector<vector<vector<bool>>> maskedResult;
	maskedResult.push_back(valuesOfHand);
	maskedResult.push_back(valueOccurencesOfHand);
	return maskedResult;
}
bool pokerCore::checkStraight(vector<vector<vector<bool>>>& input) {
	bitset<FIRST_BITSET_SIZE> firstBitset =
		getBinaryFromMaskFirstBitset(input[VALUE_EXISTS_BITSET]);
	bitset<SECOND_BITSET_SIZE> secondBitset =
		getBinaryFromMaskSecondBitset(input[VALUE_EXISTS_BITSET]);
	// Check for straight.
	// if '11111' or '31' is the quotient, a straight is found.
	//
	long divisor = (secondBitset.to_ulong() & -secondBitset.to_ulong());
	long result = secondBitset.to_ulong() / divisor;
	if (result != STRAIGHT_FOUND) {
		return false;
	}
	return true;
}
bool pokerCore::checkAceLowStraight(vector<vector<vector<bool>>>& input) {
	bitset<FIRST_BITSET_SIZE> firstBitset =
		getBinaryFromMaskFirstBitset(input[VALUE_EXISTS_BITSET]);
	bitset<SECOND_BITSET_SIZE> secondBitset =
		getBinaryFromMaskSecondBitset(input[VALUE_EXISTS_BITSET]);
	string aceLowStringCheck = firstBitset.to_string();
	// Check for ace-low straight (Special Case).
	// Check first bitset string for '100000000111100' as this is that hand.
	//
	if (aceLowStringCheck[LOW_ACE_STRAIGHT_POS_ONE] == '1') {
		if (aceLowStringCheck[LOW_ACE_STRAIGHT_POS_TWO] == '1') {
			if (aceLowStringCheck[LOW_ACE_STRAIGHT_POS_THREE] == '1') {
				if (aceLowStringCheck[LOW_ACE_STRAIGHT_POS_FOUR] == '1') {
					if (aceLowStringCheck[LOW_ACE_STRAIGHT_POS_FIVE] == '1') {
						return true;
					}
				}
			}
		}
	}
	return false;
}
bool pokerCore::checkFlush(vector <card>& input) {
	char suitToCheck = input[FIRST_INDEX].suit;
	for (auto& i : input) {
		if (i.suit != suitToCheck) {
			return false;
		}
	}
	return true;
}
bool pokerCore::checkRoyalFlush(vector <card>& input) {
	int valueCheck = FIRST_INDEX;
	char valueToCheck;
	for (auto& i : input) {
		valueToCheck = VALUES_POSSIBLE[valueCheck];
		if (i.value != valueToCheck) {
			return false;
		}
		valueCheck++;
	}
	return true;
}
int pokerCore::getDeepEvaluationScore(vector <card>& input) {
	int score;
	vector <int> handValuesInts = getIntegerVector(input);
	// Sort hand by occurences and then by magnitude.
	// Since a card's value is a symbol representation of its value,
	// the card's magnitude is used for the integer value of the represented symbol value.
	// 
	sort(handValuesInts.begin(), handValuesInts.end());
	sortByOccurencesThenByMagnitude(handValuesInts);
	// Reverse so that occurences come first.
	// 
	reverse(handValuesInts.begin(), handValuesInts.end());
	int first = handValuesInts.back();
	handValuesInts.pop_back();
	int second = handValuesInts.back();
	handValuesInts.pop_back();
	int third = handValuesInts.back();
	handValuesInts.pop_back();
	int forth = handValuesInts.back();
	handValuesInts.pop_back();
	int fifth = handValuesInts.back();
	handValuesInts.pop_back();
	int firstShift;
	int secondShift;
	int thirdShift;
	int forthShift;
	int fifthShift;
	// Apply bitwise operations on each number following the algorithm.
	// First shifted left by 16, second by 12, third by 8, 
	// forth by 4, and fifth by 0.
	// 
	firstShift = first << SLL_ALGO_FIRST_NUMBER;
	secondShift = second << SLL_ALGO_SECOND_NUMBER;
	thirdShift = third << SLL_ALGO_THIRD_NUMBER;
	forthShift = forth << SLL_ALGO_FORTH_NUMBER;
	fifthShift = fifth << SLL_ALGO_FIFTH_NUMBER;
	size_t* index = 0;
	// Convert numbers into decimals to add together for determined hand score.
	//
	int firstBinaryNumber = stoi(toBinary(firstShift), index, BINARY_BASE);
	int secondBinaryNumber = stoi(toBinary(secondShift), index, BINARY_BASE);
	int thirdBinaryNumber = stoi(toBinary(thirdShift), index, BINARY_BASE);
	int forthBinaryNumber = stoi(toBinary(forthShift), index, BINARY_BASE);
	int fifthBinaryNumber = stoi(toBinary(fifthShift), index, BINARY_BASE);
	// Perform OR operations by adding all numbers together.
	// This score is now unique to this hand according to it's value.
	//
	score = firstBinaryNumber + secondBinaryNumber + thirdBinaryNumber +
		forthBinaryNumber + fifthBinaryNumber;
	return score;
}
int pokerCore::getRankScore(string& input) {
	int score;
	// Search ranks map using the input string as a key.
	// Return its value if found, else fail due to invalid hand otherwise.
	//
	auto it = ranks.find(input);
	if (it == ranks.end()) {
		cout << "ERROR: Rank not found!" << endl;
		exit(EXIT_FAILURE);
	}
	else {
		score = it->second;
		return score;
	}
}