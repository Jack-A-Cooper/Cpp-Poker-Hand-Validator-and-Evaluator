# Open Source C++ Poker Hand Validator and Evaluator 

> Created by: Jack A. Cooper <Jack_cooper01@yahoo.com>

## Core Features

- 5-hand poker validator - core module.
- 5-hand poker evaluator that can define a unique score for any possible poker hand, and also evaluate ties if need be - core module.
- 5-hand poker comparator - core module.
- A modular framework to build off of or modify into other projects.
- Works out of box with .txt file input, but can be quickly modified for other input methods.
- Extensive documentation in-code and here for the project, implementation suggestions, algorithm implemented, and other important information.
- Simple read file module that handles files from the command line, and also provides data output to the core module for processing.
- Simple write file module that is still undergoing development, but is working with the current build version.
- Simple unit testing module.
- GoogleTest unit testing module.
- Multiple .txt files for testing using file input. These are found under the testFiles directory. One will need to drag files into the build's ../bin/debug/ directory to use currently.

### Software Requirements

- Some form of command line program.
- Cmake: https://cmake.org/download/.
- Compiled using C++17 standard.
- ~Some form of C++ compiler (used minGW-w64): https://www.mingw-w64.org/~.

## Quick Summary

The program correctly validates hands, and then determines a "winner". It handles Ace-low and Ace-high straights as well as providing a definitive "value"
or "strength" in a numerical format. This numerical format allows for resolving tie-breaks if the both hands
have the same kind of rank. The only way to get a tie result if, disregarding suit, are exactly the same.
Likewise, I wished to provide a basic packaged module that would allow for reading hands from txt files.
This program does assume a particular format for how these files should be generated/written to work. Otherwise,
the validator will reject processing of the file if an invalid hand is found (from invalid formatting, for instance).

## Redesign Notice

