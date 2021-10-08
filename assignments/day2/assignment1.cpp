#include <iostream>
#include <random>


int main() {
    
    unsigned int input;
    unsigned int randomNumber;
    unsigned int size1;
    unsigned int size2;
    unsigned int size3;

    std::cout << "Type max number, and press enter..." << std::endl;
    std::cin >> input;
    std::cout << "Type size of array 1, and press enter..." << std::endl;
    std::cin >> size1;
    std::cout << "Type size of array 2, and press enter..." << std::endl;
    std::cin >> size2;
    std::cout << "Type size of array 2, and press enter..." << std::endl;
    std::cin >> size3;

    unsigned int ***arrayP = new unsigned int**[size1];
    for (size_t i = 0; i < size1; i++) {
        arrayP[i] = new unsigned int*[size2];
        for (size_t j = 0; j < size2; j++) {
            arrayP[i][j] = new unsigned int[size3];
            for (size_t k = 0; k < size3; k++) {
                randomNumber = rand() % input;
                arrayP[i][j][k] = randomNumber;
                std::cout << randomNumber << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n\n";
    }
    std::cout << std::endl;
}