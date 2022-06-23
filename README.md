**Open Source C++ Poker Hand Validator and Evaluator**  
Author: Jack A. Cooper <Jack_cooper01@yahoo.com>

========================================================================

Motivation:

Provide a C++ implementation of a 5-hand poker hand validator and evaluator
based on a bitwise algorithm.
A major inspiration for this project was reading Jonathan Hsiao's blog post about
a bitwise algorithm to evaluate 5-hand poker hands I found very interesting.
Please check out his blog: https://jonathanhsiao.com/blog/ and the particular post
which inspired the project: https://jonathanhsiao.com/blog/evaluating-poker-hands-with-bit-math.
The original algorithm was implemented by Pat Wilson with his implementation in JavaScript (2012) here:
http://jsfiddle.net/subskybox/r4mSF/.

I wished to design it in such a way that modifications were possible, and followed an OOP design.

========================================================================

Quick Summary:

The program correctly validates hands, and then determines
a "winner". It handles Ace-low and Ace-high straights as well as providing a definitive "value"
or "strength" in a numerical format. This numerical format allows for resolving tie-breaks if the both hands
have the same kind of rank. The only way to get a tie result if, disregarding suit, are exactly the same.
Likewise, I wished to provide a basic packaged module that would allow for reading hands from txt files.
This program does assume a particular format for how these files should be generated/written to work. Otherwise,
the validator will reject processing of the file if an invalid hand is found (from invalid formatting, for instance).

========================================================================

Compiling/Running Main Program:

