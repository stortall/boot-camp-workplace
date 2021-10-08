#include <iostream>
#include <random>
#include <ctime>

enum Payment_method_t {Cash, Credit};
enum Services {Cash, Credit};

class Customer {
public:
    // Attributes
    std::string Name;
    tm date;
    // Methods
    Customer(std::string _name, tm _date);
};

class Service {
public:
    // Attributes
    std::string Name;
    short cost;
    // Methods
    Service(std::string _name, tm _cost);
};

class Part {
    // Attributes
    std::string Name;
    short cost;
    // Methods
    Part(std::string _name, tm _cost);
};

class Payment {
    // Attributes
    Payment_method_t Payment_method;
    int amount;
    // Methods
    Payment(Payment_method_t _payment_method, int _amount);
};

int main() {
    // Customer("Joe", );
    Service("")
    
}