#include "LinkedListRental.h"
#include "RentalListNode.h"
#include "Utilities.h"

// #include "RentalListNode.cpp" // Delete this after testing is done

using namespace std;

LinkedListRental::LinkedListRental() {
  head = NULL;
}

LinkedListRental::~LinkedListRental() {
  // TODO:: Free memory allocated to linked list
}

// Add item to the beginning of LinkedRentalList
void LinkedListRental::addItem(string a) {
	RentalListNode *new_node = new RentalListNode(a, NULL);
	RentalListNode *t = head;

  if (head == NULL) {
    // New item, make head point to it
	  head = new_node;
  } else {
	// Check if next node is NULL
    for(;t->getNext() != NULL;) {
      t = t->getNext();
    }
	// Set the next node(item)
	t->setNext(new_node);
	// Head is always the first one so cannot set the head = temp
  }
}
// Is List Rentals have this Id
bool LinkedListRental::isListHaveId(string i) {
    RentalListNode* t = head;
    for(;t != NULL;) {
        if (toLowerCase(t->getItem()).compare(toLowerCase(i)) == 0) {
            return true;
        }
        t = t->getNext();
    }
    return false;
}
void LinkedListRental::removeItem(string a) {
  RentalListNode *t = head;
  RentalListNode *p = NULL;

  for(;t != NULL;) {
    if (toLowerCase(t->getItem()) == toLowerCase(a)) {
      if (p== NULL) {
        // Delete the head of the list
        head = head->getNext();
        delete t;
      } else {
        p->setNext(t->getNext());
        delete t;
      }
      break;
    }
    p = t;
    t = t->getNext();
  }
}

void LinkedListRental::showItem() {
  RentalListNode *t = head;
  for(;t != NULL;) {
    cout <<"Item: "<< t->getItem() << endl;
    t = t->getNext();
  }
}

RentalListNode * LinkedListRental::getHead() {
    return head;
}

ostream& operator<<(ostream& o, const LinkedListRental& l)
{
    RentalListNode* t = l.head;
    for(;t != NULL;) {
        o << t->getItem() << endl;
        t = t->getNext();
    }
    return o;
}
