#include "suduko.h"

bool IsValueInHypos(std::vector<int> &hypos, int num) {
    for (int& hypo: hypos) {
        if (hypo == num) {
            return true;
        }
    }
    return false;
}

void VisitRowPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num) {
    for (int col = 0; col < N; col++) {
        if (col != _col) {
            if (IsValueInHypos(puzzle[_row][col].hypos, _num)) {
                CheckUnits(puzzle, _row, col);
            }
        }
    }
}

void VisitColPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num) {
    for (int row = 0; row < N; row++) {
        if (row != _row) {
            if (IsValueInHypos(puzzle[row][_col].hypos, _num)) {
                CheckUnits(puzzle, row, _col);
            }
        }
    }
}

void VisitBoxPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num) {
    int boxStartRow = _row - _row % 3;
    int boxStartCol = _col - _col % 3;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (!(row + boxStartRow == _row && col + boxStartCol == _col)) {
                if (IsValueInHypos(puzzle[row + boxStartRow][col + boxStartCol].hypos, _num)) {
                    CheckUnits(puzzle, row + boxStartRow, col + boxStartCol);
                } 
            }
        }
    }
}

void VisitPeers(Cell (&puzzle)[N][N], int row, int col, int num) {
    VisitRowPeers(puzzle, row, col, num);
    VisitColPeers(puzzle, row, col, num);
    VisitBoxPeers(puzzle, row, col, num);
}

void DeleteValueInVector(Cell (&puzzle)[N][N], int row, int col, int num) {
    for (unsigned i = 0; i < puzzle[row][col].hypos.size(); i++) {
        if (puzzle[row][col].hypos[i] == num) {
            puzzle[row][col].hypos.erase(puzzle[row][col].hypos.begin() + i);
            VisitPeers(puzzle, row, col, num);
        }
    }
    if (puzzle[row][col].hypos.size() == 1) {
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

void RemoveFromPeers(Cell (&puzzle)[N][N], int row, int col, int num) {
    RemovePeerInRow(puzzle, row, num);
    RemovePeerInCol(puzzle, col, num);
    RemovePeerInBox(puzzle, row - row % 3 , col - col % 3, num);
}

void setValue(Cell (&puzzle)[N][N], int row, int col, int _num) {
    int num;
    if (_num == 0) {
        num = puzzle[row][col].hypos[0];
    } else {
        num = _num;
    }
    if (isPossible(puzzle, row, col, num)) {
        puzzle[row][col].value = num;
        puzzle[row][col].hypos.clear();    
        RemoveFromPeers(puzzle, row, col, num);
    }
}

/* For a given Cell defined by (_row, _col), returns true if Value (_num) is in 
 any of the peers vector Hypos.
 */
bool IsHypoInRowPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num) {
    for (int col = 0; col < N; col++) {
        if (col != _col) {
            if (std::count(puzzle[_row][col].hypos.begin(), puzzle[_row][col].hypos.end(), _num)) {
                return true;
            }
        }
    }
    return false;
}

bool IsHypoInColPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num) {
    for (int row = 0; row < N; row++) {
        if (row != _row) {
            if (std::count(puzzle[row][_col].hypos.begin(), puzzle[row][_col].hypos.end(), _num)) {
                return true;
            }
        }
    }
    return false;
}

bool IsHypoInBoxPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num) {
    int boxStartRow = _row - _row % 3;
    int boxStartCol = _col - _col % 3;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (!(row + boxStartRow == _row && col + boxStartCol == _col)) {
                if (std::count(puzzle[row + boxStartRow][col + boxStartCol].hypos.begin(), puzzle[row + boxStartRow][col + boxStartCol].hypos.end(), _num)) {
                    return true;
                } 
            }
        }
    }
    return false;
}

/* For a given Cell, check if any of the possible numbers are unique in 
any of the three Units.
 */
void CheckUnits(Cell (&puzzle)[N][N], int row, int col) {
    int num;
    for (size_t i = 0; i < puzzle[row][col].hypos.size(); i++) {
        num = puzzle[row][col].hypos[i];
        if (!IsHypoInRowPeers(puzzle, row, col, num) || 
            !IsHypoInColPeers(puzzle, row, col, num) || 
            !IsHypoInBoxPeers(puzzle, row, col, num)) {
            setValue(puzzle, row, col, num);
        }
    }        
}

void CleanHypoValues(Cell (&puzzle)[N][N]) {
    int row, col;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col].value != 0) {
                puzzle[row][col].hypos.clear();
            }
        }
    }
}

void ConstraintPropagation(Cell (&puzzle)[N][N]) {
    CleanHypoValues(puzzle);
    int row, col;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col].value == 0) {
                // Visiting empty cell
                for (int num = 1; num <= 9; num++) {
                    // Eliminate possible value if value NOT possible in cell
                    if (!isPossible(puzzle, row, col, num)) {
                        DeleteValueInVector(puzzle, row, col, num);
                    }
                }
                CheckUnits(puzzle, row, col);
            } else {
                // Visiting defined cell
                int num = puzzle[row][col].value;
                puzzle[row][col].hypos.clear();
                RemoveFromPeers(puzzle, row, col, num);
            }
        }
    }

}

void printCell(Cell (&puzzle)[N][N], int row, int col) {
    std::cout << row << ":" << col << ", ";
    std::cout << "Value: " << puzzle[row][col].value << ", ";
    std::cout << "hypos: ";
    for (unsigned i=0; i<puzzle[row][col].hypos.size(); i++) {
        std::cout << ' ' << puzzle[row][col].hypos.at(i);
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
    for (int& num: puzzle[row][col].hypos) {
        if (isPossible(puzzle, row, col, num)) {
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
bool isPossible(Cell (&puzzle)[N][N], int row, int col, int num) {
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
    unsigned int hypo_size;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            hypo_size = puzzle[row][col].hypos.size();
            if (hypo_size > max_size) {
                max_size = hypo_size;
            }
        }
    }
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (puzzle[row][col].value == 0) {
                for (size_t i = 0; i < max_size; i++) {
                    if (i < puzzle[row][col].hypos.size()) {
                        std::cout<<puzzle[row][col].hypos[i];
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
                puzzle[row][col].hypos = {1,2,3,4,5,6,7,8,9};
                col++;
            }
            row++;
        }
    }
    myFile.close();
}
