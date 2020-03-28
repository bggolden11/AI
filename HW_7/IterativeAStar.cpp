//
// Created by Brian Goldenberg on 3/5/20.
//

#ifndef AIHW4_ASTAR_H
#define AIHW4_ASTAR_H


#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

#define BOARD_WIDTH 4
#define BOARD_HEIGHT 4
#define INPUT_SIZE 16
#define MAX_DEPTH 16000
#define ABSOLUTE_MAX std::numeric_limits<int>::max();



int BOARD[BOARD_HEIGHT][BOARD_WIDTH];
bool populateBoard(int input[BOARD_HEIGHT][BOARD_WIDTH], int output[BOARD_HEIGHT][BOARD_WIDTH]);
bool populateBoard(int input[]);
double Memory_Used_In_Bytes = 0.0;
high_resolution_clock::time_point start;
high_resolution_clock::time_point stop;

class BoardQueue;

int numberOfMisplacedTiles(BoardQueue b);
int manhattanDistance(BoardQueue b);

/*
 *
 * Point class used for editing boards easily
 */
struct Point
{
    int x;
    int y;
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    Point()
    {
        this->x = -1;
        this->y = -1;
    }
};

//--------------------------------------------------------

/*
 * BoardQueue Class used for storing board information easily
 * Very similar to other implementation with addition of distanceFromOriginal
 * to keep track of distance from original node to create the hueristic
 */
class BoardQueue
{
public:
    Point emptySpot;
    int board[BOARD_HEIGHT][BOARD_HEIGHT];
    string *moves;
    int distanceFromOriginal;;

    BoardQueue(Point emptySpot, int board[BOARD_HEIGHT][BOARD_WIDTH])
    {
        this->emptySpot = Point(emptySpot.x, emptySpot.y);
        populateBoard(board, this->board);
        this->moves = new string("");
        distanceFromOriginal = 0;
    }


    BoardQueue(Point emptySpot, int board[BOARD_HEIGHT][BOARD_WIDTH], string moves)
    {
        this->emptySpot = Point(emptySpot.x, emptySpot.y);
        populateBoard(board, this->board);
        this->moves = new string(moves);
        distanceFromOriginal = 0;
    }

    BoardQueue(Point emptySpot, int board[BOARD_HEIGHT][BOARD_WIDTH], string moves, int numberFromOriginal)
    {
        this->emptySpot = Point(emptySpot.x, emptySpot.y);
        populateBoard(board, this->board);
        this->moves = new string(moves);
        this->distanceFromOriginal = numberFromOriginal;
    }


    // test whether boards are equivalent used for hashing the baord
    bool operator==(const BoardQueue &p) const
    {
        for (int x = 0; x < BOARD_HEIGHT; x++)
        {
            for (int y = 0; y < BOARD_WIDTH; y++)
            {
                if (board[x][y] != p.board[x][y])
                    return false;
            }
        }
        return true;
    }

};

int numberOfMisplacedTilesCalc(BoardQueue b){
    return numberOfMisplacedTiles(b) + b.distanceFromOriginal;
}

int manhattanDistanceCalc(BoardQueue b){
    return manhattanDistance(b)+ b.distanceFromOriginal;
}


//Implementation of both heuristics to for A* algorithm
// Used later
struct LessThanByMisPlacedTitles
{
    bool operator()(const BoardQueue& lhs, const BoardQueue& rhs) const
    {
        return (numberOfMisplacedTiles(lhs) + lhs.distanceFromOriginal) > (numberOfMisplacedTiles(rhs) + rhs.distanceFromOriginal);
    }
};
struct LessThanMannhatanDistance
{
    bool operator()(const BoardQueue& lhs, const BoardQueue& rhs) const
    {
        return (manhattanDistance(lhs)+ lhs.distanceFromOriginal) > (manhattanDistance(rhs) + rhs.distanceFromOriginal);
    }
};

/*
 *
 * Simple hash function used for hashing the boards into a set for O(1) lookup and insert
 */
class MyHashFunction
{
public:
    size_t operator()(const BoardQueue &p) const
    {
        int hashStorage = 0;
        for (int x = 0; x < BOARD_HEIGHT; x++)
        {
            for (int y = 0; y < BOARD_WIDTH; y++)
            {
                hashStorage += (x * y * p.board[x][y]);
            }
        }
        return hashStorage;
    }
};

