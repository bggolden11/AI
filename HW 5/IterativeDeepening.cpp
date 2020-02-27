#include <iostream>
#include <queue>
#include <unordered_set>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace std::chrono;

#define BOARD_WIDTH 4
#define BOARD_HEIGHT 4
#define MAX_DEPTH 512 //temp value

int BOARD[BOARD_HEIGHT][BOARD_WIDTH];
bool populateBoard(int input[BOARD_HEIGHT][BOARD_WIDTH], int output[BOARD_HEIGHT][BOARD_WIDTH]);
bool populateBoard(int input[]);
double Memory_Used_In_Bytes = 0.0;
int numNodesExplored = 0;
high_resolution_clock::time_point start;
high_resolution_clock::time_point stop;

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
 * BoardQueue Class used for storing board information easiely
 */
class BoardQueue
{
public:
    Point emptySpot;
    int board[BOARD_HEIGHT][BOARD_HEIGHT];
    string *moves;

    BoardQueue(Point emptySpot, int board[BOARD_HEIGHT][BOARD_WIDTH])
    {
        this->emptySpot = Point(emptySpot.x, emptySpot.y);
        populateBoard(board, this->board);
        this->moves = new string("");
    }

    BoardQueue(Point emptySpot, int board[BOARD_HEIGHT][BOARD_WIDTH], string moves)
    {
        this->emptySpot = Point(emptySpot.x, emptySpot.y);
        populateBoard(board, this->board);
        this->moves = new string(moves);
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

//-----------------------------------
/*
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

/*
 * Main function for iterative depth first search
 */
bool DLS(BoardQueue board, int limit){

    // validates whether the current board is correct
    // return true if it has
    if(validateCorrectBoard(board.board)){
        stop = high_resolution_clock::now();
        printResult(board, numNodesExplored);
        return true;
    }
    //Checks whether the depth has been reached if it has return false
    if(limit <= 0)
        return false;

    //increment the number of nodes explored
    numNodesExplored++;

    // Check whether the right spot is valid
    // If it is move to that spot
    // Check whether that board has been visited
    BoardQueue moveBoard(board.emptySpot, board.board);
    if(validateRight(board.emptySpot)){
        moveBoard= goRight(board, moveBoard, board.emptySpot);
        if(!contains(moveBoard)){
            boardsVisted.insert(moveBoard);
            // Recursive call to DLS with new board
            // Decrement limit by 1
            Memory_Used_In_Bytes += sizeof(BoardQueue(Point(board.emptySpot.x , board.emptySpot.y+1), moveBoard.board, *board.moves + "R"));
            if(DLS(BoardQueue(Point(board.emptySpot.x, board.emptySpot.y+1), moveBoard.board, *board.moves + "R"), limit-1))
                return true;
        }
    }
    //Similar pattern seen in 4 other directions below
    if(validateLeft(board.emptySpot)){
        moveBoard = goLeft(board, moveBoard, board.emptySpot);
        if(!contains(moveBoard)){
            boardsVisted.insert(moveBoard);
            Memory_Used_In_Bytes += sizeof(BoardQueue(Point(board.emptySpot.x, board.emptySpot.y-1), moveBoard.board, *board.moves + "L"));
            if(DLS(BoardQueue(Point(board.emptySpot.x, board.emptySpot.y-1), moveBoard.board, *board.moves + "L"), limit-1))
                return true;
        }
    }
    if(validateUp(board.emptySpot)){
        moveBoard = goUp(board, moveBoard, board.emptySpot);
        if(!contains(moveBoard)){
            boardsVisted.insert(moveBoard);
            Memory_Used_In_Bytes += sizeof(BoardQueue(Point(board.emptySpot.x - 1, board.emptySpot.y), moveBoard.board, *board.moves + "U"));
            if(DLS(BoardQueue(Point(board.emptySpot.x - 1, board.emptySpot.y), moveBoard.board, *board.moves + "U"), limit-1))
                return true;
        }
    }
    if(validateDown(board.emptySpot)){
        moveBoard = goDown(board, moveBoard, board.emptySpot);
        if(!contains(moveBoard)){
            boardsVisted.insert(moveBoard);
            Memory_Used_In_Bytes += sizeof(BoardQueue(Point(board.emptySpot.x + 1, board.emptySpot.y), moveBoard.board, *board.moves + "D"));
            if(DLS(BoardQueue(Point(board.emptySpot.x + 1, board.emptySpot.y), moveBoard.board, *board.moves + "D"), limit-1))
                return true;
        }
    }
    // Return false
    // Valid board could not been found with the given depth
    return false;
}

bool IDDFS(){
    start = high_resolution_clock::now();
    for(int i=0; i < MAX_DEPTH; i++){
        // Move through each depth until max depth is found
        if(DLS(BoardQueue(getEmptySpot(), BOARD),i))
        {
            // Return true if the current depth was fioudn
            return true;
        }
    //clear boards visted
    boardsVisted.clear();
    }

    //return false not valid board
    return false;
}


//------------------------------------------
//Driver function
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

    IDDFS();

    cout << "Memory Used: " << Memory_Used_In_Bytes * .001 << "Kb\n";
}