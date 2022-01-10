#pragma once

#include <string>
#include <iostream>

using namespace std;

class RentalListNode {
private:
	string data;
	RentalListNode* next;

public:
	string getItem();

	RentalListNode();
	RentalListNode(string item_name, RentalListNode* next_node);
	RentalListNode* getNext();

	void setNext(RentalListNode* next_node);
};


