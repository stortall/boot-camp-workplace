#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream> 
#include <vector> 
using namespace std;
#define UNASSIGNED 0
#define N 9

typedef struct struct_cell {
    unsigned int value;
    std::vector<int> possibilites;
}Cell;

bool FindUnassignedLocation(Cell **puzzle, int &row, int &col);
bool isSafe(Cell **puzzle, int row, int col, int num);
void FindPossible(Cell **puzzle);
void RemovePeerInRow(Cell **puzzle, int row, int num);
void RemovePeerInCol(Cell **puzzle, int col, int num);
void RemovePeerInBox(Cell **puzzle, int boxStartRow, int boxStartCol, int num);
void printCell(Cell **puzzle, const int &row, const int &col);
void setValue(Cell **puzzle, const int &row, const int &col);


void DeleteValueInVector(Cell **puzzle, const int &row, const int &col, const int &num) {
    for (unsigned i=0; i<puzzle[row][col].possibilites.size(); i++) {
        if (puzzle[row][col].possibilites[i] == num) {
            puzzle[row][col].possibilites.erase(puzzle[row][col].possibilites.begin() + i);
        }
    }
    if (puzzle[row][col].possibilites.size() == 1) {
        setValue(puzzle, row, col);
    }
}

void RemovePeerInRow(Cell **puzzle, int row, int num) {
    for (int col = 0; col < N; col++) {
        DeleteValueInVector(puzzle, row, col, num);
    }
}
void RemovePeerInCol(Cell **puzzle, int col, int num) {
    for (int row = 0; row < N; row++) {
        DeleteValueInVector(puzzle, row, col, num);
    }
}
void RemovePeerInBox(Cell **puzzle, int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            DeleteValueInVector(puzzle, row+boxStartRow, col+boxStartCol, num);
        }
    }
}

void removeFromPeers(Cell **puzzle, const int &row, const int &col, int &num) {
    RemovePeerInRow(puzzle, row, num);
    RemovePeerInCol(puzzle, col, num);
    RemovePeerInBox(puzzle, row - row % 3 , col - col % 3, num);
}

void setValue(Cell **puzzle, const int &row, const int &col) {
    int num = puzzle[row][col].possibilites[0];
    puzzle[row][col].value = num;
    puzzle[row][col].possibilites.clear();
    removeFromPeers(puzzle, row, col, num);
}

void FindPossible(Cell **puzzle) {
    int row, col;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col].value == UNASSIGNED) {
                cout << "Visiting empty cell " << row << ":" << col << endl;
                printCell(puzzle, row, col);
                for (int num = 1; num <= 9; num++) {
                    if (!isSafe(puzzle, row, col, num)) {
                        DeleteValueInVector(puzzle, row, col, num);
                    }
                }
            } else {
                cout << "Visiting defined cell " << row << ":" << col << endl;
                int num = puzzle[row][col].value;
                puzzle[row][col].possibilites.clear();
                removeFromPeers(puzzle, row, col, num);
            }
        }
    }

}

void printCell(Cell **puzzle, const int &row, const int &col) {
    cout << row << ":" << col << ", ";
    cout << "Value: " << puzzle[row][col].value << ", ";
    cout << "possibilities: ";
    for (unsigned i=0; i<puzzle[row][col].possibilites.size(); i++) {
        cout << ' ' << puzzle[row][col].possibilites.at(i);
    }
    cout << endl;
}

void printCells(Cell **puzzle) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printCell(puzzle, row, col);
        }
    }
}

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
            cout << "---------+-----------+---------\n";
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
                if (val == 0) {
                    for (size_t i = 1; i < 10; i++) {
                        puzzle[row][col].possibilites.push_back(i);
                    }
                }
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
    // cout<<"~~~~~~~~~~~~ INPUT ~~~~~~~~~~~~"<<endl;
    // printCells(puzzle);
    FindPossible(puzzle);
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    printCells(puzzle);
    cout<<"~~~~~~~~~~~ After constraint propagation ~~~~~~~~~~~~"<<endl;
    printGrid(puzzle);
    // if (SolveSudoku(puzzle) == true) {
    //     cout<<"~~~~~~~~~~~ OUTPUT ~~~~~~~~~~~~"<<endl;
    //     printGrid(puzzle);
    // } else {
    //     cout<<"No solution exists"<<endl;
    // }
    delete puzzle;
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