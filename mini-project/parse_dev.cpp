#include "suduko.h"

void ParseFile(std::string _filename, std::vector<std::string> &_puzzles) {
    std::ifstream file(_filename);
    std::string line;
    while(std::getline(file, line)) {
        _puzzles.push_back(line);
    }
}

void BuildPuzzleGrid(std::string _puzzle, Cell (&puzzle)[N][N]) {
    int col = 0;
    int row = 0;
    for (size_t i = 0; i < _puzzle.length(); i++) {
        if (col >= 9) {
            col = 0;
            row++;
        } 
        char character = _puzzle[i];
        if (character > '0' and character <= '9') {
            puzzle[row][col].value = _puzzle[i] -'0';
        } else {
            puzzle[row][col].value = 0;
        }
        puzzle[row][col].hypos = {1,2,3,4,5,6,7,8,9};
        PopulateUnitsAndPeers(puzzle, row, col);
        col++;
    }
}

void BuildUnitsAndPeers(Cell (&puzzle)[N][N]) {
    for (unsigned int row = 0; row < N; row++) {
        for (unsigned int col = 0; col < N; col++) {
            PopulateUnitsAndPeers(puzzle, row, col);
        }
    }
}

void PopulateUnitsAndPeers(Cell (&puzzle)[N][N], unsigned const int &_row, unsigned const int &_col) {
    unsigned int counter = 0;
    std::set<std::string> peers_set;
    // Row unit
    for (int col = 0; col < 9; col++) {
        puzzle[_row][_col].Units[0][counter].row = _row;
        puzzle[_row][_col].Units[0][counter].col = col;
        peers_set.insert(std::to_string(_row) + std::to_string(col));
        counter++;
    }
    counter = 0;
    // Column unit
    for (int row = 0; row < 9; row++) {
        puzzle[_row][_col].Units[1][counter].row = row;
        puzzle[_row][_col].Units[1][counter].col = _col;
        peers_set.insert(std::to_string(row) + std::to_string(_col));
        counter++;
    }
    // Box unit
    counter = 0;
    int boxStartRow = _row - _row % 3;
    int boxStartCol = _col - _col % 3;
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            puzzle[_row][_col].Units[2][counter].row = row + boxStartRow;
            puzzle[_row][_col].Units[2][counter].col = col + boxStartCol;
            peers_set.insert(std::to_string(row + boxStartRow) + std::to_string(col + boxStartCol));
            counter++;
        }
    }
    counter = 0;
    // Remove current cell
    peers_set.erase(std::to_string(_row) + std::to_string(_col));
    for (auto peer : peers_set) {
        puzzle[_row][_col].Peers[counter].row = peer[0]-'0';
        puzzle[_row][_col].Peers[counter].col = peer[1]-'0';
        counter++;
    }
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

void PrintGridAsLine(Cell (&puzzle)[N][N]/* , unsigned const int &_nr, unsigned const int _guesses */) {
    // std::cout << "Puzzle " << _nr;
    // if(_guesses == 0) {
    //     std::cout << " solved w/o search (only Const. Prop.): \t";
    // } else {
    //     std::cout << " solved after " << _guesses << " guesses: \t\t\t";
    // }
    
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