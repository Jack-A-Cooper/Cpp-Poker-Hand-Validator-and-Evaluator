// writeFile.cpp
//

#include <../src/headers/writeFile.h>

using namespace std;

void writeToFile(pokerCore& pokerObj) {
	// Create and open file for writing
	//
	ofstream output("Output.txt");
	// Call compareAllWrite function to write contents of comparisons to file
	//
	compareAllWrite(pokerObj, output);
	// Close the file
	//
	output.close();
}
void compareAllWrite(pokerCore& pokerObj, ofstream& outputFile) {
	int currentRound = START;
	int result;
	while (!(pokerObj.empty())) {
		// Write current round.
		//
		outputFile << "Round " << currentRound << ":" << endl;
		pokerObj.setCurrentRound(pokerObj.getNextPair());
		vector <vector<string>> currentPair = pokerObj.getCurrentRound();
		outputFile << "Hand One: ";
		printStringVector(currentPair.at(VECTOR_POS_ONE), outputFile);
		outputFile << "Hand Two: ";
		printStringVector(currentPair.at(VECTOR_POS_TWO), outputFile);
		// Compare hands.
		//
		result = pokerObj.compareHands(currentPair.at(VECTOR_POS_ONE),
			currentPair.at(VECTOR_POS_TWO));
		// Write winner or tie result to output file.
		//
		writeWinner(result, outputFile);
		outputFile << "------------------------" << endl;
		// Update round.
        //
		currentRound++;
	}
}
void writeWinner(int& result, ofstream& outputFile) {
	if (result == HAND_ONE) {
		outputFile << "Hand 1 Wins!" << endl;
	}
	else if (result == HAND_TWO) {
		outputFile << "Hand 2 Wins!" << endl;
	}
	else {
		outputFile << "Tie!" << endl;
	}
}
void printStringVector(vector<string >& vector, ofstream& outputFile) {
	for (int i = 0; i < vector.size(); i++)
	{
		outputFile << vector[i] << " ";
	}
	outputFile << endl;
}