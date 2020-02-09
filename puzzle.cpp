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

int BOARD[BOARD_HEIGHT][BOARD_WIDTH];
bool populateBoard(int input[BOARD_HEIGHT][BOARD_WIDTH], int output[BOARD_HEIGHT][BOARD_WIDTH]);
bool populateBoard(int input[]);
high_resolution_clock::time_point start;
high_resolution_clock::time_point stop;

struct Point
{
    int x;
    int y;
 Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
  Point(){
      this->x = -1;
      this->y = -1;
  }
};

class BoardQueue
{
    public:
    Point emptySpot;
    int board[BOARD_HEIGHT][BOARD_HEIGHT];
    string moves;
    
    BoardQueue(Point emptySpot, int board[BOARD_HEIGHT][BOARD_WIDTH]){
        this->emptySpot = Point(emptySpot.x,emptySpot.y);
        populateBoard(board,this->board);
        this->moves = "";
    }

    BoardQueue(Point emptySpot, int board[BOARD_HEIGHT][BOARD_WIDTH], string moves){
        this->emptySpot = Point(emptySpot.x,emptySpot.y);
        populateBoard(board,this->board);
        this->moves = moves;
    }

    bool operator==(const BoardQueue& p) const
    {
        for(int x = 0; x < BOARD_HEIGHT; x++)
        {
            for(int y =0; y < BOARD_WIDTH; y++)
            {
                if(board[x][y] != p.board[x][y]) return false;
            }
        }
        return true;
    }
};

class MyHashFunction { 
public: 
    size_t operator()(const BoardQueue& p) const
    { 
        int hashStorage = 0;
        for(int x = 0; x < BOARD_HEIGHT; x++)
        {
            for(int y =0; y < BOARD_WIDTH; y++)
            {
                    hashStorage+=(x*y*p.board[x][y]);
            }
        }
        return hashStorage;
    } 
}; 


unordered_set<BoardQueue,MyHashFunction> boardsVisted;

bool isValidPoint(Point point){
    if(point.x < 0 || point.x > BOARD_WIDTH)
        return false;
    if(point.y < 0 || point.y > BOARD_HEIGHT)
        return false;
    return true;
}

bool getRight(Point point){
    return isValidPoint(Point(point.x,point.y+1));
}

bool getLeft(Point point){
    return isValidPoint(Point(point.x,point.y-1));
}

bool getDown(Point point){
    return isValidPoint(Point(point.x+1,point.y));
   
}

bool getUp(Point point){
    return isValidPoint(Point(point.x-1,point.y));
}

BoardQueue goRight(BoardQueue input, BoardQueue output, Point emptySpot){
    populateBoard(input.board, output.board);
    output.board[emptySpot.x][emptySpot.y] = input.board[emptySpot.x][emptySpot.y+1];
    output.board[emptySpot.x][emptySpot.y+1] = input.board[emptySpot.x][emptySpot.y];
    return output;
}

BoardQueue goLeft(BoardQueue input, BoardQueue output, Point emptySpot){
    populateBoard(input.board, output.board);
    output.board[emptySpot.x][emptySpot.y] = input.board[emptySpot.x][emptySpot.y-1];
    output.board[emptySpot.x][emptySpot.y-1] = input.board[emptySpot.x][emptySpot.y];
    return output;
}

BoardQueue goDown(BoardQueue input, BoardQueue output, Point emptySpot){
    populateBoard(input.board, output.board);
    output.board[emptySpot.x][emptySpot.y] = input.board[emptySpot.x+1][emptySpot.y];
    output.board[emptySpot.x+1][emptySpot.y] = input.board[emptySpot.x][emptySpot.y];
    return output;
}

BoardQueue goUp(BoardQueue input, BoardQueue output, Point emptySpot){
    populateBoard(input.board, output.board);
    output.board[emptySpot.x][emptySpot.y] = input.board[emptySpot.x-1][emptySpot.y];
    output.board[emptySpot.x-1][emptySpot.y] = input.board[emptySpot.x][emptySpot.y];
    return output;
}

bool populateBoard(int input[]){
    int inputTracker = 0;
        for(int x = 0; x < BOARD_HEIGHT; x++)
            for(int y =0; y < BOARD_WIDTH; y++){
                BOARD[x][y] = input[inputTracker];
                inputTracker++;
            }
    return true;
}

