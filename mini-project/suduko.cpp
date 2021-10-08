#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream> 
using namespace std;
#define UNASSIGNED 0
#define N 9

typedef struct struct_cell {
    unsigned int value;
    char posibilities[9];
}Cell;

bool FindUnassignedLocation(Cell **puzzle, int &row, int &col);
bool isSafe(Cell **puzzle, int row, int col, int num);

/* assign values to all unassigned locations for Sudoku solution  
 */
bool SolveSudoku(Cell **puzzle) {
    int row, col;
    // row and int are assigned by reference in function
    // FindUnassignedLocation() 
    if (!FindUnassignedLocation(puzzle, row, col)) {
        return true;
    }
    // "num" is the guess to put in a cell
    for (int num = 1; num <= 9; num++) {
        if (isSafe(puzzle, row, col, num)) {
            puzzle[row][col].value = num;
            if (SolveSudoku(puzzle)) {
                return true;
            }
            puzzle[row][col].value = UNASSIGNED;
        }   
    }
    return false;
}

/* Searches the grid to find an entry that is still unassigned. */
bool FindUnassignedLocation(Cell **puzzle, int &row, int &col) {
    // row and col are passed by reference and are therefore assigned 
    // "in place" in stack memory. This is where the current worlking
    // cell is set.
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col].value == UNASSIGNED) {
                return true;
            }   
        }
    }
    return false;
}

/* Returns whether any assigned entry in the specified row matches 
   the given number. */
bool UsedInRow(Cell **puzzle, int row, int num) {
    for (int col = 0; col < N; col++) {
        if (puzzle[row][col].value == num) {
            return true;
        }
    }
    return false;
}

/* Returns whether any assigned entry in the specified column matches 
   the given number. */
bool UsedInCol(Cell **puzzle, int col, int num) {
    for (int row = 0; row < N; row++) {
        if (puzzle[row][col].value == num) {
            return true;
        }
    }
    return false;
}

/* Returns whether any assigned entry within the specified 3x3 box matches 
   the given number. */
bool UsedInBox(Cell **puzzle, int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (puzzle[row+boxStartRow][col+boxStartCol].value == num) {
                return true;
            } 
        }
    }
    return false;
}

/* Returns whether it will be legal to assign num to the given row,col location. 
 */
bool isSafe(Cell **puzzle, int row, int col, int num) {
    return !UsedInRow(puzzle, row, num) && !UsedInCol(puzzle, col, num) &&
       !UsedInBox(puzzle, row - row % 3 , col - col % 3, num);
}

void printGrid(Cell **puzzle) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            cout<<puzzle[row][col].value<<"  ";

            if (col == 2 || col == 5) {
                cout << "|  ";
            }
        }
        cout << "\n";
        if (row == 2 || row == 5) {
            cout << "-------------------------------\n";
        }
    }
    cout<<endl;
}

void parse_csv(string filename, Cell **puzzle) {
    // int grid[N][N];
    string line, colname;
    int val;
    ifstream myFile(filename);
    if (!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    } 
    if (myFile.good()) {
        int row = 0;
        while(getline(myFile, line)) {
            // cout << line << endl;
            puzzle[row] = new Cell[N];
            stringstream ss(line);
            int col = 0;
            while(ss >> val){
                puzzle[row][col].value = val;
                if(ss.peek() == ',') ss.ignore();
                col++;
            }
            row++;
        }
    }
    myFile.close();
}

int main(int argc, char *argv[]) {
    if (!argv[1]) {
        cout << "CSV file needed. Aborting..." << endl;
        return 1;
    } 
    Cell **puzzle = new Cell*[N];
    parse_csv(argv[1], puzzle);
    cout<<"~~~~~~~~~~~~ INPUT ~~~~~~~~~~~~"<<endl;
    printGrid(puzzle);
    if (SolveSudoku(puzzle) == true) {
        cout<<"~~~~~~~~~~~ OUTPUT ~~~~~~~~~~~~"<<endl;
        printGrid(puzzle);
    } else {
        cout<<"No solution exists"<<endl;
    }
    return 0;
}

// Example of how to return a pointer to two dimensional array
//
// Cell **CreateGrid(int grid[N][N], Cell **puzzle) {
//     Cell **puzzle = new Cell*[N];
//     for (size_t row = 0; row < N; row++) {
//         puzzle[row] = new Cell[N];
//         for (size_t col = 0; col < N; col++) {
//             puzzle[row][col].value = grid[row][col];
//         }
//     }
//     return puzzle;
// }

    // int grid[N][N] = {
    //     {3, 0, 6,   5, 0, 8,   4, 0, 0},
    //     {5, 2, 0,   0, 0, 0,   0, 0, 0},
    //     {0, 8, 7,   0, 0, 0,   0, 3, 1},

    //     {0, 0, 3,   0, 1, 0,   0, 8, 0},
    //     {9, 0, 0,   8, 6, 3,   0, 0, 5},
    //     {0, 5, 0,   0, 9, 0,   6, 0, 0},

    //     {1, 3, 0,   0, 0, 0,   2, 5, 0},
    //     {0, 0, 0,   0, 0, 0,   0, 7, 4},
    //     {0, 0, 5,   2, 0, 6,   3, 0, 0}
    // };

    // void CreatePuzzle(int grid[N][N], Cell **puzzle) {
//     for (size_t row = 0; row < N; row++) {
//         puzzle[row] = new Cell[N];
//         for (size_t col = 0; col < N; col++) {
//             puzzle[row][col].value = grid[row][col];
//         }
//     }
// }