New directory structure is requiring a complete rewrite of some parts of the program. Currently, only an [explanation](#cmake-method) of compiling is ready using Cmake.

During my spare-time I am rewriting the overall program to be more portable, and add features/modules I wanted to implement in the original release (Feb.2022 1.0 Version)

## Compile and Run

### Compiling Methods Suggested

#### Cmake Method (*RECOMMENDED*)

1. Compiled/built using [Cmake](https://cmake.org/download).
2. Easy [tutorial](https://www.youtube.com/watch?v=8_X5Iq9niDE) for installing Cmake.
Also [here](https://google.github.io/googletest/quickstart-cmake.html) is a tutorial for how to build Google Tests outside of an IDE for use if interested.
3. Navigate to the same directory as the source code and test files.
4. To compile sourcecode using Cmake use: 
> cmake -S . -B build
5. To build, use: 
> cmake --build build
6. Now that the source code has been compiled and linked,
and the executable created imply navigate to the build/bin/debug folder using:
> cd build/bin/debug
7. Lastly, drag any .txt test files into this same directory and run using: 
> ./pokerEval [FILENAME].txt
8. The GoogleTest suite will then run.

#### ~g++ Method~ (UNDER REDESIGN)

1. Compiled using [g++](https://gcc.gnu.org) - make sure it is installed.
A guide is [here](https://www.tutorialspoint.com/How-to-Install-Cplusplus-Compiler-on-Windows).
2. Navigate to the same directory as the source code and 
test files, to compile type: 
> g++ -o pokerEval main.cpp readFile.cpp pokerCore.cpp util.cpp
3. To run, use the following (ensure .txt file(s) are in the same directory as the executable!):
> ./pokerEval [FILENAME].txt
 
An example using the filename 'testBasicOriginal.txt':
 
> ./pokerEval testBasicOriginal.txt

4. Program will run displaying the winner(s).  

Note: Highly recommend running with 'testUltimate.txt' has 1000 pairs to evaluate a winner! Use when compiled to run this test: 
> .\pokerHands.exe testUltimate.txt 

### ~Compiling/Running Test Program [Google Test C++] (Main Testing Suite)~ (UNDER REDESIGN)

#### ~To compile test program~ (UNDER REDESIGN)
1. Compiled/built using [Cmake](https://cmake.org/download).
2. Easy [tutorial](https://www.youtube.com/watch?v=8_X5Iq9niDE) for installing Cmake.
Also [here](https://google.github.io/googletest/quickstart-cmake.html) is a tutorial for how to build Google Tests outside of an IDE for use if interested.
3. Navigate to the same directory as the source code and test files.
4. To compile project using Cmake use: 
> cmake -S . -B build
5. To build, use: 
> cmake --build build
6. Now that the tests are built and dependencies (Google Test) is set up,
simply navigate to the build folder using:
> cd build
7. Lastly, to run tests use: 
> ctest
8. The GoogleTest suite will then run.

#### ~Compiling/Running the Print Tests (Secondary Testing):~ (UNDER REDESIGN)
1. Compiled using [g++](https://gcc.gnu.org/). Follow steps from the section [here](#g-method-under-redesign) up to the step with regards to compiling. Use the following steps instead however.
2. Navigate to the same directory as the source code and 
test files, to compile type:
> g++ -o printTests.exe printTests.cpp readFile.cpp pokerCore.cpp util.cpp  
3. To run, use the following:
> .\printTests.exe  
4. Program will run the printing tests.
5. Observe the 'EXPECTING' and 'GOT' results. Matching output will mean a success for that test.

## Program Usage

A card is defined as a 'VS' (value-suit). _Example:_ jack of spades: 'JS'.
 
In particular, when a card is defined, it has three members:
1. value (the character which represents the card's _"value"_).
2. suit (the character which represents the card's suit).
3. magnitude (the integer which *actually* represents the card's _"value"_).
 
### Poker Cards Table

 _Table below displays all the possible cards by name, symbolic value, and magnitude value._  
 
| Card Name                 | Value (Symbol Value)      | Magnitude (Integer Value) |
|:-------------------------:|:-------------------------:|:-------------------------:|
| Ace                       | 'A'                       | 1         OR[^ace]     14 |
| Two                       | '2'                       | 2                         |
| Three                     | '3'                       | 3                         |
| Four                      | '4'                       | 4                         |
| Five                      | '5'                       | 5                         |
| Six                       | '6'                       | 6                         |
| Seven                     | '7'                       | 7                         |
| Eight                     | '8'                       | 8                         | 
| Nine                      | '9'                       | 9                         | 
| Ten                       | 'T'                       | 10                        |
| Jack                      | 'J'                       | 11                        |
| Queen                     | 'Q'                       | 12                        |
| King                      | 'K'                       | 13                        | 

 [^ace]: Aces are unique as they can fill the role as a "low card" with an integer value of 1, or    
         as a "high card" with an integer value of 14. This applies when the ace card helps form a [straight](#poker-ranks-table) hand[^hand] in some manner.    
         An ace-to-five hand creates an ace-low straight, and a ten-to-ace creates an ace-high straight.    
         
 
If you wish to use a '10' value card, it must be written as 'T' for the
card's value. _Example:_ ten of hearts: 'TH', instead of '~~10H~~'.
 
The following is how cards are interpretted in the program:
 
```
Inside util.cpp:
struct card {
    char value;
    char suit;
    int magnitude;
};
```

Aces are scored high in the program on their own. However, they may be used to obtain an 
an Ace-Low Straight hand[^acelowexplained]; albeit as the lowest scored [straight](#poker-ranks-table) rank[^rank].
 
Lastly, throughout this file and the program, the terms "value" and "magnitude" are usually used interchangably.
Do be aware that for the program's implementation they are not the same, but are related. The magnitude is the actual integer value of the card.
and the value is the symbolic character representation of said card.
 
[^acelowexplained]: When an ace value card is used to create a [straight](#poker-ranks-table) from ace-to-five.    
_Example:_ AS, 2D, 3C, 4S, 5H
 
 ### Poker Ranks Table
 
| Rank Name          | Rank Strength      | Hand Example       |
|:------------------:|:------------------:|:------------------:|
| High Card          | 1                  | 7C, 2S, TH, 3D, 5S |
| One Pair           | 2                  | 4C, 9S, 4H, 3D, 2D |
| Two Pair           | 3                  | 4C, 4H, JS, JC, 7C |
| Three of a Kind    | 4                  | 4C, 4H, 4S, QH, 8D |
| Straight[^acelow]  | 5                  | 2C, 3H, 4S, 5H, 6D |
| Flush              | 6                  | JS, AS, TS, 5S, 7S |
| Full House         | 7                  | 3S, 3H, 3D, JC, JS |
| Four of a Kind     | 8                  | QS, QH, QD, QC, AC |
| Straight Flush     | 9                  | AC, 2C, 3C, 4C, 5C |
| Royal Flush        | 10                 | TH, JH, QH, KH, AH |
 
_Table[^poker-ranks-table] below displays all the possible poker ranks[^rank], their "strength"[^hand-strength-quality-score], and an example._  
 
```
Inside pokerCore.cpp:
values = { "A", "K", "Q", "J", "T", "9", "8", "7", "6", "5", "4", "3", "2" };
suits = { "S", "D", "C", "H" };
ranks = { {"highCard", 0}, {"onePair", 1}, {"twoPair", 2},
       {"threeKind", 3},  {"aceLowStraight", 4}, {"straight", 5}, {"flush", 6},
       {"fullHouse", 7}, {"fourKind", 8}, {"straightFlush", 9}, {"royalFlush", 10}
};
```
 
[^rank]: A hand[^hand] is ranked within its category using the ranks of its cards. Individual cards are ranked, from highest to lowest: A, K, Q, J, 10[^10-denotion], 9, 8, 7, 6, 5, 4, 3 and 2. However, aces have the lowest rank under ace-to-five low, or under high rules as part of a five-high straight or straight flush.
 
[^10-denotion]: The program interprets a card value of '10' as 'T'.

[^value]: The numerical or symbological representation of a card. Ordering of values from highest value to lowest value is as follows: A, K, Q, J, 10[^10-denotion], 9, 8, 7, 6, 5, 4, 3 and 2. A "Jack", "Queen", or "King" card is also nicknamed a "face card".
 
[^hand]: The five cards a player is holding in [poker](https://en.wikipedia.org/wiki/Poker). Eace card has a value[^value]. Do note that the card's magnitude actually represents the numerical score of the card. Each card also has a suit[^suits] it belongs to.
 
 [^suits]: [poker](https://en.wikipedia.org/wiki/Poker) has four possible suits a card may belong to: 'Clubs', 'Diamonds', 'Spades', or 'Hearts'. The suit do not affect a card's value, but _may_ affect the hand's[^hand] rank[^rank].
 
[^hand-strength-quality-score]: The quality or score of the particular [poker](https://en.wikipedia.org/wiki/Poker) hand's[^hand] rank[^rank]. Denoted by an integer in the program. Scores are ordered from lowest to highest in the order of 1 to 10. A hand's rank score, quality, or strength is different to the hand's definitive score[^definitive-score-deep-evaluation].
 
[^definitive-score-deep-evaluation]: The determined score, quality, or strength evaluated by the [algorithm's](#the-algorithm) deep evaluation process[^deep-evaluation]. Used if two hands[^hand] compared have the same rank[^rank] in the program.
 
[^deep-evaluation]: The [algorithm's](#the-algorithm) process to get a hand's[^hand] definitive score[^definitive-score-deep-evaluation]. The hand is turned into an integer vector representing only its values[^value], discarding its suits[^suit], and sorting this vector result. The vector is sorted by [frequency of appearance](https://dictionary.cambridge.org/us/dictionary/english/frequency), and then by value[^value]. The sorted vector then undergoes bitwise shifting operations to obtain a numerical value. This numerical value is the hand's definitive score when compared agaisnt another hand of similar rank[^rank]. The larger numerical value 'wins' in the comparison.
 
[^poker-ranks-table]: 1 is regarded as the "weakest" rank score, and 10 is regarded as the "strongest" rank score.    
*Suit and Value Denotion*    
Suits (Symbol): C: "Clubs", S: "Spades",  H: "Hearts", D: "Diamonds".    
Values (Symbol): T: "10 or ten", J: "Jack", Q: "Queen", K: "King", A: "Ace".

[^acelow]: An Ace-low straight is still considered a straight, but the lowest valued one.
In the program it is given a rank score between that of a [three-of-a-kind](#poker-ranks-table), but lower
than a regular [straight](#poker-ranks-table).

### Ties

If a tie occurs, the stronger valued hand will win.
Example One: both hands are three of a kind, one is a Jack and another
is a 4 (i.e., JS JC JH 6H 8C versus 4H 4C 4S KS AH) - hand one wins.

Example Two : both hands are pair, both are Jacks and have only one different card
 (i.e., JS JC 3H 6H 8C versus JD JH 3D 6S TD) - hand two wins.

In essence, if no one has any type of hand, the highest card wins.
If it is a one-pair, the highest card wins again. For two-pair, the highest pair wins.
For three-of-a-kind highest trips wins. For straights and flushes, the highest card wins.
For full-houses, the highest trips win. For four-of-a-kind, the highest four-of-a-kind wins. For
straight flushes, top cards or overall highest card will determine the winner. For royal flushes, they will
always tie. For pairs/kinds that result in matching high pairs/kinds (i.e., both have a three-of-a-kind of Jack's),
then the tie-winner defaults to the highest card holding pair.

If both hands are exactly the same or same value, a tie will result.

The used algorithm handles ties by the weighted metrics above.

### Invalid hands and invalid files

If improper hands are fed into the program, it will print out an error to the console,
and exit with a failure.

As a side note, if one wishes to handle invalid hands or change this behavior,
one will need to redesign a "project-specific" amount of changes throughout the current program.
 
In other words, if one wishes to not have the program exit when the hand validator detects
an invalid hand, a few changes to pokerCore.h and pokerCore.cpp will be required.
Such as modifying the function "validateHand" to not exit the program.
 
More complex or particular redesigns, such as handling invalid hands, will require
changes fitting the larger project's goals. As such, this consideration is left for
the integrator into their project.

Furthermore, files used must follow the following pattern:

1. Each hand is separated by a new line.
2. Each hand has exactly 5 cards (each separated by a single space).
3. Each hand has valid cards
4. Each line is populated with something (no empty lines separating hands)
5. There exists an even amount of hands in the file (since you cannot compare something to nothing)
6. Each hand contains a valid number of value cards (cannot have five of the same value for valid poker hands). Five-of-a-Kind does not exist in legal poker, likewise with wildcards.

As scale was considered, a file may have multiple 'rounds' to evaluate
given a file has more than two hands to compare. The program will automatically
evaluate the entire file if this is the case.
 
 ### Readfile.cpp and File Input Notes
 
Implementation, currently, requires reading a single filename (.txt) from the command-line in order to process.
If this particular design is undesirable, very quick changes to main.cpp, pokerCore.cpp,
and pokerCore.h will be required. Notably, for main.cpp changing what is passed into the main function
will require changes according to how you wish to redesign reading in a pair of hands. For pokerCore.cpp and
pokerCore.h, changes to several functions (e.g., "currentRound") will require redesigns for your desired needs.
I could not account for all possible ways one would wish to integrate this module, so
the most I can provide is the three particular files that would need some quick redesigns in order to integrate
with a particular way of hand input, result output, and/or usage of the pokerCore class as a whole.

Also, the current implementation will only detect valid ".txt" files that exist within the same
directory as the executable. Since file input was an add-on feature, it was designed to be
basic with regards to how to handle this process.

### Missing files

If a file specified in the command line does not exist, an error will be displayed,
and the program will exit with a failure.

### Provided Test Files

Several test files are provided to be run manually (See "Compiling/Running Main Program" above).
Automated testing is done via test.cpp for each function. It is encouraged to create your own test file
akin to the ones provided. The 'testUltimate.txt' has 1000 pairs able to be evaluated.
 
## Integration Notes:
 
A section for those who wish to utilize the project as a whole, or, as it was designed for modularity in mind,
use certain sub-modules of it (such as only the validator/evaluator/comparator) this section will provide
some considerations, suggestions, and helpful notes for doing so.

### Integrator Remarks
 
As the main core of the program revolves around evaluating two 5-hand
poker pairs, integration of the evaluator can become decreasingly or
increasingly more extensive depending on the integrators's goals and project.
 
This section serves as a note regarding the importance of modularity, and
some helpful considerations for the one wishing to integrate the evaluator
into their project for their own use.
 
It goes without saying, the files pokerCore.h, pokerCore.cpp, util.h, and 
util.cpp makes up the "core modules" (the validator/evaluator/comparator). As a consequence, they are the files an integrator
should familiarize themselves the most with when implementing the useful aspects of this project into their own projects. Do note that
the implementation of the pokerCore (the validator/evaluator/comparator) is a class. As such, modifications can be made to fulfill
any requirements of a larger project granted an underlying understanding for its implementation is understood. In other words, once one is familiar
with the design, one should be able to create a multitude of modules using the base design for various uses.

Particular concerns to be aware of, while not all-encompassing, are:
 1) How this module will interface within your overall project.
 2) How this module will process input/outputs.
 3) How this module will behave.
 
 Depending on the desired outcome and usage of the core module (the evaluator),
 one will need to understand the core module's current process. Please refer to the next section.
 
### Core Module's Current Process Breakdown
 
 #### A pokerCore object is the validator and evaluator.  
  1) All hands wished to be evaluated are passed as a vector of strings  
       to the object. Each string element represents a poker hand.  
 
  2) The next two elements at the front of the vector are removed, and sent by reference into  
       the next stage: validation.  
 
  3) Validation: Each hand (string) is vetted for correctness (please refer to the  
       "Usage Notes" section above for more). If a hand is found to be invalid,  
       hand is rejected, and the program exits with a failure. Else, each hand  
       is passed by reference to the next stage: Conversion (a string vector into a vector of string vectors).  
 
  4) Conversion: Each hand (string) is parsed into a vector of string vectors (each vector element within is a string  
       that represents a card). After this process, the vector of string vectors (will now be referred to as the hand vector)  
       moves on to the third stage: Evaluation.  
 
  5) Evaluation: Firstly, each hand undergoes a rank evaluation first. This process takes the hand vector and determines its  
       rank by the algorithm. Once the rank is evaluated, a first stage rank evaluation is undergone with both hand vectors.  
       Do note each rank evaluation uses an integer for comparisons (e.g., a royal-flush is a higher value than a two-pair).  
       There are three outcomes that occur. Do note, that for simplicity, comparison is intertwined within this explanation for the evaluation process. 
 
       v.1) Outcome #1: hand vector #1 has a higher rank.  
              The rank of hand #1 is of greater rank value, and hand #1 is used as the winner of the comparison/evaluation (denoted by  
              an integer 1 being returned). The Evaluation/comparison process stops and sends along the winner onto the next main stage: Result Return.  
 
       v.2) Outcome #2: hand vector #2 has a higher rank.  
              The rank of hand #2 is of greater rank value, and hand #2 is used as the winner of the comparison/evaluation (denoted by  
              an integer 2 being returned). The Evaluation/comparison process stops and sends along the winner onto the next main stage: Result Return.  
 
       v.3) Outcome #3: hand vector #1 and hand vector #2 have the same rank (same integer value denoting rank).  
              This particular outcome fully realizes the algorithm's power. A deeper evaluation/comparison is required to either break the tie,  
              or see if both hand vectors are the same exact hand (disregarding order and suits). This outcome moves onto the deep evaluation stage. This process is
              called when a tie is returned to the comparator (denoted by an integer 3 being returned).  
                    
                   v.DE) Deep Evaluation: Both hand vectors undergo a separate bitwise masking process (refer to the [section](#the-algorithm) for more detail).  
                         This particular outcome fully realizes the algorithm's power. A deeper evaluation/comparison is undergone to either break the tie,  
                         or see if both hands are the same exact hand (disregarding order and suits). Note that the hand vector (vector of string vectors)  
                         is converted into a vector of cards for this process. Any further mention of a hand vector will be of this type. This outcome moves  
                         onto the deep evaluation stage. This stage, of course, has three outcomes.  
 
                         v.DE.1) Outcome #1: hand vector #1 has a stronger "quality of hand" (e.g., it's two-pair is comprised of a pair of 9's versus  
                                 hand vector's two-pair being a pair of 6's). Hand #1 is used as the winner of the comparison/evaluation (denoted by  
                                 an integer 1 being returned). The Evaluation/comparison process stops and sends along the winner onto the next main stage: Result
                                 Return.

                         v.DE.2) Outcome #2: hand vector #2 has a stronger "quality of hand" (e.g., it's two-pair  is comprised of a pair of 9's versus  
                                 hand vector #1's two-pair being a pair of 6's). Hand #2 is used as the winner of the comparison/evaluation (denoted by  
                                 an integer 2 being returned). The Evaluation/comparison process stops and sends along the winner onto the next main stage: Result
                                 Return.

                         v.DE.3) Outcome #3: both hand vectors are the same "quality of hand" (e.g., it's straight is comprised of cards 4-8 versus  
                                 hand vector's straight being composed of cards 4-8 as well; thus, they are the same "quality"). A definitive tie is the result 
                                 of the comparison/evaluation (denoted by an integer 3 being returned). The Evaluation/comparison process stops and sends along 
                                 the tie result onto the next main stage: Result Return. 

 6) Result Return (End of validator/evaluator/comparator): The result of the evaluation stage is determined. In the current implementation,  
      the result is not actually returned, but rather it is used to print the winner to the console.  
 
 7) Loop (End of Core Module Process): Steps #iii-vi are repeated until the vector list containing all hands is depleted. The condition  
      for continuing is determined if the allHands member of a pokerCore's object is empty.  

 ## Core Module Considerations (Planned Features)
 
 This section provides a non-exhaustive list of considerations that should be factored when using the core module.
 Depending on one's intended goals, these are some of the considered behaviors/changes an
 integrator may want. Of course, the redesign is fully up to the integrator's own discretion.

 - Updating the Evaluator's Hands to Evaluate
     The evaluator will run through the populated pairs in its allHands member 
     (a vector of strings where each string is a hand that will be evaluated).
     This method may be accessed by the pokerCores's "setHands" function.
     The vector of strings passed in will overwrite the previous vector.
     Please do know that a pokerCore object's allHands member may be instantiated or dynamically set
     using the constructor or manipulator functions.

 - Use Without File Input
     If not one wishes to not read from a file, the "setAllHands" function 
     should not reverse the vector upon return. The default implementation
     assumes file input, and applies this to correctly sequence the order of evaluation.
     As a pokerCore's object only needs a vector of string to work, the manner in which
     this vector generated or passed into it does not matter. This is left up to the integrator's
     design, and intended usage.

 - Only Determining the Winner of a Comparison
     The default behavior does involve using the resulting winner (or tie) upon a finished
     evaluation round/cycle, but currently does not return it. The function "compareAll" in pokerCore.h/cpp captures
     the the resulting winner of an evaluation/comparison process as an integer called "result" 
     (an int with three outcomes: "1" first hand wins,
     "2" second hand wins, or "3" a resultant tie between both hands). Changing the function
     behavior to just returning the result at the end, and removing the loop would be a quick
     method to integrate the evaluator. Likewise, if printing of the result is not desired it may be omitted.

 - Single Pair Evaluation
     If one wishes to only evaluate one pair, a few changes would be required.
     a quick'n'dirty approach (not recommended) could be that the pokerCore object is only passed a
     string vector which contains a pair of hands. Likewise, the object is only 
     instantiated with a pair or updated with a pair. Otherwise, it will go
     go through all hands until depletion with how "compareAll" is currently implemented in
     pokerCore.h/cpp.
     An alternative and recommended approach would be to duplicate the implementation of "compareAll" into a new function
     (e.g., "compare" or "singleCompare"), and omit the while loop with preservation of the inside logic.
     Since the all hands vector will be modified by reference upon a call to "compareAll" or one's single compare function,
     the removal of the last round/cycle of hands is handled by its logic. Numerous advantages are observed from this
     approach such as requiring only one pokerCore object or easily observing an upcoming evaluation's pair.
 
 - A Definitive Evaluator
     The comparison aspect of the module is an added feature. If one just wished to be able to determine a hand's definitive strength
     (or "quality" with regards to its composition for ranks), one would just require forcing deep evaluation with every hand passed in,
     adding a function to simply pop the next hand in the pokerCore object's allHands member and convert it into a vector of cards, and
     then calling the function "getTieBreakScore" (might want to be renamed or cloned with a different name to something like "getHandScore").
     This function undergoes the deep evaluation only used when both hand's rank is equal and a tie break is required. It returns an integer which
     is the calculated score of the hand passed into it. The function serves as a stand-alone hand evaluator that can return a particular hand's 
     definitive strength given in a card format (vector of string vectors where each element of the outer vector is a card, and each element within
     the string vector is a string representing a card; an example would be "5H" for the card "five of hearts", and this would be in the vector of vectors
     as an elementing like this, "[****["5H"]****, ["AC"], ["KC"], ["3S"], ["2D"]]"). This is the primary goal of the project.

### Closing Remarks  
To conclude this section, an integration will require some changes to get working within a larger project as a module. 
Simply put, these changes could be extensive or minimal, but utilizing the core of the project (specifically referring
to the sub-section: "A Definitive Evaluator" above) can easily be followed to get the power of the algorithm working for your project. Likewise, if
one wishes to extend, modify, or redesign aspects of the overall project, a foundation is there for you.

## Code Credits:

While noted in the program's code itself, I will note the pieces of code
that is not my own here as well. I wish to give proper credit for any sections
within the program that I did not create myself or borrowed.

splitString function (util.cpp):
- Source: https://slaystudy.com/c-split-string-by-space-into-vector/
- Written by: none specified
- Elegant algorithm to parse spaces given an input string. Handy for getting
the input converted to a string vector to use in evaluations. Little modifications
for readability.

convertUpper function (util.cpp):
- Souce: http://www.cplusplus.com/forum/beginner/89508/
- Written by: 'vlad from moscow'
- function to make all string elements in a string vector uppercase

leftTrim function (util.cpp):
- Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
- by user: 'Evan Teran'
- function to trim all leading spaces

rightTrim function (util.cpp):
- Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
- by user: 'Evan Teran'
- function to trim all trailing spaces

trim function (util.cpp):
- Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
- by user: 'Evan Teran'
- function to trim all leading/trailing spaces

sortByOccurenceThenByMagnitude (util.cpp):
- Source: https://codereview.stackexchange.com/questions/173382/sorting-elements-according-to-frequency-of-occurence-in-c
- by user: 'coderodde'
- function to sort an int vector by order of occurrences. Used after already sorting by value (magnitude) in tie breaking scenarios.  Requires an int vector since by the time a tie needs to be broken only the values (magnitudes) are required. Was slightly modified by me to work with C++17.

toBinary (util.cpp)
- Source: https://www.delftstack.com/howto/cpp/how-to-convert-decimal-number-to-binary-in-cpp/
- by user: none specified
- Converts decimal numbers to a binary string.

## Poker Hand Evaluator Algorithm:

### Sources:

Where I found out about the of the [algorithm](https://jonathanhsiao.com/blog/evaluating-poker-hands-with-bit-math).
- Excellent explanation of the algorithm by Jonathan Hsiao. _Secondary source_.

Original Source of [algorithm](https://jsfiddle.net/subskybox/r4mSF/).
- Implemented in JavaScript by Pat Wilson. _Primary Source_.

### Preamble:

The algorithm I implemented was not designed myself. However, it was ported
into C++ completely by me, and the implementation is mine alone, unless otherwise
specified. The core of the program's design/implementation was developed as independently
as possible. It should be noted that a few changes were made to the algorithm's flow to work
with my implementation.

### The Algorithm:

To summarize how the algorithm works, it relies upon bitsets and bitwise operations.
Each hand is masked with two bitsets. I called the first 'value (Symbol) exists bitset',
and the second 'value occurrences bitset'. The first fifteen-sized bitset determines what 
values occur in the hand (A->2 'high ace to low order'). If a value appears the 
bit is updated to '1', else it is left alone '0'. Once the first bitset is finished, 
the second sixty-sized bitset then determines the count of each value respectively. 
Once again this is ordered from Ace to Two (i.e, the first four left bits are keeping
track of the number of ace cards in the hand while the lower four bits are keeping
track of the number of two cards in the hand).

Once the masking is complete, a rank can be found by simply taking mod fifteen of the
second bitmask ('value occurrences bitset'). Do note, this only works for a four-of-a-kind,
full-house, three-of-a-kind, two-pairs, one-pair, and high-card hand ranks. 
The other four legal hand ranks require special checking.

For straights, we use the first bitset ('value exists bitset'), and the fact that
the binary number '11111' equals '31'. We take our first bitset, use bitwise AND with the
negative of the same bitset to obtain the least significant bit ('LSB'). Then divide the 
first bitset with the LSB which will normalize it. Finally, we check if the quotient of this
is '11111' in binary, or '31' in decimal. We need an extra check for ace-low straights. This
requires checking that the first bitset equals '100000000111100'.

For Flushes, bitwise operations are not needed. Simply scan over the hand's suits, and if they
are all the same, then you have a flush. An extra check is required to check for a royal flush,
simply if the first bitset equals '111110000000000'. In other words, if you have a flush, check
for a royal flush by checking the first five bits of the first bitset. If they are all '1', then
you have a royal flush, else it is just a flush.

The final aspect of the algorithm is handling ties. As the previous cases simply determine what
the hand is ranked (one of ten), a method is needed to break ties if the same hand results from
a comparison. Ties are broken by sorting the cards by order of occurrence and then by values (using a card's magnitude).
Bit shifting is used to then create a comparable score. We shift the first number to the left by 16 bits,
the second by 12 bits, the third by 8 bits, the forth by 4 bits, and the fifth by 0.
We then combine all five shifted numbers with bitwise OR. Finally we then compare the results of
these operations on each hand to determine a winner. If after these operations both results are the same,
then the hand's value is exactly the same as the other hand. This is a tie result.

Please read [Jonathan's post](https://jonathanhsiao.com/blog/evaluating-poker-hands-with-bit-math) for more information.

### Special Aspects:

This section highlights special ways of how I implemented the above algorithm that is worth noting.

- Every hand is sorted (high-to-low) prior to masking (for use in masking).

- Every hand is masked prior to comparison.

- In my implementation, the modulo is only used after the special checks to avoid identifying
hands incorrectly.

- Ties are handled after determining what each hand is, and then following the algorithm's tie breaking method.

- The hands are sorted differently for the ties as they must be sorted first by occurence (number of times they appear),
and then by value (magnitude). This will be handled in a helper function.

Please refer to the source code in pokerCore.cpp for the complete implementation I did.

## Project Motivations:

Provide a C++ class-based module implementation of a 5-hand poker hand evaluator based on a bitwise algorithm. This evolved to become a more sophisticated program with other modules now. The idea would be to eventually have separate modules for pokerCore that would handle validation, evaluation, and comparison separately.
A major inspiration for this project was reading Jonathan Hsiao's [blog post](https://jonathanhsiao.com/blog/evaluating-poker-hands-with-bit-math "Jonathan Hsiao' post") about a bitwise algorithm to evaluate 5-hand poker hands I found very interesting.
The [original algorithm was implemented](https://jsfiddle.net/subskybox/r4mSF "Pat Wilson's JavaScript Implementation") by Pat Wilson in JavaScript (2012).

## Source Code Overview:

### Cpp-Poker-Hand-Validator-and-Evaluator
- README.md - this file.
- CHANGELOG.md - file for recording project changes from version to version.
- CMakeLists.txt - cmake makefile.
- .gitignore - stop git from including files specified to repository.
- LICENSE - file for license declaration (open-source MIT license).

### src

#### headers
- util.h - header file for util.cpp.
- pokerCore.h - header file for pokerCore.cpp.
- readFile.h - header file for readFile.cpp.
- writeFile.h - header file for readFile.cpp.

#### modules
- main.cpp - driver file - creates a pokerCore object instance and runs the pokerHands application. (Core Module).
- pokerCore.cpp - class implementation of a poker hand evaluator and validator. Bundled with some extra features. (Core Module).
- util.cpp - helper functions and global variables for pokerCore.cppp.  (Core Module).
- readFile.cpp - handles reading file Input.
- writeFile.cpp - handles reading file output.

### tests

#### googleTests
- googleTests.cpp - main testing suite for program. Tests all functions (aside from ones that print). Uses the Google Test C++ Framework.  

#### testModules
- simpleCoreTest.cpp - printing tests not covered in main testing framework .txt - provided test files for manual testing.  

### testFiles

#### AdvancedTestFiles
- Several .txt files for more advanced or intensive testing purposes.

#### BasicTestFiles
- Several .txt files for more basic or easy testing purposes.
