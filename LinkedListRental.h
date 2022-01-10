#pragma once

#include "RentalListNode.h"
#include <iostream>
#include <string>


using namespace std;

class LinkedListRental {
	friend ostream& operator<<(ostream& o, const LinkedListRental& l);

private:
  RentalListNode* head;

public:
	LinkedListRental();
	~LinkedListRental();

	RentalListNode* getHead();
  
  //Adding Item to the list 
	void addItem(string a);

  //Removing the first time apperence of a from the list 
	void removeItem(string a);

  //Display all items in the RentalListNode
	void showItem();

	bool isListHaveId(string i);
  
};
