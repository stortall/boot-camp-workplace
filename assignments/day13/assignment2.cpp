#include <iostream>
#include <map>

void GenerateRandomNumbers(unsigned int (&array)[10000]) {
    for (size_t i = 0; i < 10000; i++) {
        array[i] = rand() % 33;
    }
}

// void CountOccurrences(unsigned int (&array)[10000], unsigned int (&occurrences)[33]) {
//     for (size_t i = 0; i < 10000; i++) {
//         unsigned int num = array[i];
//         occurrences[num] = occurrences[num] + 1;
//     }
// }

int main(){
    unsigned int array[10000];
    // unsigned int occurrences[33] = {0};
    std::map<int, int> occurrences;

    GenerateRandomNumbers(array);
    // CountOccurrences(array, occurrences);

    for (size_t i = 0; i < 10000; i++)
    {
        if (occurrences.find(i) == occurrences.end()) {
            occurrences[i] = occurrences[i] + 1;
        } else {
            occurrences.insert(std::pair<int, int>(i,1));
        }
    }
    

    for (size_t i = 0; i < 33; i++) {
        std::cout << occurrences[i] << " ";
    }
    std::cout << std::endl;

}