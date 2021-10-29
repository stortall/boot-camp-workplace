#ifndef SOLVER
#define SOLVER
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
#include <iterator>

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

class Solver {
    public:
        unsigned const int N = 9;
        unsigned int guesses;
        Cell puzzle[9][9];

        Solver(Cell _puzzle[9][9], std::string _oneLinePuzzle);
        void BuildPuzzleGrid(std::string _oneLinePuzzle);
        void PropagatateConstraints();
        bool isPossible(int row, int col, int num);
        bool UsedInRow(int row, int num);
        bool UsedInCol(int col, int num);
        bool UsedInBox(int boxStartRow, int boxStartCol, int num);
        void DeleteHypo(int row, int col, int num);
        void VisitPeers(int row, int col, int num);
        bool IsValueInHypos(std::vector<int> &hypos, int num);
        void CheckUnits(int row, int col);
        void setValue(int row, int col, int _num=0);
        void RemoveFromPeers(int row, int col, int num);

        bool Search();
        bool IsHypoInRowPeers(int _row, int _col, int _num);
        bool IsHypoInColPeers(int _row, int _col, int _num);
        bool IsHypoInBoxPeers(int _row, int _col, int _num);
        bool FindFewestHypoCell(int &_row, int &_col);

        void PrintGridAsLine();
        void PrintGrid();
        void PrintGridState();
};

#endif
