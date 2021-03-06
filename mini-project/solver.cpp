#include "solver.h"

Solver::Solver(Cell_t _puzzle[9][9], std::string _oneLinePuzzle) {
    // Copy puzzle template
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            puzzle[i][j] = _puzzle[i][j];
        }
    }
    BuildPuzzleGrid(_oneLinePuzzle);
    guesses = 0;
}

void Solver::BuildPuzzleGrid(std::string _oneLinePuzzle) {
    int col = 0;
    int row = 0;
    for (size_t i = 0; i < _oneLinePuzzle.length(); i++) {
        if (col >= 9) {
            col = 0;
            row++;
        } 
        char character = _oneLinePuzzle[i];
        if (character > '0' and character <= '9') {
            puzzle[row][col].value = _oneLinePuzzle[i] -'0';
        } else {
            puzzle[row][col].value = 0;
            puzzle[row][col].hypos = {1,2,3,4,5,6,7,8,9};
        }
        col++;
    }
}

void Solver::PropagatateConstraints() {
    int row, col;
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (puzzle[row][col].value == 0) {
                // Visiting empty cell
                for (int num = 1; num <= 9; num++) {
                    // Eliminate possible value if value NOT possible in cell
                    if (!isPossible(row, col, num)) {
                        DeleteHypo(row, col, num);
                    }
                }
                CheckUnits(row, col);
            } else {
                // Visiting defined cell
                int num = puzzle[row][col].value;
                puzzle[row][col].hypos.clear();
                RemoveFromPeers(row, col, num);
            }
        }
    }
}

/* Returns whether it will be legal to assign num to the given row,col location. 
 */
bool Solver::isPossible(unsigned const int &row, unsigned const int &col, unsigned const int &num) {
    return !UsedInRow(row, num) && !UsedInCol(col, num) &&
       !UsedInBox(row - row % 3 , col - col % 3, num);
}

/* Returns whether any assigned entry in the specified row matches 
   the given number. */
bool Solver::UsedInRow(unsigned const int &row, unsigned const int &num) {
    for (int col = 0; col < N; col++) {
        if (puzzle[row][col].value == num) {
            return true;
        }
    }
    return false;
}

/* Returns whether any assigned entry in the specified column matches 
   the given number. */
bool Solver::UsedInCol(unsigned const int &col, unsigned const int &num) {
    for (int row = 0; row < N; row++) {
        if (puzzle[row][col].value == num) {
            return true;
        }
    }
    return false;
}

/* Returns whether any assigned entry within the specified 3x3 box matches 
   the given number. */
bool Solver::UsedInBox(unsigned const int &boxStartRow, unsigned const int &boxStartCol, unsigned const int &num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (puzzle[row+boxStartRow][col+boxStartCol].value == num) {
                return true;
            } 
        }
    }
    return false;
}

void Solver::DeleteHypo(unsigned const int &row, unsigned const int &col, unsigned const int &num) {
    for (unsigned i = 0; i < puzzle[row][col].hypos.size(); i++) {
        if (puzzle[row][col].hypos[i] == num) {
            puzzle[row][col].hypos.erase(puzzle[row][col].hypos.begin() + i);
            VisitPeers(row, col, num);
        }
    }
    if (puzzle[row][col].hypos.size() == 1) {
        setValue(row, col);
    }
}

void Solver::VisitPeers(unsigned const int &row, unsigned const int &col, unsigned const int &num) {
    // unsigned int peer_row, peer_col;
    for (Coord_t peers : puzzle[row][col].Peers) {
        if (IsValueInHypos(puzzle[peers.row][peers.col].hypos, num)) {
            CheckUnits(peers.row, peers.col);
        }
    }
}

bool Solver::IsValueInHypos(std::vector<int> &hypos, unsigned const int &num) {
    for (int& hypo: hypos) {
        if (hypo == num) {
            return true;
        }
    }
    return false;
}

/* For a given Cell, check if any of the possible numbers are unique in 
any of the three Units.
 */
