Instructions to run:
Compile the code with g++.
I used c++11 standard to compile. But I tested it with c++98 also. 
Example: 
    g++ -std=c++11 puzzle.cpp -o puzzle-execution
After compilation has completed. Execute the program.
The execution takes in the input of your board as arguments. 
Example:
    ./puzzle-execution 1 0 2 4 5 7 3 8 9 6 11 12 13 10 14 15

Sample Output:
    Moves: RDLDDRR
    Number of Nodes Expanded: 461
    Time Taken: 0.004
    Memory Used: 83.44Kb

The time output is in seconds. Also, I couldn't find a good library for getting c++ memory used so I'm using the sizeOF
operation to get the memory of each new node that is created and then converting the bytes to Kb.  

Testing Environment:
I wrote this code on OSX; however, I also tested it on systems4 which is a linux envirement.