To compile program:
1. Compiled using g++ (https://gcc.gnu.org/) - make sure it is installed.
a guide provided: https://www.tutorialspoint.com/How-to-Install-Cplusplus-Compiler-on-Windows
2. Navigate to the same directory as the source code and 
test files, type: 'g++ -o pokerHands main.cpp readFile.cpp pokerCompare.cpp util.cpp' to compile code.
into a console window (utilize command prompt)
3. To run, use the following:
'.\pokerHands.exe <testFileName>.txt'
example: '.\pokerHands.exe testBasicOriginal.txt'
4. Program will run displaying the winner

Note: Highly recommend running with 'testUltimate.txt' has 1000 pairs to evaluate a winner!
use when compiled: '.\pokerHands.exe testUltimate.txt'

Compiling/Running Test Program [Google Test C++] (Main Testing Suite):

To compile test program:
1. Compiled/built using cmake - https://cmake.org/download/
2. Easy tutorial for installing cmake - https://www.youtube.com/watch?v=8_X5Iq9niDE
Also a tutorial for how to build Google Tests outside of an IDE for use:
https://google.github.io/googletest/quickstart-cmake.html.
3. Navigate to the same directory as the source code and test files.
A special note: Please ensure the directory with all source code is
called: 'Poker-Hands' or the proper files cannot be linked.
4. To build the build folder, use: 'cmake -S . -B build'. Note this
will download the dependent 'Google Test' framework for use.
5 Then use: 'cmake --build build' to build the project. Do note
the makefile is CMakeLists.txt.
6. Now that the tests are built and dependencies (Google Test) is set up,
simply navigate to the build folder using: 'cd build'.
7. Lastly, use: 'ctest' to run the tests. These should output to the console.
8. Use 'cd ..' to go back to the main directory.

Compiling/Running the Print Tests (Secondary Testing):
1. Compiled using g++ (https://gcc.gnu.org/) (see compiling/running the program section)
2. Navigate to the same directory as the source code and 
test files, type: 'g++ -o printTests.exe printTests.cpp readFile.cpp pokerCompare.cpp util.cpp' to compile code.
into a console window (utilize command prompt)
3. To run, use the following:
'.\printTests.exe'
4. Program will run the printing tests.
5. Observe the 'EXPECTING' and 'GOT' results. Matching means success.

========================================================================

Usages Notes:

A card is defined as a 'FS' (face-suit). Example: jack of spades: 'JS'.

If you wish to use a '10' value card, it must be written as 'T' for the
face value. Example: ten of hearts: 'TH'.

Aces are scored high in the program. However, they may be used to obtain an 
an Ace-Low Straight hand.

Hand ranks ordered weakest to strongest:
1. High Card
2. One Pair
3. Two Pair
4. Three of a Kind
5. Straight
6. Flush
7. Full House
8. Four of a Kind
9. Straight Flush
10. Royal Flush

Note: an Ace-low straight is still considered a straight, but the lowest valued one.
In the program it is given a rank score between that of a three-of-a-kind, but lower
than a regular straight.

****Ties****

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

****Invalid hands and invalid files****

If improper hands are fed into the program, it will print out an error to the console,
and exit with a failure.

As a side note, if one wishes to handle invalid hands or change this behavior,
one will need to redesign a "project-specific" amount of changes throughout the current program.
 
In other words, if one wishes to not have the program exit when the hand validator detects
an invalid hand, a few changes to pokerCompare.h and pokerCompare.cpp will be required.
Such as modifying the function "validateHand" to not exit the program.
 
More complex or particular redesigns, such as handling invalid hands, will require
changes fitting the larger project's goals. As such, this consideration is left for
the integrator into their project.

Furthermore, files used must follow the following pattern:

1. Each hand is separated by a new line.
2. Each hand has exactly 5 cards (each separated by a single space).
3. Each hand has valid cards
4. Each line is populated with something (no empty lines separating hands)
5. There exists an even amount of hands in the file (since you cannot
compare something to nothing)
6. Each hand contains a valid number of face cards (cannot have five of the same face
for valid poker hands). Five-of-a-Kind does not exist in legal poker, 
likewise with wildcards.

As scale was considered, a file may have multiple 'rounds' to evaluate
given a file has more than two hands to compare. The program will automatically
evaluate the entire file if this is the case.
 
 ****Readfile.cpp and File Input Notes****
 
Implementation, currently, requires reading a single filename (.txt) from the command-line in order to process.
If this particular design is undesirable, very quick changes to main.cpp, pokerCompare.cpp,
and pokerCompare.h will be required. Notably, for main.cpp changing what is passed into the main function
will require changes according to how you wish to redesign reading in a pair of hands. For pokerCompare.cpp and
pokerCompare.h, changes to several functions (e.g., "currentRound") will require redesigns for your desired needs.
I could not account for all possible ways one would wish to integrate this module, so
the most I can provide is the three particular files that would need some quick redesigns in order to integrate
with a particular way of hand input, result output, and/or usage of the pokerCompare class as a whole.


Also, the current implementation will only detect valid ".txt" files that exist within the same
directory as the executable. Since file input was an add-on feature, it was designed to be
basic with regards to how to handle this process.

****Missing files****

If a file specified in the command line does not exist, an error will be displayed,
and the program will exit with a failure.


****Provided Test Files****

Several test files are provided to be run manually (See "Compiling/Running Main Program" above).
Automated testing is done via test.cpp for each function. It is encouraged to create your own test file
akin to the ones provided. The 'testUltimate.txt' has 1000 pairs able to be evaluated.
 
========================================================================
 
Integration Notes:
 
A section for those who wish to utilize the project as a whole, or, as it was designed for modularity in mind,
use certain sub-modules of it (such as only the validator/evaluator/comparator) this section will provide
some considerations, suggestions, and helpful notes for doing so.

****Integrator Remarks****
 
As the main core of the program revolves around evaluating two 5-hand
poker pairs, integration of the evaluator can become decreasingly or
increasingly more extensive depending on the integrators's goals and project.
 
This section serves as a note regarding the importance of modularity, and
some helpful considerations for the one wishing to integrate the evaluator
into their project for their own use.
 
It goes without saying, the files pokerCompare.h, pokerCompare.cpp, util.h, and 
util.cpp makes up the "core modules" (the validator/evaluator/comparator). As a consequence, they are the files an integrator
should familiarize themselves the most with when implementing the useful aspects of this project into their own projects. Do note that
the implementation of the pokerCompare (the validator/evaluator/comparator) is a class. As such, modifications can be made to fulfill
any requirements of a larger project granted an underlying understanding for its implementation is understood. In other words, once one is familiar
with the design, one should be able to create a multitude of modules using the base design for various uses.

Particular concerns to be aware of, while not all-encompassing, are:
 1) How this module will interface within your overall project.
 2) How this module will process input/outputs.
 3) How this module will behave.
 
 Depending on the desired outcome and usage of the core module (the evaluator),
 one will need to understand the core module's current process. Please refer to the next section.
 
