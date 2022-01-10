#include "Customer.h"
#include "CustomerNode.h"
#include <string>

#ifndef LINKEDCUSTOMER_H
#define LINKEDCUSTOMER_H

class LinkedListCustomer {
private:
    CustomerNode* h, * t, * la, * tr, * curr;

public:
    LinkedListCustomer();
    LinkedListCustomer(const LinkedListCustomer& customerList);

    CustomerNode* searchCustomerByID(string id);
    CustomerNode* getHead() const;
    CustomerNode* getHead();

    LinkedListCustomer searchCustomerByName(string name);

    void addCustomer(Customer* newCustomer);
    void deleteCustomer(string id);
    void sortedByID();
    void sortedByName();
    void printAllCustomer();
    void Output(LinkedListCustomer* Customerlist);

};
#endif
