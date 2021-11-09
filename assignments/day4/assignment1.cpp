#include "assignment1.h"

void IdObject::SetId(unsigned int _id) {
    id = _id;
}

unsigned int IdObject::GetId() {
    return id;
}

std::string Customer::GetName() {
    return this->name;
}

void ServiceRecord::AddPart(unsigned int _part_id) {
    parts.push_back(_part_id);
}

void ServiceRecord::AddPayment(unsigned int _payment_id) {
    payment.push_back(_payment_id);
}

int Shop::AddCustomer(std::string _name, std::string _email) {
    Customer new_instance = Customer(_name, _email);
    new_instance.SetId(customers.size());
    customers.push_back(new_instance);
    return new_instance.GetId();
}

int Shop::AddPart(std::string _name, unsigned int _price) {
    Part new_instance = Part(_name, _price);
    new_instance.SetId(parts.size());
    parts.push_back(new_instance);
    return new_instance.GetId();
}

int Shop::AddPayment(Payment_method_t _payment_method, unsigned int _amount) {
    Payment new_instance = Payment(_payment_method, _amount);
    new_instance.SetId(payments.size());
    payments.push_back(new_instance);
    return new_instance.GetId();
}

int Shop::AddService(std::string _title, std::string _description, unsigned int _customer_id) {
    ServiceRecord new_instance = ServiceRecord(_title, _description, _customer_id);
    new_instance.SetId(services.size());
    services.push_back(new_instance);
    return new_instance.GetId();
}

Customer* Shop::GetCustomerFromId(unsigned const int id) {
    unsigned int index;
    for (size_t i=0; i<customers.size(); i++) {
        if (customers[i].GetId() == id) {
            index = i;
        }
    }
    return &(customers[index]);
}