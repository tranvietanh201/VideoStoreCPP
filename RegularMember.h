#pragma once

#include "Customer.h"
#include <string>
#include <iostream>

#define REGULAR_PROMOTION_CONDITION 3

class RegularMember : public Customer {
private:


public:
  // Constructors
	RegularMember();

	RegularMember(string Id, string Name, string Address, string PhNo, int number_of_rental);

  // Member functions
  void rentItem(const string Item_Name, LinkedListItem &item_list);

  void returnItem(const string Item_Name);

  void details();

  void showRentalList();

  int typeCustomer();

};
