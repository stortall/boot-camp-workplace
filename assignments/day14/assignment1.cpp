#include <iostream>
#include <bitset>

void reader(std::bitset<16> &set) {
    // MSB is stored in the higherst address

    std::cout << "Seat belts:\t";
    for (int i = 16; i --> 11; ) {
        std::cout << set[i];
    }
    std::cout << std::endl;
    
    std::cout << "Windows:\t";
    for (int i = 11; i --> 7; ) {
        std::cout << set[i];
    }
    std::cout << std::endl;

    std::cout << "Doors:\t";
    for (int i = 7; i --> 3; ) {
        std::cout << set[i];
    }
    std::cout << std::endl;

    std::cout << "Lights:\t";
    for (int i = 3; i --> 0; ) {
        std::cout << set[i];
    }
    std::cout << std::endl;
}


int main() { 
    uint16_t bits = 0b1011101001011011;
    std::bitset<16> set(bits);   
    reader(set);
    return 0; 
} 