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
 * @brief Provides the core of the implementation for definitions.
 * Supports main core of the program (pokerCompare.cpp).
 *
 * @author Jack Cooper
 * Contact: Jack_cooper01@yahoo.com
 *
 */

#include "util.h"

using namespace std;

void splitString(string &inputString, vector <string> &StringVector) {
	string temp = "";
	trim(inputString);
	for(int i = 0; i < inputString.length(); ++i) {	
		if(inputString[i] == ' '){
			StringVector.push_back(temp);
			temp = "";
		} else {
			temp.push_back(inputString[i]);
		}
	}
	StringVector.push_back(temp);
}
void convertUpper(vector <string> &handStringVector) {
    for (auto &s : handStringVector)
    {
        for (auto &c : s) c = toupper(c);
    }
}
inline void leftTrim(string &s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !isspace(ch);
    }));
}
inline void rightTrim(string &s) {
    s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !isspace(ch);
    }).base(), s.end());
}
 inline void trim(string &s) {
    leftTrim(s);
    rightTrim(s);
}
void printVector(vector <string> &vector) {
	for (auto i : vector)
    {
        cout << i << " ";
    }
	cout << endl;
}
void printCardVector(std::vector <card> &vector) {
    for (auto i : vector)
    {
        cout << i.face << i.suit << " ";
    }
    cout << endl;
}
bool compareCardValue(const card &cardOne, const card &cardTwo) {
    return (cardOne.value < cardTwo.value);
}
void sortByOccurencesAndValue(vector<int> &vector) {
    // Count frequency
    //
    unordered_map<int, int> frequency;
    for (int i : vector) {
        frequency[i]++;
    }
    // Sort based on frequencey then value
    //
    sort(
    vector.begin(), 
    vector.end(),
    [&frequency](int const& a, int const& b) {
        if (a == b) {
            return false;
        }
        if (frequency[a] > frequency[b]) {
            return true;
        }
        else if (frequency[a] < frequency[b]) {
            return false;
        } else if (a < b) {
            return true;
        }
        return a > b;
    });
}
void sortHand(vector <card> &vector) {
    // sort hand
    //
    sort(vector.begin(), vector.end(), compareCardValue);
    // reverse for proper usage
    //
    reverse(vector.begin(), vector.end());
}
string vectorToString(vector<string> &vector) {
    string result;
    for (auto& element : vector) {
        result += element;
    }
    return result;
}
char getBit(bool input) {
    if(input == true) {
        return '1';
    } else {
        return '0';
    }
}
unsigned long long getLongFromMask(vector <vector<bool>> &vector) {
    string stringResult;
    char bit;
    for (int i = 0; i < vector.size(); i++)
    {
        for (int j = 0; j < vector[i].size(); j++)
        {
            bit = getBit(vector[i][j]);
            stringResult.push_back(bit);
        }
    }
    stringstream resStr(stringResult);
    return bitset<SECOND_BITSET_SIZE>(stringResult).to_ullong();
}
bitset<FIRST_BITSET_SIZE> getBinaryFromMaskFirstBitset(vector <vector<bool>> &vector) {
    string stringResult;
    char bit;
    for (int i = 0; i < vector.size(); i++)
    {
        for (int j = 0; j < vector[i].size(); j++)
        {
            bit = getBit(vector[i][j]);
            stringResult.push_back(bit);
        }
    }
    stringstream resStr(stringResult);
    return bitset<FIRST_BITSET_SIZE>(stringResult);
}
bitset<SECOND_BITSET_SIZE> getBinaryFromMaskSecondBitset(vector <vector<bool>> &vector) {
    string stringResult;
    char bit;
    for (int i = 0; i < vector.size(); i++)
    {
        for (int j = 0; j < vector[i].size(); j++)
        {
            bit = getBit(vector[i][j]);
            stringResult.push_back(bit);
        }
    }
    stringstream resStr(stringResult);
    return bitset<SECOND_BITSET_SIZE>(stringResult);
}
vector <int> getIntegerVector(vector <card> &input) {
    vector <int> result;
    for (auto& i : input) {
        result.push_back(i.value);
    }
    return result;
}
string toBinary(int &n) {
    string r;
    while (n != 0){
        r += ( n % 2 == 0 ? "0" : "1" );
        n /= 2;
    }
    reverse(r.begin(), r.end());
    return r;
}