#pragma once

#include <string>
#include "Item.h"

class RecordItem : public Item {
	private:
		string g;

	public:
		RecordItem();
		RecordItem(string Id, string Title, string rental_type, string loan_type, int number_of_copies, double rental_fee,string g);

		string getGenre();

		//Functions
		void setGenre(string g);
		void printDetail();
};
