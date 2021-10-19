#include "suduko.h"

int main(int argc, char *argv[]) {
    auto start_program = std::chrono::high_resolution_clock::now();
    if (!argv[1]) {
        std::cout << "Input file needed. Aborting..." << std::endl;
        return 1;
    } 
    Cell puzzle[N][N];
    ParseFile(argv[1], puzzle);
    std::cout<<"~~~~~~~~~~~~ INPUT ~~~~~~~~~~~~"<<std::endl;
    PrintGrid(puzzle);
    ConstraintPropagation(puzzle);
    std::cout<<"~ After constraint propagation~"<<std::endl;
    PrintGridState(puzzle);
    if (SolveSudoku(puzzle) == true) {
        std::cout<<"~~~~~~ After Brute Force ~~~~~~"<<std::endl;
        PrintGrid(puzzle);
    } else {
        std::cout<<"No solution exists"<<std::endl;
    }
    
    auto end_program = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_program - start_program);
    std::cout << "Total execution time (ms): " << duration.count() << std::endl;
    return 0;
}