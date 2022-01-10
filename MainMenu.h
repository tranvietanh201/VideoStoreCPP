#pragma once

#include <string>

#include "Item.h"
#include "GameItem.h"
#include "RecordItem.h"
#include "DVDItem.h"
#include "LinkedListItem.h"
#include "LinkedListCustomer.h"

void mainMenu(LinkedListItem& item_list, LinkedListCustomer& cust_list, string item_file_name, string cust_file_name);

void closeProgram(LinkedListItem& item_list, LinkedListCustomer& cust_list, string item_file_name, string cust_file_name);