****Core Module's Current Process Breakdown****
 
 1) A pokerCompare object is the validator and evaluator.  
    1.1) All hands wished to be evaluated are passed as a vector of strings  
         to the object. Each string element represents a poker hand.  
    1.2) The next two elements at the front of the vector are removed, and sent by reference into  
         the next stage: validation.  
    1.3) Validation: Each hand (string) is vetted for correctness (please refer to the  
         "Usage Notes" section above for more). If a hand is found to be invalid,  
         hand is rejected, and the program exits with a failure. Else, each hand  
         is passed by reference to the next stage: Conversion (a string vector into a vector of string vectors).  
    1.4) Conversion: Each hand (string) is parsed into a vector of string vectors (each vector element within is a string  
         that represents a card). After this process, the vector of string vectors (will now be referred to as the hand vector)  
         moves on to the third stage: Evaluation.  
    1.5) Evaluation: Firstly, each hand undergoes a rank evaluation first. This process takes the hand vector and determines its  
         rank by the algorithm. Once the rank is evaluated, a first stage rank evaluation is undergone with both hand vectors.  
         Do note each rank evaluation uses an integer for comparisons (e.g., a royal-flush is a higher value than a two-pair).  
         There are three outcomes that occur. Do note, that for simplicity, comparison is intertwined within this explanation for the evaluation process.  
         1.5.1) Outcome #1: hand vector #1 has a higher rank.  
                The rank of hand #1 is of greater rank value, and hand #1 is used as the winner of the comparison/evaluation (denoted by  
                an integer 1). The Evaluation/comparison process stops and sends along the winner onto the next main stage: Result Return.  
         1.5.2) Outcome #2: hand vector #2 has a higher rank.  
                The rank of hand #2 is of greater rank value, and hand #2 is used as the winner of the comparison/evaluation (denoted by  
                an integer 2). The Evaluation/comparison process stops and sends along the winner onto the next main stage: Result Return.  
         1.5.3) Outcome #3: hand vector #1 and hand vector #2 have the same rank (same integer value denoting rank).  
                This particular outcome fully realizes the algorithm's power. A deeper evaluation/comparison is required to either break the tie,  
                or see if both hand vectors are the same exact hand (disregarding order and suits). This outcome moves onto the deep evaluation stage.  
                1.5.3.DE) Deep Evaluation: Both hand vectors undergo a bitwise masking process (refer to the section: "The Algorithm" below for detail).  
                          This particular outcome fully realizes the algorithm's power. A deeper evaluation/comparison is undergone to either break the tie,  
                          or see if both hands are the same exact hand (disregarding order and suits). Note that the hand vector (vector of string vectors)  
                          is converted into a vector of cards for this process. Any further mention of a hand vector will be of this type. This outcome moves  
                          onto the deep evaluation stage. This stage, of course, has three outcomes.  
                          1.5.3.DE.1) Outcome #1: hand vector #1 has a stronger "quality of hand" (e.g., it's two-pair is comprised of a pair of 9's versus  
                                      hand vector's two-pair being a pair of 6's). Hand #1 is used as the winner of the comparison/evaluation (denoted by  
                                      an integer 1). The Evaluation/comparison process stops and sends along the winner onto the next main stage: Result Return.  
                          1.5.3.DE.2) Outcome #2: hand vector #2 has a stronger "quality of hand" (e.g., it's two-pair  is comprised of a pair of 9's versus  
                                      hand vector #1's two-pair being a pair of 6's). Hand #2 is used as the winner of the comparison/evaluation (denoted by  
                                      an integer 2). The Evaluation/comparison process stops and sends along the winner onto the next main stage: Result Return.  
                          1.5.3.DE.3) Outcome #3: both hand vectors are the same "quality of hand" (e.g., it's straight is comprised of cards 4-8 versus  
                                      hand vector's straight being composed of cards 4-8 as well; thus, they are the same "quality"). Do note that no suit is  
                                      of higher quality than another suit. A definitive tie is the result of the comparison/evaluation (denoted by an integer 3).  
                                      The Evaluation/comparison process stops and sends along the tie result onto the next main stage: Result Return.  
       1.6) Result Return (End of validator/evaluator): The result of the evaluation stage is determined. In the current implementation,  
                       the result is not actually returned, but rather it is used to print the winner to the console.  
       1.7) Loop (End of Core Module Process): Steps #1.3-1.6 are repeated until the vector list containing all hands is depleted. The condition  
            for continuing is determined if the allHands member of a pokerCompare object is empty.  
 
 ****Core Module Redesign Considerations****
 
 This section provides a non-exhaustive list of considerations that should be factored when using the core module.
 Depending on one's intended goals, these are some of the considered behaviors/changes an
 integrator may want. Of course, the redesign is fully up to the integrator's own discretion.

 - Updating the Evaluator's Hands to Evaluate:
     The evaluator will run through the populated pairs in its allHands member 
     (a vector of strings where each string is a hand that will be evaluated).
     This method may be accessed by the pokerCompare's "setHands" function.
     The vector of strings passed in will overwrite the previous vector.
     Please do know that a pokerCompare object's allHands member may be instantiated or dynamically set
     using the constructor or manipulator functions.

 - Use Without File Input:
     If not one wishes to not read from a file, the "setAllHands" function 
     should not reverse the vector upon return. The default implementation
     assumes file input, and applies this to correctly sequence the order of evaluation.
     As a pokerCompare object only needs a vector of string to work, the manner in which
     this vector generated or passed into it does not matter. This is left up to the integrator's
     design, and intended usage.

 - Only Determining the Winner of a Comparison:
     The default behavior does involve using the resulting winner (or tie) upon a finished
     evaluation round/cycle, but currently does not return it. The function "compareAll" in pokerCompare.h/cpp captures
     the the resulting winner of an evaluation/comparison process as an integer called "result" 
     (an int with three outcomes: "1" first hand wins,
     "2" second hand wins, or "3" a resultant tie between both hands). Changing the function
     behavior to just returning the result at the end, and removing the loop would be a quick
     method to integrate the evaluator. Likewise, if printing of the result is not desired it may be omitted.

 - Single Pair Evaluation:
     If one wishes to only evaluate one pair, a few changes would be required.
     a quick'n'dirty approach (not recommended) could be that the pokerCompare object is only passed a
     string vector which contains a pair of hands. Likewise, the object is only 
     instantiated with a pair or updated with a pair. Otherwise, it will go
     go through all hands until depletion with how "compareAll" is currently implemented in
     pokerCompare.h/cpp.
     An alternative and recommended approach would be to duplicate the implementation of "compareAll" into a new function
     (e.g., "compare" or "singleCompare"), and omit the while loop with preservation of the inside logic.
     Since the all hands vector will be modified by reference upon a call to "compareAll" or one's single compare function,
     the removal of the last round/cycle of hands is handled by its logic. Numerous advantages are observed from this
     approach such as requiring only one pokerCompare object or easily observing an upcoming evaluation's pair.
 
 - A Definitive Evaluator:
     The comparison aspect of the module is an added feature. If one just wished to be able to determine a hand's definitive strength
     (or "quality" with regards to its composition for ranks), one would just require forcing deep evaluation with every hand passed in,
     adding a function to simply pop the next hand in the pokerCompare object's allHands member and convert it into a vector of cards, and
     then calling the function "getTieBreakScore" (might want to be renamed or cloned with a different name to something like "getHandScore").
     This function undergoes the deep evaluation only used when both hand's rank is equal and a tie break is required. However, it can just as well
     serve as a stand-alone hand evaluator that can return a particular hand's definitive strength.

