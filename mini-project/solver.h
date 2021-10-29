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
}Cell_t;

class Solver {
    public:
        unsigned const int N = 9;
        unsigned int guesses;
        Cell_t puzzle[9][9];

        Solver(Cell_t _puzzle[9][9], std::string _oneLinePuzzle);
        void BuildPuzzleGrid(std::string _oneLinePuzzle);
        void PropagatateConstraints();
        bool isPossible(unsigned const int &row, unsigned const int &col, unsigned const int &num);
        bool UsedInRow(unsigned const int &row, unsigned const int &num);
        bool UsedInCol(unsigned const int &col, unsigned const int &num);
        bool UsedInBox(unsigned const int &boxStartRow, unsigned const int &boxStartCol, unsigned const int &num);
        void DeleteHypo(unsigned const int &row, unsigned const int &col, unsigned const int &num);
        void VisitPeers(unsigned const int &row, unsigned const int &col, unsigned const int &num);
        bool IsValueInHypos(std::vector<int> &hypos, unsigned const int &num);
        void CheckUnits(unsigned const int &row, unsigned const int &col);
        void setValue(unsigned const int &row, unsigned const int &col, int _num=0);
        void RemoveFromPeers(unsigned const int &row, unsigned const int &col, unsigned const int &num);

        bool Search();
        bool IsHypoInRowPeers(unsigned const int &_row, unsigned const int &_col, unsigned const int &_num);
        bool IsHypoInColPeers(unsigned const int &_row, unsigned const int &_col, unsigned const int &_num);
        bool IsHypoInBoxPeers(unsigned const int &_row, unsigned const int &_col, unsigned const int &_num);
        bool FindFewestHypoCell(int &_row, int &_col);

        void PrintGridAsLine();
        void PrintGrid();
        void PrintGridState();
};

#endif
