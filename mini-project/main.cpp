#include "solver.h"
#include "pre.h"

int main(int argc, char *argv[]) {
    auto start_program = std::chrono::high_resolution_clock::now();
    if (!argv[1]) {
        std::cout << "Input file needed. Aborting..." << std::endl;
        return 1;
    } 
    std::vector<std::string> puzzles;
    Cell puzzle_template[9][9];
    ParseFile(argv[1], puzzles);
    PopulateUnitsAndPeers(puzzle_template);

    unsigned int puzzle_nr = 1;
    for(std::string line : puzzles) {
        Solver solver = Solver(puzzle_template, line);

        std::cout << "\n================================ Puzzle: " << puzzle_nr << " =====================================" << std::endl;
        std::cout<<"Input:"<<std::endl;
        // solver.PrintGridAsLine();
        solver.PrintGrid();

        solver.PropagatateConstraints();
        std::cout<<"After constraint propagation:"<<std::endl;
        // solver.PrintGridAsLine();
        solver.PrintGridState();

        if (solver.Search() == true) {
            std::cout<<"Search with " << solver.guesses << " numbers guessed:"<<std::endl;
            // solver.PrintGridAsLine();
            solver.PrintGrid();
        } else {
            std::cout<<"No solution exists"<<std::endl;
        }

        puzzle_nr++;
    }

    auto end_program = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_program - start_program);
    std::cout << "\nTotal execution time (ms): " << duration.count() << std::endl;
    return 0;
}
