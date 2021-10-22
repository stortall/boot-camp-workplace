#include <iostream>
#include <bitset>

// int decode(std::bitset<16> &set, int _from, int _to) {
//     std::string mask_seed;
//     for (size_t i = 0; i < 16; i++)
//     {
//         if (i>=_from && i<=_to)
//         {
//             mask_seed = mask_seed + "1";
//         } else {
//             mask_seed = mask_seed + "0";
//         }
        
//     }
//     std::bitset<16> MASK(std::stoi(mask_seed, 0, 2));
//     std::bitset<16> isolated = std::bitset<16>((set & MASK) >> (15-_to));
//     // std::cout << "Debug " << MASK << std::endl;
//     return (int)(isolated.to_ulong());
//     // return isolated;
// }

uint16_t encode(int _speed, int _front, int _rear, int _right, int _left) {
    std::string speed = std::bitset<4>(_speed / 20).to_string();
    std::string front = std::bitset<3>(_front / 150).to_string();
    std::string rear = std::bitset<3>(_rear / 150).to_string();
    std::string right = std::bitset<3>(_right / 150).to_string();
    std::string left = std::bitset<3>(_left / 150).to_string();
    std::string all_parts = speed + front + rear + right + left;
    std::bitset<16> data(std::stoi(all_parts, 0, 2));
    return (uint16_t)data.to_ulong();
}


int main() { 
    std::cout <<  encode(220,300,300,300,300) << std::endl;
    // int b = 11;
    // std::string a = std::to_string(b);
    // std::string str = std::bitset<4>(11).to_string();
    // std::cout << str << std::endl;
    // uint16_t bits = 0b1011101001011011;
    // std::bitset<16> set(bits);   

    // std::cout << "Speed: \t\t" << decode(set,0,3)*20 << std::endl;
    // std::cout << "Distance:\t" << decode(set,4,6)*150 << std::endl;

    return 0; 
} 