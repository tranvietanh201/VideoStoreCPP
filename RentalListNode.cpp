#include "RentalListNode.h"
#include <string>
#include <iostream>

using namespace std;

RentalListNode::RentalListNode() : data(""), next(NULL) {}

RentalListNode::RentalListNode(string item_name, RentalListNode* next_node): data(item_name), next(next_node) {}

string RentalListNode::getItem() {
	return data;
}

RentalListNode* RentalListNode::getNext() {
  return next;
}

void RentalListNode::setNext(RentalListNode *next_node) {
  next = next_node;
}

