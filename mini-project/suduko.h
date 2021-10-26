#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream> 
#include <vector> 
#include <algorithm>
#include <chrono>
#include <sstream>
#include <set>
#define N 9

typedef struct cell_coordinate {
    unsigned int row;
    unsigned int col;
}Coord_t;

typedef struct struct_cell {
    unsigned int value;
    std::vector<int> hypos;
    Coord_t Units[3][9];
    Coord_t Peers[20];
}Cell;

// General
bool isPossible(Cell (&puzzle)[N][N], int row, int col, int num);
void RemovePeerInRow(Cell (&puzzle)[N][N], int row, int num);
void RemovePeerInCol(Cell (&puzzle)[N][N], int col, int num);
void RemovePeerInBox(Cell (&puzzle)[N][N], int boxStartRow, int boxStartCol, int num);
void printCell(Cell (&puzzle)[N][N], int row, int col);
void setValue(Cell (&puzzle)[N][N], int row, int col, int _num=0);
void PrintGridState(Cell (&puzzle)[N][N]);
void CheckUnits(Cell (&puzzle)[N][N], int row, int col);
void PrintGrid(Cell (&puzzle)[N][N]);
void PrintGridState(Cell (&puzzle)[N][N]);
void ParseFile(std::string filename, std::vector<std::string> &_puzzles);
void BuildPuzzleGrid(std::string _puzzle, Cell (&puzzle)[N][N]);
void PrintGridAsLine(Cell (&puzzle)[N][N], unsigned const int &_nr, unsigned const int _guesses);
void PopulateUnitsAndPeers(Cell (&puzzle)[N][N], unsigned const int &_row, unsigned const int &_col);

// For Constraint Propagation, Rule 1 and common
void ConstraintPropagation(Cell (&puzzle)[N][N]);
void DeleteHypo(Cell (&puzzle)[N][N], int row, int col, int num);
void RemovePeerInRow(Cell (&puzzle)[N][N], int row, int num);
void RemovePeerInCol(Cell (&puzzle)[N][N], int col, int num);
void RemovePeerInBox(Cell (&puzzle)[N][N], int boxStartRow, int boxStartCol, int num);
void RemoveFromPeers(Cell (&puzzle)[N][N], int row, int col, int num);
void setValue(Cell (&puzzle)[N][N], int row, int col, int _num);
void CleanHypoValues(Cell (&puzzle)[N][N]);

// For Constraint Propagation, Rule 2
bool IsValueInHypos(std::vector<int> &hypos, int num);
void VisitRowPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
void VisitColPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
void VisitBoxPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
bool IsHypoInRowPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
bool IsHypoInColPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
bool IsHypoInBoxPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
void CheckUnits(Cell (&puzzle)[N][N], int row, int col);

// For Brute Force
bool FindUnassignedLocation(Cell (&puzzle)[N][N], int &row, int &col);
bool SolveSudoku(Cell (&puzzle)[N][N], unsigned int &_guesses);
bool UsedInRow(Cell (&puzzle)[N][N], int row, int num);
bool UsedInCol(Cell (&puzzle)[N][N], int col, int num);
bool UsedInBox(Cell (&puzzle)[N][N], int boxStartRow, int boxStartCol, int num);

// Developer tools
void printCell(Cell (&puzzle)[N][N], int row, int col);
void printCells(Cell (&puzzle)[N][N]);