bool populateBoard(int input[BOARD_HEIGHT][BOARD_WIDTH], int output[][BOARD_WIDTH]){
    int** newBoard = 0;
    newBoard = new int*[BOARD_HEIGHT];
        for(int x = 0; x < BOARD_HEIGHT; x++){
            newBoard[x] = new int[BOARD_WIDTH];
            for(int y =0; y < BOARD_WIDTH; y++){
                output[x][y] = input[x][y];
            }
        }
    return true;
}

void printBoard(){
    for(int x = 0; x < BOARD_HEIGHT; x++){
        for(int y =0; y < BOARD_WIDTH; y++){
            cout << BOARD[x][y] << " ";
        }
        cout << "\n";
    }
        return;
}

void printBoard(int input[BOARD_HEIGHT][BOARD_WIDTH]){
    for(int x = 0; x < BOARD_HEIGHT; x++){
        for(int y =0; y < BOARD_WIDTH; y++){
            cout << input[x][y] << " ";
        }
        cout << "\n";
    }
        return;
}

Point getEmptySpot()
{
    for(int x = 0; x < BOARD_HEIGHT; x++)
        for(int y =0; y < BOARD_WIDTH; y++)
            if(BOARD[x][y] == 0) 
                return Point(x,y);
    return Point(-1,-1);
}


bool validateCorrectBoard(int board[BOARD_HEIGHT][BOARD_WIDTH]){
    int correct[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    int correctCounter = 0;
    for(int x = 0; x < BOARD_HEIGHT; x++)
        for(int y =0; y < BOARD_WIDTH; y++){
            if(board[x][y] != correct[correctCounter]) return false;
            correctCounter++;
        }
    return true;
            
}

bool contains(BoardQueue board)
{
    if(boardsVisted.find(board)!=boardsVisted.end())
        return true;
    else 
        return false;
}

void printResult(BoardQueue board, int numNodesExplored){
    cout << endl << "Moves: " << board.moves;
    cout << endl << "Number of Nodes Expanded: " << numNodesExplored;
    cout << endl << "Time Taken: " << ((duration_cast<milliseconds>(stop - start)).count())/(1000.000);
    cout << endl;
}

bool BFSSolveUtil(queue<BoardQueue> boards)
{
    int numNodesExplored = 0;
    while(!boards.empty())
    {
        BoardQueue current = boards.front();
        
        if(validateCorrectBoard(current.board)){
            //GOAL STATE REACHED
            stop = high_resolution_clock::now(); 
            printResult(current, numNodesExplored);
            return true;
        } 
        BoardQueue moveBoard(current.emptySpot,current.board);
        numNodesExplored++;
        boards.pop();
        if(getRight(current.emptySpot)){
            moveBoard = goRight(current,moveBoard,current.emptySpot);
            if(!contains(moveBoard)){
                boards.push(BoardQueue(Point(current.emptySpot.x,current.emptySpot.y+1),moveBoard.board,current.moves+"R"));
                boardsVisted.insert(moveBoard);
            }
        }
        if(getLeft(current.emptySpot)){
            moveBoard = goLeft(current,moveBoard,current.emptySpot);
            if(!contains(moveBoard)){
                boards.push(BoardQueue(Point(current.emptySpot.x,current.emptySpot.y-1),moveBoard.board,current.moves+"L"));
                boardsVisted.insert(moveBoard);
            }
        }
        if(getDown(current.emptySpot)){
            moveBoard = goDown(current,moveBoard,current.emptySpot);
            if(!contains(moveBoard)){
                boards.push(BoardQueue(Point(current.emptySpot.x+1,current.emptySpot.y),moveBoard.board, current.moves+"D"));
                boardsVisted.insert(moveBoard);
            }
        }
        if(getUp(current.emptySpot)){
            moveBoard = goUp(current,moveBoard,current.emptySpot);
            if(!contains(moveBoard)){
                boards.push(BoardQueue(Point(current.emptySpot.x-1,current.emptySpot.y),moveBoard.board,current.moves+"U"));
                boardsVisted.insert(moveBoard);
            }
        }
    }
    return false;
}

bool BFSSolve()
{
    queue<BoardQueue> points;
    points.push(BoardQueue(getEmptySpot(),BOARD));
    return BFSSolveUtil(points);
}

int main(){
    int input[] = {1,0,2,4,5,7,3,8,9,6,11,12,13,10,14,15};
    populateBoard(input);
    // printBoard();
    start = high_resolution_clock::now(); 
    BFSSolve();
    // printBoard();
    
}