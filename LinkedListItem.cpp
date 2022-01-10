#include "Item.h"
#include <iostream>
#include "LinkedListItem.h"
#include "ItemElement.h"
#include<iostream>
#include<fstream>
#include "Utilities.h"

LinkedListItem::LinkedListItem(){
	h = l = t = c = NULL;
}

//Copy Constructor
// References: https://stackoverflow.com/questions/7811893/creating-a-copy-constructor-for-a-linked-list
LinkedListItem::LinkedListItem(const LinkedListItem& l) {

	if (l.h == NULL) {
		h = NULL;
		return;
	}
	// Create a temp variable since ll.current doesn't move/change.
	ItemElement* var = l.h;

	// Allocate a new node in memory.
	h = new ItemElement;
	// Copy over the value.
	h->data = var->data;
	// Set the 'next' value to null (the loop will fill this in).
	h->next = NULL;
	// Point 'current' to 'head'.
	c = h;

	// Move to next item in ll's list.
	var = var->next;

	for(;var != NULL;)
	{
		// Allocate new memory for a new 'node'.
		c->next = new ItemElement;
		// Point to this new 'node'.
		c = c->next;
		// Copy over the data.
		c->data = var->data;
		// By default set the 'next' to null.
		c->next = NULL;
		// Move along ll's list.
		var = var->next;
	}
}


// Add item to linked list
void LinkedListItem::addItem(Item *newItem) {
    ItemElement* ptr = new ItemElement;
    ptr->data = newItem;
	ptr->next = NULL;
    if(h == NULL){
        h = ptr;
    }
	else{
		c = h;
        for(;c->next != NULL;){
            c = c->next;
        }
        c->next = ptr;
    }
}


// Print all items
void LinkedListItem::printItem(){
    c = h;
    for(;c!=NULL;){
		// Print first then move to jnext
		c->data->printDetail();
		c = c->next;
    }
};

// Print all out of stock items
void LinkedListItem::printOutOfStockItem() {
	c = h;
	for (;c != NULL;) {
		// Print first then move to jnext
		if (c->data->getNumberOfCopies() == 0) {
			c->data->printDetail();
		}
		c = c->next;
	}
}
// Increase Number Of Copies
void LinkedListItem::IncreaseNumberOfCopies(string id) {
	c = h;
	t = h;
	for(;c != NULL && c->data->getId() != id;) {
		t = c;
		c = c->next;
	}
	int no = c->data->getNumberOfCopies();
	c->data->setNumberOfCopies(no + 1);
};

// Decrease Number Of Copies
void LinkedListItem::DecreaseNumberOfCopies(string id) {
	c = h;
	t = h;

	for(;c != NULL && c->data->getId() != id;) {
		t = c;
		c = c->next;
	}
	int no = c->data->getNumberOfCopies();
	c->data->setNumberOfCopies(no - 1);
};

// Get object in list
void LinkedListItem::Output(LinkedListItem* list) {
	ofstream out("items.txt");
	ItemElement* t = list->h;
	for(;t != NULL;) {
		if (t->data->getGenre() != "") {
			out << t->data->getId() << "," << t->data->getTitle() << "," << t->data->getRentalType() << "," << t->data->getLoanType() << "," << t->data->getNumberOfCopies() << "," << t->data->getRentalFee() << "," << t->data->getGenre() << endl;
		}
		else {
			out << t->data->getId() << "," << t->data->getTitle() << "," << t->data->getRentalType() << "," << t->data->getLoanType() << "," << t->data->getNumberOfCopies() << "," << t->data->getRentalFee()<< endl;
		}
		t = t->next;
	}

}
// Search item by ID
ItemElement * LinkedListItem::searchItemByID(string id){

    c = h;
    t = h;
    for(;c!=NULL && toLowerCase(c->data->getId()) != toLowerCase(id);){
        t = c;
        c = c->next;
    }
    if(c == NULL){
        // No need to print message in this function. Message will be carried out by menu.
        return NULL;
    }
    return c;
};

LinkedListItem LinkedListItem::searchItemByTitle(string title) {
	c = h;

	// Initial customer list
	LinkedListItem temp_list;

	for(;c != NULL;) {
		// If match name
		if (toLowerCase(c->data->getTitle()) == toLowerCase(title)) {
			temp_list.addItem(c->data); // Add to list
		}
		c = c->next;
	}
	return temp_list;

};

// Delete item by ID
void LinkedListItem::deleteItem(string id) {
	// Considering to refactor this function because there is a repeat part in find by id.
    c = h;
    t = c;
    for(;c!=NULL;){
		// Rewrite
		if (c->data->getId() == id) {
			// Found match id
			if (c != h) {
				t->next = c->next; // behind item now will point to front item of the deleted item
				c->next = NULL; // deleted item will be remove the next
			}
			else {
				h = c->next;
			}
            delete c->data; // Free memory
            delete c; // Free memory
			return;
		}
        t = c; // track will keep the behind item of the current item in case found item to delete.
        c = c->next;
    }

}

// Sorted by id. Directly affect on linked list so need to create a deep copy linked list.
void LinkedListItem::sortedByID() {
	// The function enhance on this program
	// References: https://www.javatpoint.com/program-to-sort-the-elements-of-the-singly-linked-list
	c = h;
	t = NULL;

	if (h == NULL)
		return;
	else {
		for(;c != NULL;) {
			t = c-> next;
			for(;t != NULL;) {
				if (stoi(c->data->getId().substr(1, 3)) > stoi(t->data->getId().substr(1, 3))) {
					Item *pt = c->data;
					c->data = t->data;
					t->data = pt;
				}

				t = t->next;
			}

			c = c->next;
		}

	}

}

// Sorted by title. Directly affect on linked list so need to create a deep copy linked list.
void LinkedListItem::sortedByTitle() {
	c = h;
	t = NULL;

	if (h == NULL)
		return;
	else {
		for(;c != NULL;) {
			t = c->next;
			for(;t != NULL;) {
				if (c->data->getTitle() > t->data->getTitle()) {
					Item *pt = c->data;
					c->data = t->data;
					t->data = pt;
				}

				t = t->next;
			}

			c = c->next;
		}

	}

}


ItemElement * LinkedListItem::getHead() const {
	return h;
}

