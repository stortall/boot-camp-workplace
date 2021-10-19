#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream> 
#include <vector> 
#include <algorithm>
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
void setValue(Cell (&puzzle)[N][N], const int &row, const int &col, const int &_num=0);
void PrintGridState(Cell (&puzzle)[N][N]);

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

void setValue(Cell (&puzzle)[N][N], const int &row, const int &col, const int &_num) {
    int num;
    if (_num == 0) {
        num = puzzle[row][col].possibilites[0];
    } else {
        num = _num;
    }
    puzzle[row][col].value = num;
    puzzle[row][col].possibilites.clear();
    removeFromPeers(puzzle, row, col, num);
}

bool IsPossibilityInRowPeers(Cell (&puzzle)[N][N], const int &_row, const int &_col, int _num) {
    for (int col = 0; col < N; col++) {
        if (col != _col) {
            if (std::count(puzzle[_row][col].possibilites.begin(), puzzle[_row][col].possibilites.end(), _num)) {
                return true;
            }
        }
    }
    std::cout << "NOT Found possible number in row: " << _num << std::endl;
    return false;
}

bool IsPossibilityInColPeers(Cell (&puzzle)[N][N], const int &_row, const int &_col, int _num) {
    for (int row = 0; row < N; row++) {
        if (row != _row) {
            if (std::count(puzzle[row][_col].possibilites.begin(), puzzle[row][_col].possibilites.end(), _num)) {
                return true;
            }
        }
    }
    std::cout << "NOT Found possible number col: " << _num << std::endl;
    return false;
}

bool IsPossibilityInBoxPeers(Cell (&puzzle)[N][N], const int &_row, const int &_col, int _num) {
    int boxStartRow = _row - _row % 3;
    int boxStartCol = _col - _col % 3;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            
            if (!(row + boxStartRow == _row && col + boxStartCol == _col)) {
                // std::cout << "Visiting box peer: " << row + boxStartRow << ":" << col + boxStartCol << std::endl;
                if (std::count(puzzle[row + boxStartRow][col + boxStartCol].possibilites.begin(), puzzle[row + boxStartRow][col + boxStartCol].possibilites.end(), _num)) {
                    printCell(puzzle, row + boxStartRow, col + boxStartCol);
                    // std::cout << "Found possible number: " << _num << std::endl;
                    return true;
                } 
            }
        }
    }
    // std::cout << "NOT Found possible number in box: " << _num << std::endl;
    return false;
}

void CheckUnits(Cell (&puzzle)[N][N], const int &row, const int &col) {
    for (int& num: puzzle[row][col].possibilites) {
        std::cout << "checking " << row << ":" << col << " Possible number: " << num << std::endl;
        if (!IsPossibilityInRowPeers(puzzle, row, col, num) || !IsPossibilityInColPeers(puzzle, row, col, num) || !IsPossibilityInBoxPeers(puzzle, row, col, num)) {
            std::cout << "Setting value: " << row << ":" << col << " value: " << num << std::endl;
            setValue(puzzle, row, col, num);
        }
    }        
}

void CleanPossibleValues(Cell (&puzzle)[N][N]) {
    int row, col;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col].value != 0) {
                puzzle[row][col].possibilites.clear();
            }
        }
    }
}

void ConstraintPropagation(Cell (&puzzle)[N][N]) {
    CleanPossibleValues(puzzle);
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
                PrintGridState(puzzle);
                CheckUnits(puzzle, row, col);
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
    for (int& num: puzzle[row][col].possibilites) {
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

void PrintGridState(Cell (&puzzle)[N][N]) {
    unsigned int max_size = 1; 
    unsigned int possi_size;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            possi_size = puzzle[row][col].possibilites.size();
            if (possi_size > max_size) {
                max_size = possi_size;
            }
        }
    }
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (puzzle[row][col].value == 0) {
                for (size_t i = 0; i < max_size; i++) {
                    if (i < puzzle[row][col].possibilites.size()) {
                        std::cout<<puzzle[row][col].possibilites[i];
                    } else {
                        std::cout<< " ";
                    }
                }
                std::cout<<"  ";
            } else {
                std::cout<<puzzle[row][col].value;
                for (size_t i = 0; i < max_size-1; i++){
                    std::cout<< " ";
                }
                std::cout<<"  ";
            }
            if (col == 2 || col == 5) {
                std::cout << "|  ";
            }
        }
        std::cout << "\n";
        std::string dashes;
        dashes.insert(0, (max_size-1)*3, '-');
        if (row == 2 || row == 5) {
            std::cout << "---------" << dashes << "+-----------" << dashes << "+---------" << dashes << "\n";
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
    PrintGridState(puzzle);
    ConstraintPropagation(puzzle);
    std::cout<<"~ After constraint propagation~"<<std::endl;
    PrintGridState(puzzle);
    // if (SolveSudoku(puzzle) == true) {
    //     std::cout<<"~~~~~~ After Brute Force ~~~~~~"<<std::endl;
    //     PrintGrid(puzzle);
    // } else {
    //     std::cout<<"No solution exists"<<std::endl;
    // }
    return 0;
}
