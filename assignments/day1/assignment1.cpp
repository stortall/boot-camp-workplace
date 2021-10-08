#include <iostream>
#include <random>


int main() {
    unsigned int array[8][9][11];
    unsigned int input;
    unsigned int randomNumber;

    std::cout << "Type a number, and press enter..." << std::endl;
    std::cin >> input;

    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 9; j++) {
            for (size_t k = 0; k < 11; k++) {
                randomNumber = rand() % input;
                std::cout << randomNumber << std::endl;
                array[i][j][k] = randomNumber;
            }
        }
    }

    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 9; j++) {
            for (size_t k = 0; k < 11; k++) {
                std::cout << array[i][j][k] << "\t" std::endl;
            }
        std::cout << std::endl;
        }
    }
}