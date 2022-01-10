#include "Item.h"
#include "ItemElement.h"
#include <string>

using namespace std;

#ifndef LINKEDITEM_H
#define LINKEDITEM_H

class LinkedListItem{
private:
    ItemElement *h,*l,*t,*c;

public:
	LinkedListItem();
	// Copy constructors
	LinkedListItem(const LinkedListItem& itemList);
	LinkedListItem searchItemByTitle(string title);

	ItemElement* searchItemByID(string id);
	ItemElement* getHead() const;

	void addItem(Item* newItem);
	void deleteItem(string id);
	void printItem();
	void printOutOfStockItem();
	void sortedByID();
	void sortedByTitle();

	void IncreaseNumberOfCopies(string id);
	void DecreaseNumberOfCopies(string id);
	void Output(LinkedListItem* itemList);
};


#endif