// hashset of boards queue already visted
unordered_set<BoardQueue, MyHashFunction> boardsVisted;

bool isValidPoint(Point point)
{
    if (point.x < 0 || point.x >= BOARD_WIDTH)
        return false;
    if (point.y < 0 || point.y >= BOARD_HEIGHT)
        return false;
    return true;
}

//-------------------------------------------

/*
 * Valid function to ensure that the spot is a valid spot
 */
bool validateRight(Point point)
{
    return isValidPoint(Point(point.x, point.y + 1));
}

bool validateLeft(Point point)
{
    return isValidPoint(Point(point.x, point.y - 1));
}

bool validateDown(Point point)
{
    return isValidPoint(Point(point.x + 1, point.y));
}

bool validateUp(Point point)
{
    return isValidPoint(Point(point.x - 1, point.y));
}


/*
 * ----------------------------------------------------------------------
 * Go function used to easily move points among board
 */
BoardQueue goRight(BoardQueue &input, BoardQueue &output, Point emptySpot)
{
    populateBoard(input.board, output.board);
    output.board[emptySpot.x][emptySpot.y] = input.board[emptySpot.x][emptySpot.y + 1];
    output.board[emptySpot.x][emptySpot.y + 1] = input.board[emptySpot.x][emptySpot.y];
    return output;
}

BoardQueue goLeft(BoardQueue &input, BoardQueue &output, Point emptySpot)
{
    populateBoard(input.board, output.board);
    output.board[emptySpot.x][emptySpot.y] = input.board[emptySpot.x][emptySpot.y - 1];
    output.board[emptySpot.x][emptySpot.y - 1] = input.board[emptySpot.x][emptySpot.y];
    return output;
}

BoardQueue goDown(BoardQueue &input, BoardQueue &output, Point emptySpot)
{
    populateBoard(input.board, output.board);
    output.board[emptySpot.x][emptySpot.y] = input.board[emptySpot.x + 1][emptySpot.y];
    output.board[emptySpot.x + 1][emptySpot.y] = input.board[emptySpot.x][emptySpot.y];
    return output;
}

BoardQueue goUp(BoardQueue &input, BoardQueue &output, Point emptySpot)
{
    populateBoard(input.board, output.board);
    output.board[emptySpot.x][emptySpot.y] = input.board[emptySpot.x - 1][emptySpot.y];
    output.board[emptySpot.x - 1][emptySpot.y] = input.board[emptySpot.x][emptySpot.y];
    return output;
}

//-----------------------------------------------
/*
 * Populates baord according to the input
 */
bool populateBoard(int input[])
{
    int inputTracker = 0;
    for (int x = 0; x < BOARD_HEIGHT; x++)
        for (int y = 0; y < BOARD_WIDTH; y++)
        {
            BOARD[x][y] = input[inputTracker];
            inputTracker++;
        }
    return true;
}


/*
 * Given input will alter the output board according to the input
 * HELPER FUNCTION
 */
bool populateBoard(int input[BOARD_HEIGHT][BOARD_WIDTH], int output[][BOARD_WIDTH])
{
    int **newBoard = 0;
    newBoard = new int *[BOARD_HEIGHT];
    for (int x = 0; x < BOARD_HEIGHT; x++)
    {
        newBoard[x] = new int[BOARD_WIDTH];
        for (int y = 0; y < BOARD_WIDTH; y++)
        {
            output[x][y] = input[x][y];
        }
    }
    return true;
}

/*
 * Print board function used for testing and debugging
 */
void printBoard()
{
    for (int x = 0; x < BOARD_HEIGHT; x++)
    {
        for (int y = 0; y < BOARD_WIDTH; y++)
        {
            cout << BOARD[x][y] << " ";
        }
        cout << "\n";
    }
    return;
}


/*
 * Print board according to given input
 */
void printBoard(int input[BOARD_HEIGHT][BOARD_WIDTH])
{
    for (int x = 0; x < BOARD_HEIGHT; x++)
    {
        for (int y = 0; y < BOARD_WIDTH; y++)
        {
            cout << input[x][y] << " ";
        }
        cout << "\n";
    }
    return;
}

