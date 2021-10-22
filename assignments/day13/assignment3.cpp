#include<iostream>
#include<set>

int main() {
    std::multiset<int> s;

    for (size_t i = 5; i < 10; i++)
    {
        s.insert(i);
    }
    
    std::set<int> :: iterator it;
 
    // Print the elements of the set
    for(it=s.begin(); it != s.end();it++)
        std::cout<<*it<<" ";
    std::cout<<std::endl;

    s.insert(8);

    for(it=s.begin(); it != s.end();it++)
        std::cout<<*it<<" ";
    std::cout<<std::endl;

    auto upper = s.upper_bound(7.51);

    std::cout << "upper: " << *upper << std::endl;

    auto lower = s.lower_bound(7.51);

    std::cout << "lower: " << *lower << std::endl;
}





