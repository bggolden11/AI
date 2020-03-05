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
        ./a.out 1 2 0 4 6 7 3 8 5 9 10 12 13 14 11 15

Example output:
    Moves: DLLDRRDR
    Number of Nodes Expanded: 800
    Time Taken: 0.005
    Memory Used: 134Kb

The time output is in seconds. Also, I couldn't find a good library for getting c++ memory used so I'm using the sizeOF
operation to get the memory of each new node that is created and then converting the bytes to Kb.

Testing Environment:
I wrote and tested this code on OSX.
