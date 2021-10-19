#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <sstream> 
#include <vector> 
#include <algorithm>
#include <chrono>
#define N 9

typedef struct struct_cell {
    unsigned int value;
    std::vector<int> possibilites;
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
void ParseFile(std::string filename, Cell (&puzzle)[N][N]);

// For Constraint Propagation, Rule 1 and common
void ConstraintPropagation(Cell (&puzzle)[N][N]);
void DeleteValueInVector(Cell (&puzzle)[N][N], int row, int col, int num);
void RemovePeerInRow(Cell (&puzzle)[N][N], int row, int num);
void RemovePeerInCol(Cell (&puzzle)[N][N], int col, int num);
void RemovePeerInBox(Cell (&puzzle)[N][N], int boxStartRow, int boxStartCol, int num);
void removeFromPeers(Cell (&puzzle)[N][N], int row, int col, int num);
void setValue(Cell (&puzzle)[N][N], int row, int col, int _num);
void CleanPossibleValues(Cell (&puzzle)[N][N]);

// For Constraint Propagation, Rule 2
bool IsValueInPossibilities(std::vector<int> &possibilities, int num);
void RunCheckUnitsForAllRowPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
void RunCheckUnitsForAllColPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
void RunCheckUnitsForAllBoxPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
bool IsPossibilityInRowPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
bool IsPossibilityInColPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
bool IsPossibilityInBoxPeers(Cell (&puzzle)[N][N], int _row, int _col, int _num);
void CheckUnits(Cell (&puzzle)[N][N], int row, int col);

// For Brute Force
bool FindUnassignedLocation(Cell (&puzzle)[N][N], int &row, int &col);
bool SolveSudoku(Cell (&puzzle)[N][N]);
bool UsedInRow(Cell (&puzzle)[N][N], int row, int num);
bool UsedInCol(Cell (&puzzle)[N][N], int col, int num);
bool UsedInBox(Cell (&puzzle)[N][N], int boxStartRow, int boxStartCol, int num);


// Developer tools
void printCell(Cell (&puzzle)[N][N], int row, int col);
void printCells(Cell (&puzzle)[N][N]);
