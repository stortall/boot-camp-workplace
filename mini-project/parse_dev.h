#ifndef PARSEDEV
#define PARSEDEV
#include "solver.h"

// void PrintGrid(Cell (&puzzle)[N][N]);
// void PrintGridState(Cell (&puzzle)[N][N]);
void ParseFile(std::string filename, std::vector<std::string> &_puzzles);
void PopulateUnitsAndPeers(Cell (&puzzle)[9][9], unsigned const int &_row, unsigned const int &_col);
void BuildUnitsAndPeers(Cell (&puzzle)[9][9]);
// void printCell(Cell (&puzzle)[N][N], int row, int col);
// void printCells(Cell (&puzzle)[N][N]);

#endif