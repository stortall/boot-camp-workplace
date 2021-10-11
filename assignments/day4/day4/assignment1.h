#include <iostream>
#include <random>
#include <ctime>

enum Payment_method_t {Cash, Credit};
enum Services {Cash, Credit};
enum Month {January, February, Mars, April, May, June, Juli, August, September, October, November, December};
typedef struct date{
    int year;
    Month month;
    int day;
}Date_t;

class Customer {
public:
    // Attributes
    int id;
    std::string Name;
    int phone_nr;
    // Methods
    Customer() {}; 
    Customer(std::string _name);
};

class Service {
public:
    // Attributes
    int id;
    std::string Name;
    short cost;
    Date_t date;
    // Methods
    Service(std::string _name, tm _cost);
};

class Part {
    // Attributes
    int id;
    std::string Name;
    short price;
    bool avalible;
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