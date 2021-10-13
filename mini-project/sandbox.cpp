#include <iostream>
#include <vector>


int main() {

    std::vector<int> possibilites; 
    for (size_t i = 1; i < 10; i++) {
        possibilites.push_back(i);
    }
    


    for(int i : possibilites) 
        std::cout << "i = " << i << std::endl;
    
    return 0;
}
