#ifndef PARSEDEV
#define PARSEDEV
#include "solver.h"

void ParseFile(std::string filename, std::vector<std::string> &_puzzles);
void PopulateUnitsAndPeers(Cell_t (&puzzle)[9][9]);

#endif
