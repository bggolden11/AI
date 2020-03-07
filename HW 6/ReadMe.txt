Instructions to run:
Compile the code with g++.
The code will compule and run with both
c++11 and c++98.

1.
    Move into the proper directory containing
    the IterativeDeepening.cpp file.
2.
    Compile the code:
        g++ IterativeDeepening.cpp
3.
    Run the code:
        ./a.out 1 3 4 8 5 2 0 6 9 10 7 11 13 14 15 1

Example output:

    RESULT FOR MISPLACED TILES
    ---------------------
    Moves: RULLDRDRD
    Number of Nodes Expanded: 21
    Time Taken: 0
    Memory Used: 4.4Kb

    RESULT FOR MANHATTAN DISTANCE
    ---------------------
    Moves: RULLDRDRD
    Number of Nodes Expanded: 12
    Time Taken: 0
    Memory Used: 2.64Kb

The time output is in seconds. Also, I couldn't find a good library for getting c++ memory used so I'm using the sizeOF
operation to get the memory of each new node that is created and then converting the bytes to Kb.

Testing Environment:
I wrote and tested this code on OSX.