****Final Remarks****
To conclude, an integration will require some changes to get working within a larger project as a module. 
Simply put, these changes could be extensive or minimal, but utilizing the core of the project (specifically referring
to the sub-section: "A Definitive Evaluator" above) can easily be followed to get the power of the algorithm working for your project. Likewise, if
one wishes to extend, modify, or redesign aspects of the overall project, a foundation is there for you.
 
========================================================================

Credits and Borrowed Code:

While noted in the program's code itself, I will note the pieces of code
that is not my own here as well.

splitString function (util.cpp)
- Source: https://slaystudy.com/c-split-string-by-space-into-vector/
- Written by: none specified
- Elegant algorithm to parse spaces given an input string. Handy for getting
the input converted to a string vector to use in evaluations. Little modifications
for readability.

convertUpper function (util.cpp)
- Souce: http://www.cplusplus.com/forum/beginner/89508/
- Written by: 'vlad from moscow'
- function to make all string elements in a string vector uppercase

leftTrim function (util.cpp)
- Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
- by user: 'Evan Teran'
- function to trim all leading spaces

rightTrim function (util.cpp)
- Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
- by user: 'Evan Teran'
- function to trim all trailing spaces

trim function (util.cpp)
- Source: https://stackoverflow.com/questions/216823/how-to-trim-a-stdstring
- by user: 'Evan Teran'
- function to trim all leading/trailing spaces

sortByOccurences (util.cpp)
- Source: https://codereview.stackexchange.com/questions/173382/sorting-elements-according-to-frequency-of-occurence-in-c
- by user: 'coderodde'
- function to sort an int vector by order of occurrences.
Used after already sorting by face value in tie breaking scenarios. 
Requires an int vector since by the time a tie needs to be broken only
the face values are required.

