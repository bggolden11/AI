Instructions to run:
Compile the code with g++.
The code will compile and run with both
c++11 and c++98.

1.
    Move into the proper directory containing
    the IterativeAStar.cpp file.
2.
    Compile the code:
        g++ IterativeAStar.cpp
3.
    Run the code:
        ./a.out 1 3 4 8 5 2 0 6 9 10 7 11 13 14 15 1
4.
    Once you run the code you will be prompted for which hueristic to use


Example outputs:
Would like to run the misplaced tile heuristic or manhattan distane heuristics?
1: Misplaced Tile
2: Manhattan Distance
2

RESULT FOR MANHATTAN DISTANCE
---------------------
Moves: DRRUULLDRRUULLDLDRRDLUULURRDDRD
Number of Nodes Expanded: 1902
Time Taken: 0.112
Memory Used: 504.504Kb

<---------------------------------------------------------------------------------->

Would like to run the misplaced tile heuristic or manhattan distane heuristics?
1: Misplaced Tile
2: Manhattan Distance
2

RESULT FOR MANHATTAN DISTANCE
---------------------
Moves: RDDLLURDRRUULLDRRUULLDLDRRDLUULURRDDRD
Number of Nodes Expanded: 137606
Time Taken: 72.493
Memory Used: 25889.4Kb

<---------------------------------------------------------------------------------->

Would like to run the misplaced tile heuristic or manhattan distane heuristics?
1: Misplaced Tile
2: Manhattan Distance
1

RESULT FOR MISPLACED TILES
---------------------
Moves: RULLDRDRD
Number of Nodes Expanded: 21
Time Taken: 0
Memory Used: 1.936Kb

<---------------------------------------------------------------------------------->


The time output is in seconds. Also, I couldn't find a good library for getting c++ memory used so I'm using the sizeOF
operation to get the memory of each new node that is created and then converting the bytes to Kb.

Testing Environment:
I wrote and tested this code on OSX.