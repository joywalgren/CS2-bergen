#include <iostream>
#include <string>
#include "gameOfLife.h"

using namespace std;

int main(int argc, char* argv[])
{
    int stage = 0;
    bool boardChanged = true;
    size_t boardSize = 10;
    Cell* board[10][10];

    initCells(board, boardSize);
    readBoard(board, boardSize);

    while(boardChanged) {
        clearScreen();
        cout << "Stage: " << stage << endl;

        printCells(board, boardSize);
        boardChanged = updateCellState(board, boardSize);

        cin.get();
        stage++;
    }

    // Clean up board if cells were allocated on the heap
    for (int y = 0; y < 10; y++) {
        for (int x = 0; x < 10; x++) {
            delete board[y][x];
            board[y][x] = nullptr;
        }
    }
    return 0;
}