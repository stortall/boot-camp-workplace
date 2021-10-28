#include <iostream>
#include <vector>
#include <set>
#include<list>

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

const int goal = 9;

void p(int n) {
    if (n != 0)
            {
        p(n -1);
        std::cout << n << std::endl;
    }
    
}

struct c {
    c(){std::cout << "1";}
    c(const c &) {std::cout << "2";}
    ~c(){std::cout<<"3"<<std::endl;}
};
c ex() { return c();}

using namespace std;

class b {
    public:
    b(){cout << "in basec";}
    virtual void pr() {cout<<"in basec";}
};
class d: public b {
    public:
    // (){cout << "in basec";}
    void pr() {cout<<"in derc";}
};


int main() {
    enum en {a=10,b=9,c};
    std::cout << c << std::endl;

    // for (size_t i = 0; i < 9; i++)
    // {
    //     int startrow = i - i % 3 ;
    //     std::cout << startrow << std::endl;
    // }

    // std::set<std::string> peers_set;
    // peers_set.insert("11");
    // peers_set.insert("22");
    // peers_set.insert("22");

    // for (auto item : peers_set)
    // {
    //     std::cout << item << std::endl;
    // }
    
    // int a = 14, b = 41, *c = new int, *d = new int, *e, *f;

    // e = nullptr;
    // f = nullptr;

    // *c = 22;
    // c = &a;
    // *d = b;
    // b = *c;
    // d = c;
    // e = d;

    // std::cout << "a: " << a << std::endl;
    //  std::cout << "b: " << b << std::endl;
    //   std::cout << "c: " << c << std::endl;
    //   std::cout << "*c: " << *c << std::endl;
    //    std::cout << "d: " << d << std::endl;
    //    std::cout << "*d: " << *d << std::endl;
    //     std::cout << "e: " << e << std::endl;
    //     std::cout << "*e: " << *e << std::endl;
    //      std::cout << "f: " << f << std::endl;
    //      std::cout << "*f: " << *f << std::endl;

    
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
