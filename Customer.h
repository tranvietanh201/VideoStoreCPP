#pragma once

#include <string>
#include "RentalListNode.h"
#include "LinkedListRental.h"
#include "LinkedListItem.h"

using namespace std;

class Customer {
private:
    string Id, Name, Address, PhNo, Type;
    int number_of_rental, number_of_returnedItems;
    LinkedListRental rental_list;

public:
 //Constructors
    Customer();
    Customer(string Id, string Name, string Address, string PhNo, int number_of_rental);

  //Getter and setter
    string getId() const;

    string getName() const;

    string getAddress() const;
    
    string getPhoneNumber() const;

    int getNumberOfRental();

    int getNumberOfReturnedItems();

    string getType() const;

    void setId(const string Id);

    void setName(const string Name);

    void setAddress(const string Address);

    void setPhoneNumber(const string PhNo);

    void setNumberOfRental(const int number_of_rental);

    void setNumberOfReturnedItems(const int number_of_returned_items);

    void setType(const string& typeCustomer);

    void setRentalList(LinkedListRental& rental_list);

    LinkedListRental* getRentalList1();
    LinkedListRental getRentalList2();


  // Base method
    virtual void details() = 0;

    virtual void showRentalList() = 0;

    virtual void rentItem(const string Item_Name, LinkedListItem& item_list) = 0;

    virtual void returnItem(const string Item_Name) = 0;

    virtual int typeCustomer() = 0;

};
