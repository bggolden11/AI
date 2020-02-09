#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

#define BOARD_WIDTH 4
#define BOARD_HEIGHT 4
#define INPUT_SIZE 16

int BOARD[BOARD_HEIGHT][BOARD_WIDTH];
bool populateBoard(int input[BOARD_HEIGHT][BOARD_WIDTH], int output[BOARD_HEIGHT][BOARD_WIDTH]);

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
    
    BoardQueue(Point emptySpot, int board[BOARD_HEIGHT][BOARD_WIDTH]){
        this->emptySpot = Point(emptySpot.x,emptySpot.y);
        populateBoard(board,this->board);
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

Point getUp(Point point){
    Point newPoint = Point(point.x,point.y+1);
    if(isValidPoint(newPoint))
        return newPoint;
    else 
        return Point(-1,-1);
}

Point getDown(Point point){
    Point newPoint = Point(point.x,point.y-1);
    if(isValidPoint(newPoint))
        return newPoint;
    else 
        return Point(-1,-1);
}

Point getRight(Point point){
    Point newPoint = Point(point.x+1,point.y);
    if(isValidPoint(newPoint))
        return newPoint;
    else 
        return Point(-1,-1);
}

Point getLeft(Point point){
    Point newPoint = Point(point.x-1,point.y);
    if(isValidPoint(newPoint))
        return newPoint;
    else 
        return Point(-1,-1);
}

vector<Point> getAll(Point point)
{
    vector<Point> points;
    points.push_back(getUp(point));
    points.push_back(getDown(point));
    points.push_back(getRight(point));
    points.push_back(getLeft(point));
    return points;
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

bool populateBoard(int input[BOARD_HEIGHT][BOARD_WIDTH], int output[BOARD_HEIGHT][BOARD_WIDTH]){
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
            if(board[x][y] != correct[correctCounter]) return false
            correctCounter++;
        }
            
}

bool BFSFixUtil(queue<Point> points)
{
    while(!points.empty())
    {
        Point current = points.front();
        points.pop();
        vector<Point> allPoints = getAll(current);
    }
    return true;
}

int BFSFix()
{
    queue<Point> points;
    points.push(getEmptySpot());
    BFSFixUtil(points);
    return 3;
}



int main(){
    int input[] = {1,0,2,4,5,7,3,8,9,6,11,12,13,10,14,15};
    populateBoard(input);
    printBoard();
    BoardQueue x = BoardQueue(Point(),BOARD);
    printBoard(x.board);
    cout << endl;
 Point emptySpot = getEmptySpot();
    cout << emptySpot.x << " " << emptySpot.y;
}