#include <fstream>
#include "gameOfLife.h"

using namespace std;

/*
Function to clear terminal depending on OS
*/
void clearScreen()
{
    // use "cls" in windows and "clear" command in Mac and Linux
    #ifdef _WIN32
        system("clS");
    #else
        system("clear");
    #endif
}

/*
Function to initialize all cells in the board.
Takes in 2D array of pointers and size of array
Should create structs and populate the array
*/
void initCells(Cell* board[][10], int boardSize)
{
    for (int y = 0; y < boardSize; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            board[y][x] = new Cell;
            board[y][x]->x = x;
            board[y][x]->y = y;
            board[y][x]->state = 0;
            board[y][x]->numLiveNeighbors = 0;
        }
    }

}

/*
Function to read the board from a file
Prompt for the file to read inside of the function
Structure of file should consist of 10 lines of 0 or 1 to indicate cell state
*/
void readBoard(Cell* board[][10], int boardSize) 
{

    string fileName;
    cout << "please enter a starting board state file: "<< endl;
    cin >> fileName;

    ifstream fileIn(fileName);
    if(fileIn.is_open()){
        for (int y = 0; y < boardSize; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                char c;
                fileIn >> c;
                if(!fileIn){
                    cout << "file is too short\n";
                    return;
                }
                if (c == '1'){
                    board[y][x]->state = 1;
                } else if (c == '0'){
                    board[y][x]->state = 0;
                }
                else{
                    cout << c << " is an invalid character\n";
                }

            }
        }
    } else {
        cout << "Could not open " << fileName << endl;
        return;
    }
    // eat the trailing newline so main's cin.get() works
    cin.ignore(10000, '\n');
}

/*
Function to print out all cells to cout
*/
void printCells(Cell* board[][10], int boardSize)
{
    for (int y = 0; y < boardSize; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                cout << board[y][x]->state;
            }
            cout << '\n';
        }

}

/*
Function to count the number of live neighbors for each cell.
Must use the x, y position stored with each cell to determine which neighbors they have
*/
void findNumNeighbors(Cell* board[][10], int boardSize, Cell* curCell) 
{
    //label x & y to make calling them clearer
    int x = curCell->x;
    int y = curCell->y;
    int neighbors = 0;
    
    //use -1 0 1 on both x and y to see who is around me
    for(int changeInY = -1; changeInY <=1; changeInY++){
        for(int changeInX = -1; changeInX <=1; changeInX++){
            if (changeInX == 0 && changeInY == 0) continue;  // self
            int neighborX = x + changeInX;
            int neighborY = y + changeInY;
            if (neighborY >= 0 && neighborY < boardSize && neighborX >= 0 && neighborX < 10){
                if (board[neighborY][neighborX]-> state == 1) neighbors++;
            }
        }
    }
    curCell->numLiveNeighbors = neighbors;

}

/*
Function to update each cell's state based on number of neighbors
Must use following rules:

Any live cell with fewer than two live neighbors dies, as if by underpopulation.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by overpopulation.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.

Return if you updated cells or not to break out of while loop from main.
*/
bool updateCellState(Cell* board[][10], int boardSize) 
{
    for (int y = 0; y < boardSize; y++)
        {
            for (int x = 0; x < 10; x++)
            {
                findNumNeighbors(board, boardSize, board[y][x]);
            }
        }
    
    for (int y = 0; y < boardSize; y++)
    {
        for (int x = 0; x < 10; x++)
        {
            if (board[y][x]->state == 1) {                  //alive cells
                if(board[y][x]->numLiveNeighbors<2){
                    board[y][x]->state = 0; // cell dies underpop
                } else if (board[y][x]->numLiveNeighbors == 2 || board[y][x]->numLiveNeighbors == 3){
                    board[y][x]->state = 1; //cell survives
                } else if (board[y][x]-> numLiveNeighbors > 3){
                    board[y][x]->state = 0; // cell dies overpop
                }

            } else {                                        // dead cells
                if(board[y][x]->numLiveNeighbors == 3) {
                    board[y][x]->state = 1; //comes back to life
                }
                else {
                    board[y][x]->state = 0; //stays dead
                }
            }
        }
    }


    return true;
}