/*
 * returns the empty spot according to global board variable
 */
Point getEmptySpot()
{
    for (int x = 0; x < BOARD_HEIGHT; x++)
        for (int y = 0; y < BOARD_WIDTH; y++)
            if (BOARD[x][y] == 0)
                return Point(x, y);
    return Point(-1, -1);
}

/*
 * Returns spot of specific number
 */
Point getSpecificSpot(int b[4][4],int spot){
    for (int x = 0; x < BOARD_HEIGHT; x++)
        for (int y = 0; y < BOARD_WIDTH; y++)
            if (b[x][y] == spot)
                return Point(x, y);
    return Point(-1, -1);
}

/*
 * Validate whether the given board is correct
 */
bool validateCorrectBoard(int board[BOARD_HEIGHT][BOARD_WIDTH])
{
    int correct[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    int correctCounter = 0;
    for (int x = 0; x < BOARD_HEIGHT; x++)
        for (int y = 0; y < BOARD_WIDTH; y++)
        {
            if (board[x][y] != correct[correctCounter])
                return false;
            correctCounter++;
        }
    return true;
}

/*
 * Used to quickly whether a given baord is already within the board visted set.
 * I used this because some older version of c++ dont have the conain function for a hashset.
 */
bool contains(BoardQueue &board)
{
    if (boardsVisted.find(board) != boardsVisted.end())
        return true;
    else
        return false;
}

//------------------------------------------------------------
/*
 * Print the result of the search according to the rubric given
 */
void printResult(BoardQueue &board, int numNodesExplored)
{
    cout << "Moves: " << *board.moves;
    cout << endl
         << "Number of Nodes Expanded: " << numNodesExplored;
    cout << endl
         << "Time Taken: " << ((duration_cast<milliseconds>(stop - start)).count()) / (1000.000);
    cout << endl;
}

/**
 *
 * @param x1 X cordinate one to compare
 * @param y1 Y cordinate one to compare
 * @param x2 X cordinate two to compare
 * @param y2 Y cordinate two to compare
 * @return The manhattan distance of these cordinates
 */
int _manhattanDistance(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

/**
 *
 * @param b board to get manhattan distance for
 * @return manhattan distance of board compared to valid board
 */
int manhattanDistance(BoardQueue b){
    int correct[4][4] = {{1,2,3,4}, {5,6,7,8}, {9,10,11,12},{13,14,15,0}};

    int distanceCount = 0;
    for (int x = 0; x < BOARD_HEIGHT; x++)
        for (int y = 0; y < BOARD_WIDTH; y++)
        {
            if (b.board[x][y] != 0) {
                Point p = getSpecificSpot(b.board,b.board[x][y]);
                Point c = getSpecificSpot(correct,b.board[x][y]);
                distanceCount += _manhattanDistance(p.x,p.y,c.x,c.y);
            }

        }
    return distanceCount;

}


/**
 *
 * @param b boad to get number of misplaced tiles
 * @return number of misplaced tiles compared to orginal board
 */
int numberOfMisplacedTiles(BoardQueue b){
    int correct[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0};
    int numberOfIncorrectCounter = 0;
    int correctCounterIterator = 0;
    for (int x = 0; x < BOARD_HEIGHT; x++)
        for (int y = 0; y < BOARD_WIDTH; y++)
        {
            if (b.board[x][y] != correct[correctCounterIterator])
                numberOfIncorrectCounter++;
            correctCounterIterator++;

        }
    return numberOfIncorrectCounter-1;
}

/**
 *
 * @param boards priority quue to be analyzed
 * @return boolean as to whether misplaced tile path was found
 */
bool _AStarMisplacedTiles(priority_queue<BoardQueue, std::vector<BoardQueue>, LessThanByMisPlacedTitles> &boards, int depth, int &minManDist)
{
    start = high_resolution_clock::now();
    int numNodesExplored = 0;
    while (!boards.empty())
    {
        BoardQueue current = boards.top();
//        printBoard(current.board);
//        cout << "----------------------" << endl;

        if (validateCorrectBoard(current.board))
        {
            //GOAL STATE REACHED
            stop = high_resolution_clock::now();
            printResult(current, numNodesExplored);
            return true;
        }
        BoardQueue moveBoard(current.emptySpot, current.board);
        numNodesExplored++;
        boards.pop();
        int currentNumberFromOriginal = current.distanceFromOriginal;
        if (validateRight(current.emptySpot))
        {
        moveBoard = goRight(current, moveBoard, current.emptySpot);
            if (!contains(moveBoard))
            {
                int currentManDist = numberOfMisplacedTilesCalc(BoardQueue(Point(current.emptySpot.x - 1, current.emptySpot.y), moveBoard.board, *current.moves + "U", currentNumberFromOriginal +1));
                if(currentManDist<= depth){
                boards.push(BoardQueue(Point(current.emptySpot.x, current.emptySpot.y + 1), moveBoard.board, *current.moves + "R", currentNumberFromOriginal +1));
                Memory_Used_In_Bytes += sizeof(BoardQueue(Point(current.emptySpot.x, current.emptySpot.y + 1), moveBoard.board, *current.moves + "R"));
                boardsVisted.insert(moveBoard);
                }
                else{
                    minManDist = min(minManDist,currentManDist);
                }
            }
        }
        if (validateLeft(current.emptySpot))
        {
            moveBoard = goLeft(current, moveBoard, current.emptySpot);
            if (!contains(moveBoard))
            {
                int currentManDist = numberOfMisplacedTilesCalc((BoardQueue(Point(current.emptySpot.x, current.emptySpot.y - 1), moveBoard.board, *current.moves + "L", currentNumberFromOriginal +1)));
                if(currentManDist <= depth){
                boards.push(BoardQueue(Point(current.emptySpot.x, current.emptySpot.y - 1), moveBoard.board, *current.moves + "L", currentNumberFromOriginal +1));
                Memory_Used_In_Bytes += sizeof(BoardQueue(Point(current.emptySpot.x, current.emptySpot.y - 1), moveBoard.board, *current.moves + "L"));
                boardsVisted.insert(moveBoard);
                }
                else{
                    minManDist = min(minManDist,currentManDist);
                }
            }
        }

        if (validateDown(current.emptySpot))
        {
            moveBoard = goDown(current, moveBoard, current.emptySpot);
            if (!contains(moveBoard))
            {
                int currentManDist = numberOfMisplacedTilesCalc(BoardQueue(Point(current.emptySpot.x + 1, current.emptySpot.y), moveBoard.board, *current.moves + "D", currentNumberFromOriginal +1));
                if(currentManDist <= depth){
                boards.push(BoardQueue(Point(current.emptySpot.x + 1, current.emptySpot.y), moveBoard.board, *current.moves + "D", currentNumberFromOriginal +1));
                Memory_Used_In_Bytes += sizeof(BoardQueue(Point(current.emptySpot.x + 1, current.emptySpot.y), moveBoard.board, *current.moves + "D"));
                boardsVisted.insert(moveBoard);
                }
                else{
                    minManDist = min(minManDist,currentManDist);
                }

            }
        }
        if (validateUp(current.emptySpot))
        {
            moveBoard = goUp(current, moveBoard, current.emptySpot);
            if (!contains(moveBoard)) {
                int currentManDist = numberOfMisplacedTilesCalc(
                        BoardQueue(Point(current.emptySpot.x - 1, current.emptySpot.y), moveBoard.board,
                                   *current.moves + "U", currentNumberFromOriginal + 1));
                if (currentManDist <= depth) {
                    boards.push(BoardQueue(Point(current.emptySpot.x - 1, current.emptySpot.y), moveBoard.board,
                                           *current.moves + "U", currentNumberFromOriginal + 1));
                    Memory_Used_In_Bytes += sizeof(BoardQueue(Point(current.emptySpot.x - 1, current.emptySpot.y),
                                                              moveBoard.board, *current.moves + "U"));
                    boardsVisted.insert(moveBoard);
                } else {
                    minManDist = min(minManDist, currentManDist);
                }
            }
        }
    }
    return false;
}

/**
 *
 * @param boards priority quque based off of manhattan distance
 * @return true or false
 */
bool _AStarManhattanDistance(priority_queue<BoardQueue, std::vector<BoardQueue>, LessThanMannhatanDistance> &boards, int depth, int &minManDist)
{
    start = high_resolution_clock::now();
    int numNodesExplored = 0;
    while (!boards.empty())
    {

        BoardQueue current = boards.top();
//        printBoard(current.board);

        if (validateCorrectBoard(current.board))
        {
            //GOAL STATE REACHED
            stop = high_resolution_clock::now();
            printResult(current, numNodesExplored);
            return true;
        }
        int currentNumberFromOriginal = current.distanceFromOriginal;
        BoardQueue moveBoard(current.emptySpot, current.board);
        numNodesExplored++;
        boards.pop();
        if (validateRight(current.emptySpot))
        {
            moveBoard = goRight(current, moveBoard, current.emptySpot);
            if (!contains(moveBoard))
            {
                int currentManDist = manhattanDistanceCalc(BoardQueue(Point(current.emptySpot.x - 1, current.emptySpot.y), moveBoard.board, *current.moves + "U", currentNumberFromOriginal +1));
                if(currentManDist<= depth){
                boards.push(BoardQueue(Point(current.emptySpot.x, current.emptySpot.y + 1), moveBoard.board, *current.moves + "R", currentNumberFromOriginal +1));
                Memory_Used_In_Bytes += sizeof(BoardQueue(Point(current.emptySpot.x, current.emptySpot.y + 1), moveBoard.board, *current.moves + "R"));
                boardsVisted.insert(moveBoard);
                }
                else{
                    minManDist = min(minManDist,currentManDist);
                }
            }
        }
        if (validateLeft(current.emptySpot))
        {
            moveBoard = goLeft(current, moveBoard, current.emptySpot);
            if (!contains(moveBoard))
            {
                int currentManDist = manhattanDistanceCalc((BoardQueue(Point(current.emptySpot.x, current.emptySpot.y - 1), moveBoard.board, *current.moves + "L", currentNumberFromOriginal +1)));
                if(currentManDist <= depth){
                boards.push(BoardQueue(Point(current.emptySpot.x, current.emptySpot.y - 1), moveBoard.board, *current.moves + "L", currentNumberFromOriginal +1));
                Memory_Used_In_Bytes += sizeof(BoardQueue(Point(current.emptySpot.x, current.emptySpot.y - 1), moveBoard.board, *current.moves + "L"));
                boardsVisted.insert(moveBoard);
                }
                else{
                    minManDist = min(minManDist,currentManDist);
                }
            }
        }

        if (validateDown(current.emptySpot))
        {
            moveBoard = goDown(current, moveBoard, current.emptySpot);
            if (!contains(moveBoard))
            {
                int currentManDist = manhattanDistanceCalc(BoardQueue(Point(current.emptySpot.x + 1, current.emptySpot.y), moveBoard.board, *current.moves + "D", currentNumberFromOriginal +1));
                if(currentManDist <= depth){
                boards.push(BoardQueue(Point(current.emptySpot.x + 1, current.emptySpot.y), moveBoard.board, *current.moves + "D", currentNumberFromOriginal +1));
                Memory_Used_In_Bytes += sizeof(BoardQueue(Point(current.emptySpot.x + 1, current.emptySpot.y), moveBoard.board, *current.moves + "D"));
                boardsVisted.insert(moveBoard);
                }
                else{
                    minManDist = min(minManDist,currentManDist);
                }

            }
        }
        if (validateUp(current.emptySpot))
        {
            moveBoard = goUp(current, moveBoard, current.emptySpot);
            if (!contains(moveBoard))
            {
                int currentManDist =manhattanDistanceCalc(BoardQueue(Point(current.emptySpot.x - 1, current.emptySpot.y), moveBoard.board, *current.moves + "U", currentNumberFromOriginal +1));
                if(currentManDist <= depth){
                boards.push(BoardQueue(Point(current.emptySpot.x - 1, current.emptySpot.y), moveBoard.board, *current.moves + "U", currentNumberFromOriginal +1));
                Memory_Used_In_Bytes += sizeof(BoardQueue(Point(current.emptySpot.x - 1, current.emptySpot.y), moveBoard.board, *current.moves + "U"));
                boardsVisted.insert(moveBoard);
                }
                else{
                    minManDist = min(minManDist,currentManDist);
                }
            }
        }
    }
    return false;
}

bool AStarSolveMisplacedBoards()
{
    priority_queue<BoardQueue, std::vector<BoardQueue>, LessThanByMisPlacedTitles> boardsMis;

    Memory_Used_In_Bytes += sizeof(BoardQueue(getEmptySpot(), BOARD));
    int itertiveValue = manhattanDistanceCalc(BoardQueue(getEmptySpot(), BOARD));
    int t = ABSOLUTE_MAX;
    // cout << endl << "Inital Iterative VALUE :" << itertiveValue <<endl;
    for(int i=0; i < MAX_DEPTH; i++){
        boardsMis.push(BoardQueue(getEmptySpot(), BOARD));
        if(_AStarMisplacedTiles(boardsMis,itertiveValue, t))
            return true;
        boardsMis = priority_queue<BoardQueue, std::vector<BoardQueue>, LessThanByMisPlacedTitles>();
        boardsVisted.clear();
        itertiveValue = t;
        t = ABSOLUTE_MAX;

        // cout << endl << itertiveValue;
    }
     return false;
}

bool AStarSolveManhattanDistance()
{
    priority_queue<BoardQueue, std::vector<BoardQueue>, LessThanMannhatanDistance> boardsMis;


    Memory_Used_In_Bytes += sizeof(BoardQueue(getEmptySpot(), BOARD));
    int itertiveValue = manhattanDistanceCalc(BoardQueue(getEmptySpot(), BOARD));
    int t = ABSOLUTE_MAX;
    // cout << endl << "Inital Iterative VALUE :" << itertiveValue <<endl;
     for(int i=0; i < MAX_DEPTH; i++){
        boardsMis.push(BoardQueue(getEmptySpot(), BOARD));
        if(_AStarManhattanDistance(boardsMis,itertiveValue, t))
            return true;
        boardsMis = priority_queue<BoardQueue, std::vector<BoardQueue>, LessThanMannhatanDistance>();
        boardsVisted.clear();
        itertiveValue = t;
        t = ABSOLUTE_MAX;

        // cout << endl << itertiveValue;
     }
     cout << "FAILED!!!!!";
     return false;






//     priority_queue<BoardQueue, std::vector<BoardQueue>, LessThanMannhatanDistance> boardsMan;

//     boardsMan.push(BoardQueue(getEmptySpot(), BOARD));
//     Memory_Used_In_Bytes += sizeof(BoardQueue(getEmptySpot(), BOARD));
//     return _AStarManhattanDistance(boardsMan);
// 
}

int main(int argc, char *argv[])
{
    int input[16];
    if (argc == 1)
        printf("\nNo Extra Command Line Argument Passed Other Than Program Name");
    if (argc == 17)
    {
        for (int i = 1; i <= 16; i++)
            input[i - 1] = atoi(argv[i]);
    }
    else
    {
        printf("\nPlease input your sequence of numbered tiles for initial board configuration");
        return 0;
    }

    populateBoard(input);
    cout << endl << "Would like to run the misplaced tile heuristic or manhattan distane heuristics? " << endl;
    cout << "1: Misplaced Tile" << endl;
    cout << "2: Manhattan Distance" << endl;
    int userInputForHueristic;
    cin >> userInputForHueristic;

    if(userInputForHueristic ==1) {
        cout << endl << "RESULT FOR MISPLACED TILES" << endl << "---------------------" << endl;
        AStarSolveMisplacedBoards();
        cout << "Memory Used: " << Memory_Used_In_Bytes * .001 << "Kb\n";
    }
    else{
        Memory_Used_In_Bytes = 0.0;
        populateBoard(input);
        boardsVisted.clear();
        cout << endl << "RESULT FOR MANHATTAN DISTANCE";
        cout << endl << "---------------------" << endl;

        AStarSolveManhattanDistance();

        cout << "Memory Used: " << Memory_Used_In_Bytes * .001 << "Kb\n";
    }
}

#endif //AIHW6_ASTAR_H
