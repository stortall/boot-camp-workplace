#include "suduko.h"

int main(int argc, char *argv[]) {
    auto start_program = std::chrono::high_resolution_clock::now();
    if (!argv[1]) {
        std::cout << "Input file needed. Aborting..." << std::endl;
        return 1;
    } 
    std::vector<std::string> puzzles;
    ParseFile(argv[1], puzzles);
    Cell puzzle_template[N][N];
    BuildUnitsAndPeers(puzzle_template);
    unsigned int nr = 1;
    for(std::string line : puzzles) {
        Cell puzzle[N][N];
        for(size_t i = 0; i < N; i++){
            for(size_t j = 0; j < N; j++){
                puzzle[i][j] = puzzle_template[i][j];
            }
        }
        BuildPuzzleGrid(line, puzzle);
        std::cout << "\n================================ Puzzle: " << nr << " =====================================" << std::endl;
        // std::cout<<"~~~~~~~~~~~~ INPUT ~~~~~~~~~~~~"<<std::endl;
        // PrintGrid(puzzle);
        std::cout<<"Input:"<<std::endl;
        PrintGridAsLine(puzzle);
        CleanHypoValues(puzzle);
        ConstraintPropagation(puzzle);
        // std::cout<<"~ After constraint propagation~"<<std::endl;
        // PrintGridState(puzzle);
        std::cout<<"After constraint propagation:"<<std::endl;
        PrintGridAsLine(puzzle);
        unsigned int guesses = 0;
        if (SolveSudoku(puzzle, guesses) == true) {
            // std::cout<<"~~~~~~ After Brute Force ~~~~~~"<<std::endl;
            // std::cout<<"~Guesses " <<guesses<<std::endl;
            // PrintGrid(puzzle);
            std::cout<<"Search with " << guesses << " numbers guessed:"<<std::endl;
            PrintGridAsLine(puzzle);
            
        } else {
            std::cout<<"No solution exists"<<std::endl;
        }
        nr++;
    }
    
    auto end_program = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_program - start_program);
    std::cout << "\nTotal execution time (ms): " << duration.count() << std::endl;
    return 0;
}