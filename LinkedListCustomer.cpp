#include "LinkedListCustomer.h"
#include "CustomerNode.h"
#include "Customer.h"
#include<iostream>
#include<fstream>
#include "Utilities.h"

LinkedListCustomer::LinkedListCustomer(){
    h = NULL;
    t = NULL;
    la = NULL;
    tr = NULL;
    curr = NULL;
}

//Copy Constructor
// References: https://stackoverflow.com/questions/7811893/creating-a-copy-constructor-for-a-linked-list
LinkedListCustomer::LinkedListCustomer(const LinkedListCustomer& ll)
{
	if (ll.h == NULL) {
		h = NULL;
		return;
	}
	// Create a t variable since ll.curr doesn't move/change.
	CustomerNode* temp = ll.h;

	// Allocate a new node in memory.
	h = new CustomerNode;
	// Copy over the value.
	h->data = temp->data;
	// Set the 'next' value to null (the loop will fill this in).
	h->next = NULL;
	// Point 'curr' to 'h'.
	curr = h;

	// Move to next item in ll's list.
	temp = temp->next;

	for(;temp != NULL;)
	{
		// Allocate new memory for a new 'node'.
		curr->next = new CustomerNode;
		// Point to this new 'node'.
		curr = curr->next;
		// Copy over the data.
		curr->data = temp->data;
		// By default set the 'next' to null.
		curr->next = NULL;
		// Move along ll's list.
		temp = temp->next;
	}
}

CustomerNode * LinkedListCustomer::getHead() const {
    return h;
}

// Add item to linked list
void LinkedListCustomer::addCustomer(Customer *newItem) {
    CustomerNode* temp = new CustomerNode;
    temp->data = newItem;
    temp->next = NULL;
    if(h == NULL){
        h = temp;
    }
    else{
        t = h;
        for(;t->next != NULL;){
            t = t->next;
        }
        t->next = temp;
    }
}
//
//
// Print all item
void LinkedListCustomer::printAllCustomer(){
    t = h;
    for(;t!=NULL;){
        // Print first then move to jnext
        t->data->details();
        cout << "-----------------------------------" << endl;
        t = t->next;
    }
};
//
//// Search customer by ID
CustomerNode * LinkedListCustomer::searchCustomerByID(string id){
    t = h;
    tr = h;

    for(;t!=NULL && toLowerCase(t->data->getId()) != toLowerCase(id);){
        tr = t;
        t = t->next;
    }
    if(t == NULL){
        // No need to print message in this function. Message will be carried out by menu.
        return NULL;
    }
    return t;
};

LinkedListCustomer LinkedListCustomer::searchCustomerByName(string name) {
	t = h;
	tr = h;

	// Initial customer list
    LinkedListCustomer tempList;

	for(;t != NULL;) {
		// If match name.
		// We converted name to lowercase to increase roburstness and flexibility.
		if (toLowerCase(t->data->getName()) == toLowerCase(name)) {
			tempList.addCustomer(t->data); // Add to list
		}
		tr = t;
		t = t->next;
	}
	return tempList;
}
// Delete item by ID
void LinkedListCustomer::deleteCustomer(string id) {
    // Considering to refactor this function because there is a repeat part in find by id.
    t = h;
    tr = t;
    for(;t!=NULL;){
        // Rewrite
        if (t->data->getId() == id) {
            // Found match id
            if (t != h) {
                tr->next = t->next; // behind item now will point to front item of the deleted item
                t->next = NULL; // deleted item will be remove the next
            }
            else {
                h = t->next;
            }
            delete t->data; // free memory
            delete t; // free memory
            return;
        }
        tr = t; // tr will keep the behind item of the curr item in case found item to delete.
        t = t->next;
    }

}

// Sorted by id. Directly affect on linked list so need to create a deep copy linked list.
void LinkedListCustomer::sortedByID() {
    // The function enhance on this program
    // References: https://www.javatpoint.com/program-to-sort-the-elements-of-the-singly-linked-list
    curr = h;
    tr = NULL;

    if (h == NULL)
        return;
    else {
        for(;curr != NULL;) {
            tr = curr-> next;
            for (;tr != NULL;) {
                if (stoi(curr->data->getId().substr(1, 3)) > stoi(tr->data->getId().substr(1, 3))) {
                    Customer *t = curr->data;
                    curr->data = tr->data;
                    tr->data = t;
                }
                tr = tr->next;
            }
            curr = curr->next;
        }
    }
}

// Sorted by title. Directly affect on linked list so need to create a deep copy linked list.
void LinkedListCustomer::sortedByName() {
    curr = h;
    tr = NULL;

    if (h == NULL)
        return;
    else {
        for(;curr != NULL;) {
            tr = curr->next;
            for(;tr != NULL;) {
                if (toLowerCase(curr->data->getName()) > toLowerCase(tr->data->getName())) {
                    Customer *t = curr->data;
                    curr->data = tr->data;
                    tr->data = t;
                }

                tr = tr->next;
            }

            curr = curr->next;
        }

    }

}




CustomerNode* LinkedListCustomer::getHead() {
	return h;
}

void LinkedListCustomer::Output(LinkedListCustomer* list) {
	ofstream out;
	out.open("customers.txt");
    CustomerNode* t = list->h;
    for (;t != NULL;) {
        if (t->data->typeCustomer() == 1) {
            out << t->data->getId() << "," << t->data->getName() << "," << t->data->getAddress() << "," << t->data->getPhoneNumber() << "," << t->data->getNumberOfRental() << "," << "Regular" << endl;
            out << t->data->getRentalList2();
        }
        if (t->data->typeCustomer() == 2) {
            out << t->data->getId() << "," << t->data->getName() << "," << t->data->getAddress() << "," << t->data->getPhoneNumber() << "," << t->data->getNumberOfRental() << "," << "VIP" << endl;
            out << t->data->getRentalList2();
        }
        if (t->data->typeCustomer() == 3) {
            out << t->data->getId() << "," << t->data->getName() << "," << t->data->getAddress() << "," << t->data->getPhoneNumber() << "," << t->data->getNumberOfRental() << "," << "Guest" << endl;
            out << t->data->getRentalList2();
        }

        t = t->next;
    }

}
