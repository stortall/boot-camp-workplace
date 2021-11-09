#include <iostream>
#include <random>
#include <ctime>

enum Payment_method_t {Cash, Credit};

// TODO: Change to composition
class IdObject {
public:
    // Attributes
    unsigned int id;
    // Methods
    void SetId(unsigned int _id);
    unsigned int GetId();
};

class Customer : public IdObject {
public:
    // Attributes
    std::string name;
    std::string email;
    // Methods
    Customer(std::string _name, std::string _email): name(_name), email(_email) {};
    std::string GetName();
};

class Part : public IdObject {
public:
    // Attributes
    std::string name;
    unsigned int price;
    // Methods
    Part(std::string _name, unsigned int _price): name(_name), price(_price) {};
};

class Payment : public IdObject {
public:
    // Attributes
    Payment_method_t payment_method;
    unsigned int amount;
    bool payed;
    // Methods
    Payment(Payment_method_t _payment_method, unsigned int _amount): 
        payment_method(_payment_method), amount(_amount) {};
};

class ServiceRecord : public IdObject {
public:
    // Attributes
    std::string title;
    std::string descrition;
    unsigned int customer; 
    std::vector<unsigned int> parts;
    std::vector<unsigned int> payment;
    // Methods
    ServiceRecord(std::string _title, std::string _description, unsigned int _customer_id): 
        title(_title), descrition(_description), customer(_customer_id) {};
    void AddPart(unsigned int _part_id);
    void AddPayment(unsigned int payment_id);
};

class Shop {
public:
    // Attributes
    std::string name;
    // Inventories
    std::vector<Customer> customers;
    std::vector<Part> parts;
    std::vector<Payment> payments;
    std::vector<ServiceRecord> services;
    // Methods
    Shop(std::string _name): name(_name) {};
    int AddCustomer(std::string _name, std::string _email);
    int AddPart(std::string _name, unsigned int _price);
    int AddPayment(Payment_method_t _payment_method, unsigned int _amount);
    int AddService(std::string _title, std::string _description, 
        unsigned int _customer_id);
    Customer* GetCustomerFromId(unsigned const int id);
    Part* GetPartFromId(unsigned const int id);
    Payment* AddPaymentFromId(unsigned const int id);
    ServiceRecord* AddServiceFromId(unsigned const int id);
};

int main() {
    Shop shop = Shop("Bosses");
    std::cout << "Adding new customer with id: " << shop.AddCustomer("Johan", "johan@mail.com") << std::endl;
    std::cout << "Adding new customer with id: " << shop.AddCustomer("Carl", "carl@mail.com") << std::endl;
    std::cout << "Adding new part with id: " << shop.AddPart("Disc Break", 600) << std::endl;
    std::cout << "Adding new part with id: " << shop.AddPart("Break Caliper", 800) << std::endl;
    std::cout << "Adding new part with id: " << shop.AddPart("Alu Rim", 1000) << std::endl;

    std::cout << "Adding new service with id: " << shop.AddService("Break repair", "Replacing caliper and discs.", 1) << std::endl;

    // Customer* johanCpy =  nullptr;//&shop.customers[0];

    std::cout << "cus " << shop.GetCustomerFromId(0)->GetName() << std::endl;
    
}