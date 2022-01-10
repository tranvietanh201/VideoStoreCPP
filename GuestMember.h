#pragma once

#include "Customer.h"
#include <string>

#define GUEST_RENT_LIMIT 2
#define GUEST_PROMOTION_CONDITION 3

class GuestMember : public Customer {

public:
  // Constructors
	GuestMember();

	GuestMember(string Id, string Name, string Address, string PhNo, int number_of_rental);

  // Member functions
  void rentItem(const string Item_Name, LinkedListItem&item_list);

  void returnItem(const string Item_Name);

  void details();

  void showRentalList();

  int typeCustomer();

};
