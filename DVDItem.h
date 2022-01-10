#pragma once
#include "Item.h"
#include <string>
#include <iostream>

using namespace std;

class DVDItem : public Item {
private:
	string g;

public:
	DVDItem();
	DVDItem(string Id, string Title, string rental_type, string loan_type, int number_of_copies, double rental_fee,string g);
	DVDItem(DVDItem& dvd);

	string getGenre();

	void setGenre(string g);
	void printDetail();
};