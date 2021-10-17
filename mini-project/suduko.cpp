#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream> 
#include <vector> 
#define N 9

typedef struct struct_cell {
    unsigned int value;
    std::vector<int> possibilites;
}Cell;

bool FindUnassignedLocation(Cell (&puzzle)[N][N], int &row, int &col);
bool isSafe(Cell (&puzzle)[N][N], int row, int col, int num);
void ConstraintPropagation(Cell (&puzzle)[N][N]);
void RemovePeerInRow(Cell (&puzzle)[N][N], int row, int num);
void RemovePeerInCol(Cell (&puzzle)[N][N], int col, int num);
void RemovePeerInBox(Cell (&puzzle)[N][N], int boxStartRow, int boxStartCol, int num);
void printCell(Cell (&puzzle)[N][N], const int &row, const int &col);
void setValue(Cell (&puzzle)[N][N], const int &row, const int &col);

void DeleteValueInVector(Cell (&puzzle)[N][N], const int &row, const int &col, const int &num) {
    for (unsigned i=0; i<puzzle[row][col].possibilites.size(); i++) {
        if (puzzle[row][col].possibilites[i] == num) {
            puzzle[row][col].possibilites.erase(puzzle[row][col].possibilites.begin() + i);
        }
    }
    if (puzzle[row][col].possibilites.size() == 1) {
        setValue(puzzle, row, col);
    }
}

void RemovePeerInRow(Cell (&puzzle)[N][N], int row, int num) {
    for (int col = 0; col < N; col++) {
        DeleteValueInVector(puzzle, row, col, num);
    }
}
void RemovePeerInCol(Cell (&puzzle)[N][N], int col, int num) {
    for (int row = 0; row < N; row++) {
        DeleteValueInVector(puzzle, row, col, num);
    }
}
void RemovePeerInBox(Cell (&puzzle)[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            DeleteValueInVector(puzzle, row+boxStartRow, col+boxStartCol, num);
        }
    }
}

void removeFromPeers(Cell (&puzzle)[N][N], const int &row, const int &col, int &num) {
    RemovePeerInRow(puzzle, row, num);
    RemovePeerInCol(puzzle, col, num);
    RemovePeerInBox(puzzle, row - row % 3 , col - col % 3, num);
}

void setValue(Cell (&puzzle)[N][N], const int &row, const int &col) {
    int num = puzzle[row][col].possibilites[0];
    puzzle[row][col].value = num;
    puzzle[row][col].possibilites.clear();
    removeFromPeers(puzzle, row, col, num);
}

void ConstraintPropagation(Cell (&puzzle)[N][N]) {
    int row, col;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col].value == 0) {
                // std::cout << "Visiting empty cell " << row << ":" << col << std::endl;
                // printCell(puzzle, row, col);
                for (int num = 1; num <= 9; num++) {
                    if (!isSafe(puzzle, row, col, num)) {
                        DeleteValueInVector(puzzle, row, col, num);
                    }
                }
            } else {
                // std::cout << "Visiting defined cell " << row << ":" << col << std::endl;
                int num = puzzle[row][col].value;
                puzzle[row][col].possibilites.clear();
                removeFromPeers(puzzle, row, col, num);
            }
        }
    }

}

void printCell(Cell (&puzzle)[N][N], const int &row, const int &col) {
    std::cout << row << ":" << col << ", ";
    std::cout << "Value: " << puzzle[row][col].value << ", ";
    std::cout << "possibilities: ";
    for (unsigned i=0; i<puzzle[row][col].possibilites.size(); i++) {
        std::cout << ' ' << puzzle[row][col].possibilites.at(i);
    }
    std::cout << std::endl;
}

void printCells(Cell (&puzzle)[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printCell(puzzle, row, col);
        }
    }
}

/* assign values to all unassigned locations for Sudoku solution  
 */
bool SolveSudoku(Cell (&puzzle)[N][N]) {
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
            puzzle[row][col].value = 0;
        }   
    }
    return false;
}

/* Searches the grid to find an entry that is still unassigned. */
bool FindUnassignedLocation(Cell (&puzzle)[N][N], int &row, int &col) {
    // row and col are passed by reference and are therefore assigned 
    // "in place" in stack memory. This is where the current worlking
    // cell is set.
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col].value == 0) {
                return true;
            }   
        }
    }
    return false;
}

/* Returns whether any assigned entry in the specified row matches 
   the given number. */
bool UsedInRow(Cell (&puzzle)[N][N], int row, int num) {
    for (int col = 0; col < N; col++) {
        if (puzzle[row][col].value == num) {
            return true;
        }
    }
    return false;
}

/* Returns whether any assigned entry in the specified column matches 
   the given number. */
bool UsedInCol(Cell (&puzzle)[N][N], int col, int num) {
    for (int row = 0; row < N; row++) {
        if (puzzle[row][col].value == num) {
            return true;
        }
    }
    return false;
}

/* Returns whether any assigned entry within the specified 3x3 box matches 
   the given number. */
bool UsedInBox(Cell (&puzzle)[N][N], int boxStartRow, int boxStartCol, int num) {
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
bool isSafe(Cell (&puzzle)[N][N], int row, int col, int num) {
    return !UsedInRow(puzzle, row, num) && !UsedInCol(puzzle, col, num) &&
       !UsedInBox(puzzle, row - row % 3 , col - col % 3, num);
}

void PrintGrid(Cell (&puzzle)[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            std::cout<<puzzle[row][col].value<<"  ";

            if (col == 2 || col == 5) {
                std::cout << "|  ";
            }
        }
        std::cout << "\n";
        if (row == 2 || row == 5) {
            std::cout << "---------+-----------+---------\n";
        }
    }
    std::cout<<std::endl;
}

void ParseFile(std::string filename, Cell (&puzzle)[N][N]) {
    std::string line;
    std::ifstream myFile(filename);
    if (!myFile.is_open()) {
        throw std::runtime_error("Could not open file");
    } 
    if (myFile.good()) {
        int row = 0;
        while(getline(myFile, line)) {
            std::stringstream ss(line);
            int col = 0;
            for (size_t i = 0; i < line.length(); i++) {
                if (col >= 9) {
                    col = 0;
                    row++;
                } 
                char character = line[i];
                if (character > '0' and character <= '9') {
                    puzzle[row][col].value = line[i] -'0';
                } else {
                    puzzle[row][col].value = 0;
                }
                puzzle[row][col].possibilites = {1,2,3,4,5,6,7,8,9};
                col++;
            }
            row++;
        }
    }
    myFile.close();
}

int main(int argc, char *argv[]) {
    if (!argv[1]) {
        std::cout << "Input file needed. Aborting..." << std::endl;
        return 1;
    } 
    Cell puzzle[N][N];
    ParseFile(argv[1], puzzle);
    std::cout<<"~~~~~~~~~~~~ INPUT ~~~~~~~~~~~~"<<std::endl;
    PrintGrid(puzzle);
    ConstraintPropagation(puzzle);
    std::cout<<"~ After constraint propagation~"<<std::endl;
    PrintGrid(puzzle);
    if (SolveSudoku(puzzle) == true) {
        std::cout<<"~~~~~~ After Brute Force ~~~~~~"<<std::endl;
        PrintGrid(puzzle);
    } else {
        std::cout<<"No solution exists"<<std::endl;
    }
    return 0;
}