void Solver::CheckUnits(unsigned const int &row, unsigned const int &col) {
    int num;
    for (size_t i = 0; i < puzzle[row][col].hypos.size(); i++) {
        num = puzzle[row][col].hypos[i];
        if (!IsHypoInRowPeers(row, col, num) || 
            !IsHypoInColPeers(row, col, num) || 
            !IsHypoInBoxPeers(row, col, num)) {
            setValue(row, col, num);
        }
    }        
}

void Solver::setValue(unsigned const int &row, unsigned const int &col, int _num) {
    int num;
    if (_num == 0) {
        num = puzzle[row][col].hypos[0];
    } else {
        num = _num;
    }
    if (isPossible(row, col, num)) {
        puzzle[row][col].value = num;
        puzzle[row][col].hypos.clear();   
        RemoveFromPeers(row, col, num);
    }
}

void Solver::RemoveFromPeers(unsigned const int &row, unsigned const int &col, unsigned const int &num) {
    for (Coord_t peers : puzzle[row][col].Peers) {
        DeleteHypo(peers.row, peers.col, num);
    }
}

/* assign values to all unassigned locations for Sudoku solution  
 */
bool Solver::Search() {
    int row, col;
    // row and int are assigned by reference
    if (!FindFewestHypoCell(row, col)) {
        return true;
    }
    // Copy puzzle
    Cell_t puzzle_copy[N][N];
    for(size_t i = 0; i < N; i++){
        for(size_t j = 0; j < N; j++){
            puzzle_copy[i][j] = puzzle[i][j];
        }
    }
    for (int& num: puzzle[row][col].hypos) {
        if (isPossible(row, col, num)) {
            setValue(row, col, num);
            guesses++;
            if (Search()) {
                return true;
            }
        }
        // Reset puzzle
        for (size_t i = 0; i < N; i++) {
            for (size_t j = 0; j < N; j++) {
                puzzle[i][j] = puzzle_copy[i][j];
            }
        }
    }
    return false;
}

/* For a given Cell defined by (_row, _col), returns true if Value (_num) is in 
 any of the peers vector Hypos.
 */
bool Solver::IsHypoInRowPeers(unsigned const int &_row, unsigned const int &_col, unsigned const int &_num) {
    for (int col = 0; col < N; col++) {
        if (col != _col) {
            if (std::count(puzzle[_row][col].hypos.begin(), puzzle[_row][col].hypos.end(), _num)) {
                return true;
            }
        }
    }
    return false;
}

bool Solver::IsHypoInColPeers(unsigned const int &_row, unsigned const int &_col, unsigned const int &_num) {
    for (int row = 0; row < N; row++) {
        if (row != _row) {
            if (std::count(puzzle[row][_col].hypos.begin(), puzzle[row][_col].hypos.end(), _num)) {
                return true;
            }
        }
    }
    return false;
}

bool Solver::IsHypoInBoxPeers(unsigned const int &_row, unsigned const int &_col, unsigned const int &_num) {
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

/* Searches the grid to find the cell with fewest hypos */
bool Solver::FindFewestHypoCell(int &_row, int &_col) {
    // row and col are passed by reference and are therefore assigned 
    // "in place" in stack memory. This is where the current working
    // cell is set.
    int fewest = 10;
    bool ret = false;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (puzzle[row][col].value == 0) {
                ret = true;
                if (puzzle[row][col].hypos.size() < fewest) {
                    fewest = puzzle[row][col].hypos.size();
                    _row = row;
                    _col = col;
                }
            }   
        }
    }
    return ret;
}

void Solver::PrintGridAsLine() {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (puzzle[row][col].value > 0 && puzzle[row][col].value <= 9) {
                std::cout << puzzle[row][col].value;
            } else {
                std::cout << '.';
            }
            
        }
    }
    std::cout<<std::endl;
}

void Solver::PrintGrid() {
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

void Solver::PrintGridState() {
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
