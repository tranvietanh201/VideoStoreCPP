#pragma once

#include "MainMenu.h"
#include "ItemMenu.h"
#include "LinkedListItem.h"
#include "LinkedListCustomer.h"
#include "CustomerNode.h"
#include "Customer.h"

void customerMenu(LinkedListItem&i_list, LinkedListCustomer&cust_list, string i_file_name, string cust_file_name);

Customer* customerCreateMenu(LinkedListCustomer&cust_list);

void customerUpdateMenu(CustomerNode *custm);