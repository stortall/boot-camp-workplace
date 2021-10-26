#include <iostream>
#include <vector>
#include <set>

typedef struct peer {
    unsigned int row;
    unsigned int col;
}Peer_t;

void VisitRowPeers(Peer_t (&Peers)[20]) {
    for (int col = 0; col < 9; col++) {
        Peers[col].row = 0;
        Peers[col].col = col;
    }
}

int main() {
    // for (size_t i = 0; i < 9; i++)
    // {
    //     int startrow = i - i % 3 ;
    //     std::cout << startrow << std::endl;
    // }

    std::set<std::string> peers_set;
    peers_set.insert("11");
    peers_set.insert("22");
    peers_set.insert("22");

    for (auto item : peers_set)
    {
        std::cout << item << std::endl;
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
