#pragma once
#include "Item.h"
#include <string>
#include <iostream>

using namespace std;

class GameItem : public Item {
	
public:
	GameItem();
	GameItem(string Id, string Title, string rental_type, string loan_type, int number_of_copies, double rental_fee);
	GameItem(GameItem& game);

	void printDetail();
};