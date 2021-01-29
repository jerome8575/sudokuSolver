#include <iostream>

using namespace std;


// displays the sudoku board 
void printBoard(int sudokuBoard[9][9]){

    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            cout << sudokuBoard[i][j] << " ";
        }
        cout << endl;
    }
}

// finds the first free spot available, returns false if the board is complete
bool checkForFreeSpot(int sudokuBoard[9][9], int &r, int &c){
    
    for (int i = 0; i < 9; i++){
        for (int j = 0; j < 9; j++){
            if (sudokuBoard[i][j] == 0){
                r = i;
                c = j;
                return true;
            }
        }
    }
    return false;
}

// returns true if the num given is safe at this spot
bool isCorrect(int sudokuBoard[9][9], int row, int col, int num){
    // check if the num to try is already in the row
    for (int i = 0; i < 9; i++){
        if (sudokuBoard[row][i] == num){
            return false;
        }
    }
    // check if the num to try is already in the column
    for (int j = 0; j < 9; j++){
        if (sudokuBoard[j][col] == num){
            return false;
        }
    }

    // find which sub box the num is in
    int boxRow = row/3;
    int boxColumn = col/3;
    // check if the num to try is in the sub 3x3 box
    for (int k = boxRow*3; k < (boxRow*3) + 3; k++){
        for (int l = boxColumn*3; l < (boxColumn*3) + 3; l++){
            if (sudokuBoard[k][l] == num){
                return false;
            }
        }
    }

    return true;

}

// main algorithm
bool solve(int grid[9][9]){

    int row, col;
    // if theres no available space, the sudoku is solved
    // this function assigned row, grid an open space if one was found
    if (!checkForFreeSpot(grid, row, col)){
        return true;
    }

    // loops through numbers 1-9 and trys them at unnassigned spots
    for (int i = 1; i < 10; i++){
        if (isCorrect(grid, row, col, i)){
            grid[row][col] = i;
            // if this attempt solved the sudoku, return true
            if(solve(grid)){
                return true;
            }
            grid[row][col] = 0;
        }
    }

    // backtrack
    return false;


}

int main(){

    int sudokuBoard[9][9] = {{0,2,0,0,0,0,0,0,0},
                          {0,0,0,6,0,0,0,0,3}, 
                          {0,7,4,0,8,0,0,0,0},
                          {0,0,0,0,0,3,0,0,2},
                          {0,8,0,0,4,0,0,1,0},
                          {6,0,0,5,0,0,0,0,0},
                          {0,0,0,0,1,0,7,8,0},
                          {5,0,0,0,0,9,0,0,0},
                          {0,0,0,0,0,0,0,4,0}};

    if(solve(sudokuBoard)){
        printBoard(sudokuBoard);
    }
    else{
        cout << "Can't solve :( " << endl;
    }


    return 0;
}