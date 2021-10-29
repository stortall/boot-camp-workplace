#include "pre.h"

void ParseFile(std::string _filename, std::vector<std::string> &_puzzles) {
    std::ifstream file(_filename);
    std::string line;
    while(std::getline(file, line)) {
        _puzzles.push_back(line);
    }
}

void PopulateUnitsAndPeers(Cell (&puzzle)[9][9]) {
    for (unsigned int _row = 0; _row < 9; _row++) {
        for (unsigned int _col = 0; _col < 9; _col++) {
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
    }
}
