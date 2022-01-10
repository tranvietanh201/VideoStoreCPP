#pragma once

#include "Item.h"
#include "GameItem.h"
#include "RecordItem.h"
#include "DVDItem.h"
#include "LinkedListItem.h"
#include "ItemElement.h"
#include "LinkedListCustomer.h"

void itemMenu(LinkedListItem& i_list, LinkedListCustomer& cust_list, string i_file_name, string cust_file_name);
Item* itemCreateMenu(LinkedListItem& i_list);
void itemUpdateMenu(ItemElement* ptr);