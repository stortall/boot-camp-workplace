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
    unsigned int peer_row, peer_col;
    for (Coord_t peers : puzzle[row][col].Peers) {
        if (IsValueInHypos(puzzle[peers.row][peers.col].hypos, num)) {
            CheckUnits(puzzle, peers.row, peers.col);
        }
    }
    // VisitRowPeers(puzzle, row, col, num);
    // VisitColPeers(puzzle, row, col, num);
    // VisitBoxPeers(puzzle, row, col, num);
}

void DeleteHypo(Cell (&puzzle)[N][N], int row, int col, int num) {
    for (unsigned i = 0; i < puzzle[row][col].hypos.size(); i++) {
        if (puzzle[row][col].hypos[i] == num) {
            // // Debugging
            // std::string hypos_str;
            // for (unsigned i = 0; i < puzzle[row][col].hypos.size(); i++) {
            //     hypos_str = hypos_str + "," + std::to_string(puzzle[row][col].hypos[i]);
            // }
            // std::cout << "removing hypo " << num << " from peer (" << row << "," << col << ") hypo vector: " << hypos_str << std::endl;
            // // Debugging end
            puzzle[row][col].hypos.erase(puzzle[row][col].hypos.begin() + i);
            VisitPeers(puzzle, row, col, num);
        }
    }
    if (puzzle[row][col].hypos.size() == 1) {
        // std::cout << "Trying to set value in (" << row << "," << col << ")" << std::endl;
        setValue(puzzle, row, col);
    }
}

void RemovePeerInRow(Cell (&puzzle)[N][N], int row, int num) {
    for (int col = 0; col < N; col++) {
        DeleteHypo(puzzle, row, col, num);
    }
}
void RemovePeerInCol(Cell (&puzzle)[N][N], int col, int num) {
    for (int row = 0; row < N; row++) {
        DeleteHypo(puzzle, row, col, num);
    }
}
void RemovePeerInBox(Cell (&puzzle)[N][N], int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            DeleteHypo(puzzle, row+boxStartRow, col+boxStartCol, num);
        }
    }
}

void RemoveFromPeers(Cell (&puzzle)[N][N], int row, int col, int num) {
    // std::cout << "removing " << num << " from peers to (" << row << "," << col << ")" << std::endl;
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
        // std::cout << "setting " << num << " in (" << row << "," << col << ")" << std::endl;
        puzzle[row][col].value = num;
        puzzle[row][col].hypos.clear();   
        // PrintGridState(puzzle); 
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
            // std::cout << "Unique peer in unit found, setting " << num << " in (" << row << "," << col << ")" << std::endl;
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
    
    int row, col;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col].value == 0) {
                // Visiting empty cell
                for (int num = 1; num <= 9; num++) {
                    // Eliminate possible value if value NOT possible in cell
                    if (!isPossible(puzzle, row, col, num)) {
                        DeleteHypo(puzzle, row, col, num);
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

/* assign values to all unassigned locations for Sudoku solution  
 */
bool SolveSudoku(Cell (&puzzle)[N][N], unsigned int &_guesses) {
    int row, col;
    // row and int are assigned by reference in function
    // FindUnassignedLocation() 
    // if (!FindUnassignedLocation(puzzle, row, col)) {
    if (!FindFewestHypoCell(puzzle, row, col)) {
        return true;
    }
    // std::cout << row << ":" << col << std::endl;
    // "num" is the guess to put in a cell
    // if (puzzle[row][col].hypos.empty()) {
    //     std::cout << "EMPTY CELL WITH EMPTY HYPO (" << row << "," << col << ")" << std::endl;
    //     for (int& num: puzzle[row][col].hypos) {
    //         std::cout << "loop" << std::endl;
    //     }
    // }
    // Copy puzzle
    Cell puzzle_copy[N][N];
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            puzzle_copy[i][j] = puzzle[i][j];
        }
    }
    for (int& num: puzzle[row][col].hypos) {
        if (isPossible(puzzle, row, col, num)) {
            // puzzle[row][col].value = num;
            
            // memcpy((&puzzle_copy), (&puzzle), sizeof(puzzle));
            // PrintGridState(puzzle_copy);
            // std::copy(std::begin(puzzle), std::end(puzzle), std::begin(puzzle_copy));
            // std::cout << "MAKING NEW GUESS" << std::endl;
            setValue(puzzle, row, col, num);
            // std::cout << "AFTER MAKING NEW GUESS" << std::endl;
            // std::cout << "PUZZLE:" << std::endl;
            // PrintGridState(puzzle);
            // std::cout << "PUZZLE COPY:" << std::endl;
            // PrintGridState(puzzle_copy);
            _guesses++;
            if (SolveSudoku(puzzle, _guesses)) {
                return true;
            }
            // std::cout << "AFTER IF" << std::endl;
            // // puzzle[row][col].value = 0;
            // PrintGridState(puzzle);
        }
        // Reset puzzle
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                puzzle[i][j] = puzzle_copy[i][j];
            }
        }
    }
    // memcpy((&puzzle), (&puzzle_copy), sizeof(puzzle));
    
    // std::cout << "BEFORE RETURN FALSE" << std::endl;
    // PrintGridState(puzzle);
    return false;
}

/* Searches the grid to find the cell with fewest hypos */
bool FindFewestHypoCell(Cell (&puzzle)[N][N], int &_row, int &_col) {
    // row and col are passed by reference and are therefore assigned 
    // "in place" in stack memory. This is where the current working
    // cell is set.
    
    int fewest = 10;
    bool ret = false;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            
            if (puzzle[row][col].value == 0) {
                // std::cout << (puzzle[row][col].hypos.size() < fewest) << std::endl;
                ret = true;
                if (puzzle[row][col].hypos.size() < fewest) {
                    fewest = puzzle[row][col].hypos.size();
                    _row = row;
                    _col = col;
                    // std::cout << row << ":" << col << std::endl;
                }
            }   
        }
    }
    return ret;
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




