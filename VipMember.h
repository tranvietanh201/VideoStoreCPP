#pragma once

#include "Customer.h"

#define VIP_EXCHANGE_CONDITION 100
#define VIP_POINTS 10

class VipMember : public Customer {
private:
  int reward,freeRentItem;

public:
  // Constructors
	VipMember();

	VipMember(string Id, string Name, string Address, string PhNo, int number_of_rental);

  // Member functions
  void rentItem(const string Item_Name, LinkedListItem&item_list);

  void returnItem(const string Item_Name);

  void checkRewardPoints();

  void details();

  void showRentalList();

  int typeCustomer();
};