toBinary (util.cpp)
- Source: https://www.delftstack.com/howto/cpp/how-to-convert-decimal-number-to-binary-in-cpp/
- by user: none specified
- Converts decimal numbers to a binary string.

========================================================================

Poker Hand Evaluator Algorithm:

Sources:

Where I found out about the of algorithm (secondary source):
https://jonathanhsiao.com/blog/evaluating-poker-hands-with-bit-math
- Excellent explanation of the algorithm by Jonathan Hsiao.
I followed how he described it for use in porting it into my project.

Original Source of algorithm (secondary source - where Jonathan found it out):
http://jsfiddle.net/subskybox/r4mSF/
- Implemented in JavaScript by Pat Wilson.

Preamble:

The algorithm I implemented was not developed by myself. However, it was ported
into C++ completely by myself, and the implementation is mine alone, unless otherwise
specified. The core of the program's design/implementation was developed as independently
as possible. It should be noted that a few changes were made to the algorithm's flow to work
with my implementation.

The Algorithm:

To summarize how the algorithm works, it relies upon bitsets and bitwise operations.
Each hand is masked with two bitsets. I called the first 'face exists bitset',
and the second 'face occurrences bitset'. The first fifteen-sized bitset determines what 
faces occur in the hand (A->2 'high ace to low order'). If a face appears the 
bit is updated to '1', else it is left alone '0'. Once the first bitset is finished, 
the second sixty-sized bitset then determines the count of each facecard respectively. 
Once again this is ordered from Ace to Two (i.e, the first four left bits are keeping
track of the number of ace cards in the hand while the lower four bits are keeping
track of the number of two cards in the hand).

Once the masking is complete, a rank can be found by simply taking mod fifteen of the
second bitmask ('face occurrences bitset'). Do note, this only works for a four-of-a-kind,
full-house, three-of-a-kind, two-pairs, one-pair, and high-card hand ranks. 
The other four legal hand ranks require special checking.

For straights, we use the first bitset ('face exists bitset'), and the fact that
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
a comparison. Ties are broken by sorting the cards by order of occurrence and then by face values.
Bit shifting is used to then create a comparable score. We shift the first number to the left by 16 bits,
the second by 12 bits, the third by 8 bits, the forth by 4 bits, and the fifth by 0.
We then combine all five shifted numbers with bitwise OR. Finally we then compare the results of
these operations on each hand to determine a winner. If after these operations both results are the same,
then the hand's value is exactly the same as the other hand. This is a tie result.

Please read Jonathan's post for more information. I highly recommend Jonathan's post as it
contains numerous examples, and it is very well-written.

Special Aspects:

This section highlights special ways of how I implemented the above algorithm that is worth noting.

- Every hand is sorted (high-to-low) prior to masking (for use in masking).

- Every hand is masked prior to comparison.

- In my implementation, the modulo is only used after the special checks to avoid identifying
hands incorrectly.

- Ties are handled after determining what each hand is, and then following the algorithm's tie breaking method.

- The hands are sorted differently for the ties as they must be sorted first by occurence (number of times they appear),
and then by face value. This will be handled in a helper function.

Please refer to the source code in pokerCompare.cpp for the complete implementation I did.

========================================================================

Source Code Overview:

Readme.txt - this file
main.cpp - driver file - creates a pokerCompare object instance and runs the pokerHands application
readFile.h - header file for readFile.cpp
readFile.cpp - handles reading file Input
pokerCompare.h - header file for pokerCompare.cpp
pokerCompare.cpp - my class implementation of a poker hand evaluator and validator
util.h - header file for util.cpp
util.cpp - helper functions and global variables for pokerCompare.cpp/main.cpp
pokerHandsTests.cpp - main testing suite for program. Tests all functions (aside
from ones that print). Uses the Google Test C++ Framework.
printTests.cpp - printing tests not covered in main testing framework
*.txt - provided test files for manual testing (may be modified)
CMakeLists.txt - cmake makefile (created by me so Google Test may be
used outside of the IDE for sake of ease).
pokerHands.exe - main executable for poker hands; run using './pokerHands.exe <textFile>.txt' once compiled.
printTests.exe - main executable for unit tests; ran using './printTests.exe' once compiled.

========================================================================

IDE Used:
Microsoft Visual Studio Community (https://visualstudio.microsoft.com/vs/community/)

Programs Required:
Windows Command prompt (console)
Some form of C++ compiler (used minGW-w64): https://www.mingw-w64.org/
cmake: https://cmake.org/download/
Google Test C++: https://github.com/google/googletest
Git for repository needs: https://github.com/

========================================================================
