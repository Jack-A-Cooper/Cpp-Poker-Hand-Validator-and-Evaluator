// util.cpp
//

#include "util.h"

using namespace std;

void splitString(string &inputString, vector <string> &stringVector) {
    string temp = "";
    trim(inputString);
    for(int i = 0; i < inputString.length(); ++i) {	
        if(inputString[i] == ' '){
            stringVector.push_back(temp);
            temp = "";
        } else {
            temp.push_back(inputString[i]);
        }
    }
    stringVector.push_back(temp);
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
    // Count frequency.
    //
    unordered_map<int, int> frequency;
    for (int i : vector) {
        frequency[i]++;
    }
    // Sort based on frequencey then value.
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
    // Sort hand.
    //
    sort(vector.begin(), vector.end(), compareCardValue);
    // Reverse for proper usage.
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
