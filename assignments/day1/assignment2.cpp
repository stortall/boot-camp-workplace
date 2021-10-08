#include <iostream>


int main() {
    unsigned int key;
    std::string cipher;
    // unsigned int lowered;
    // unsigned int decoded;
    char a;

    std::cout << "Type a number, and press enter..." << std::endl;
    std::cin >> key;
    std::cout << "Type a string, and press enter..." << std::endl;
    std::cin >> cipher;

    for (char& c : cipher) {
        a = c - key;
        if (a < 'A') {
            std::cout << (char)(a + ('Z' - 'A' + 1));
        }
        else {
            std::cout << a;
        }
    }
    std::cout << std::endl;

    // for(char& c : cipher) {
    //     lowered = c - key;
    //     if (lowered < 65) {
    //         decoded = 91-(65-lowered);
    //     }
    //     else {
    //         decoded = lowered;
    //     }
    //     std::cout << (char)decoded << std::endl;
    // }
}