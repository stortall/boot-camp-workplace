#include <iostream>
#include <vector>


int main() {
    for (size_t i = 0; i < 9; i++)
    {
        int startrow = i - i % 3 ;
        std::cout << startrow << std::endl;
    }
    
    // int row = 7;
    // int startrow = row - row % 3 ;
    // std::cout << startrow << std::endl;
    // std::vector<int> possibilites; 
    // for (size_t i = 1; i < 10; i++) {
    //     possibilites.push_back(i);
    // }
    


    // for(int i : possibilites) 
    //     std::cout << "i = " << i << std::endl;
    
    return 0;
}
