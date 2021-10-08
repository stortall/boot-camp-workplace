#include <iostream>

int recurse(int _low, int _high, int _steps) {
    int middle = (_high + _low)/2;
    char answer;

    std::cout << "Is it larger than or equal to " << middle << " (y, n), and press enter..." << std::endl;
    std::cin >> answer;
    if ((answer == 'y') && (_steps > 1)) {
        return recurse(middle, _high, --_steps);
    }
    else if ((answer == 'n') && (_steps > 1)) {
        return recurse(_low, middle, --_steps);
    }
    else {
        return middle;
    }
}

int main() {
    unsigned int number;
    unsigned int out;

    std::cout << "Type a number between 1-128, and press enter..." << std::endl;
    std::cin >> number;
    out = recurse(1, 128, 7);
    std::cout << "Is it: " << out << "?" << std::endl;
}

