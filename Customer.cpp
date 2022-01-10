#include "Customer.h"
#include "GuestMember.h"
#include "VipMember.h"
#include "RegularMember.h"
#include <iostream>

using namespace std;

Customer::Customer() { //Assume that this is a blank customer
	this->Id = "";
	this->Name = "";
	this->Address = "";
	this->PhNo = "";
	this->number_of_rental = 0;

	this->rental_list;
	this->Type = "";
}

Customer::Customer(string Id, string Name, string Address, string PhNo, int number_of_rental) {
	this->Type = "";
	this->Id = Id;
	this->Name = Name;
	this->Address = Address;
	this->PhNo = PhNo;
	this->number_of_rental = number_of_rental;
	this->rental_list;
}

//Getters for this class
string Customer::getId() const {
	return Id;
}

string Customer::getName() const {
	return Name;
}

string Customer::getAddress() const {
	return Address;
}

string Customer::getPhoneNumber() const {
	return PhNo;
}
int Customer::getNumberOfRental() {
	return number_of_rental;
}

int Customer::getNumberOfReturnedItems() {
	return number_of_returnedItems;
}

//Setters for this class
void Customer::setId(string Id) {
	this->Id = Id;
}

void Customer::setRentalList(LinkedListRental& rental_list) {
	this->rental_list = rental_list;
}

void Customer::setName(string Name) {
	this->Name = Name;
}

void Customer::setAddress(string Address) {
	this->Address = Address;
}

void Customer::setPhoneNumber(string PhNo) {
	this->PhNo = PhNo;
}

void Customer::setNumberOfRental(const int number_of_rental) {
	this->number_of_rental = number_of_rental;
}

void Customer::setNumberOfReturnedItems(const int number_of_returnedItems) {
	this->number_of_returnedItems = number_of_returnedItems;
}

LinkedListRental* Customer::getRentalList1() {
	return &rental_list;
}

LinkedListRental Customer::getRentalList2() {
	return rental_list;
}

void Customer::details() {
	cout << "ID : " << this->Id << ", Name:  " << this->Name << ",  Address:  " << this->Address 
		<< ", Phone No:  " << this->PhNo << endl;
}

void Customer::showRentalList() {
	rental_list.showItem();
}

void Customer::rentItem(const string Item_Name, LinkedListItem& item_list) {

	ItemElement* i = item_list.searchItemByID(Item_Name);
	i->data->renting();
	//Increase the customer's number of rented item
	this->number_of_rental++;
	rental_list.addItem(Item_Name);
}

void Customer::returnItem(const string Item_Name) {
	//Decrease the customer's number of rented item
	this->number_of_rental--;
	//Increase the item's number of copies
	this->number_of_returnedItems++;
	rental_list.removeItem(Item_Name);
}

string Customer::getType() const {
	return Type;
}

void Customer::setType(const string& Type) {
	this->Type = Type;
}

int Customer::typeCustomer() {
	return 0;
}

//Show rental list and return Customer's type
void GuestMember::showRentalList() {
	this->Customer::showRentalList();
}
int GuestMember::typeCustomer() {
	return 3;
}

void RegularMember::showRentalList() {
	this->Customer::showRentalList();
}
int RegularMember::typeCustomer() {
	return 1;
}

void VipMember::showRentalList() {
	this->Customer::showRentalList();
}
int VipMember::typeCustomer() {
	return 2;
}

//--------------------------------------- Guest Member ---------------------------------------

// Guest Member's Constructors
GuestMember::GuestMember() {
	this->setType("Guest");
	this->setNumberOfReturnedItems(0);
}


GuestMember::GuestMember(string Id, string Name, string Address, string PhNo, int number_of_rental) : Customer(Id, Name, Address, PhNo, number_of_rental) {
	this->setType("Guest");
	this->setNumberOfReturnedItems(0);
}

//Guest Member's functions

//Renting Function for Guest Member
void GuestMember::rentItem(const string Item_Name, LinkedListItem& item_list) {
	//Check if this customer reached the renting limitation (2 items)
	if (this->getNumberOfRental() < GUEST_RENT_LIMIT) {
		ItemElement* item = item_list.searchItemByID(Item_Name);
		//Set the condition: Guest Member can only rent 1-Week items
		if (item->data->getLoanType() != "1-week") {
			cout << "FAIL!!!: Guest member can only rent 1-week item." << endl;
		}
		else {
			cout << "SUCCESS!!!: Guest customer " << this->getName() << " rented item successfully!" << endl;
			this->Customer::rentItem(Item_Name, item_list);
		}
	}
	else {
		cout << "FAIL!!!: Sorry! Guest member can only rent " << GUEST_RENT_LIMIT << " items at a time!" << endl;
		cout << "FAIL!!!: Please return the rented items befor renting new Items!" << endl;
	}
}

//Returning Function for Guest Member
void GuestMember::returnItem(const string Item_Name) {
	cout << "SUCCESS!!!: Guest customer: " << this->getName() << " returned item successfully!" << endl;
	this->Customer::returnItem(Item_Name);
}

//Printing details Funtion for Guest Member
void GuestMember::details() {
	cout << "\nCustomer ID: " << this->getId() <<
		"\nType: Guest" <<
		"\nName: " << this->getName() <<
		"\nAddress: " << this->getAddress() <<
		"\nPhone Number: " << this->getPhoneNumber() << 
		"\nCurrently renting: " << endl;

	this->showRentalList();
}

//--------------------------------------- Regular Member ---------------------------------------

// Regular Member's Constructors
RegularMember::RegularMember() {
	this->setType("Regular");
	this->setNumberOfReturnedItems(0);
}

RegularMember::RegularMember(string Id, string Name, string Address, string PhNo, int number_of_rental) : Customer(Id, Name, Address, PhNo, number_of_rental) {
	this->setType("Regular");
	this->setNumberOfReturnedItems(0);
}

//Regular Member's Functions

//Renting Function for Regular member
void RegularMember::rentItem(const string Item_Name, LinkedListItem& item_list) {
	this->Customer::rentItem(Item_Name, item_list);
	cout << "Regular customer " << this->getName() << " rented item successfully!" << endl;
}

//Returning Funtion for Regular Member
void RegularMember::returnItem(const string Item_Name) {
	cout << "Regular customer " << this->getName() << " returned item successfully!" << endl;
	this->Customer::returnItem(Item_Name);
}

//Printing details function for Regular Member
void RegularMember::details() {
	cout << "Customer ID: " << this->getId() <<
		"\nType: Regular" <<
		"\nName: " << this->getName() <<
		"\nAddress: " << this->getAddress() <<
		"\nPhone Number: " << this->getPhoneNumber() <<
		"\nCurrently renting: " << endl;
	this->showRentalList();
}

//--------------------------------------- VIP Member ---------------------------------------

//VIP Member's Constructors
VipMember::VipMember() {
	this->reward = 0;
	this->freeRentItem = 0;
	this->setType("VIP");
	this->setNumberOfReturnedItems(0);
}

VipMember::VipMember(string Id, string Name, string Address, string PhNo, int number_of_rental) : Customer(Id, Name, Address, PhNo, number_of_rental) {
	this->reward = 0;
	this->freeRentItem = 0;
	this->setType("VIP");
	this->setNumberOfReturnedItems(0);
}

//VIP Member's Functions

//Renting Function for VIP Member
void VipMember::rentItem(const string Item_Name, LinkedListItem& item_list) {

	//Case 1:  If they meet the exchange condition, the will have 1 free rent time.
	if (this->reward >= VIP_EXCHANGE_CONDITION) {
		cout << "CONGRATULATIONS!!!: " << this->getName() << ", you have 1 free rent in your account!" << endl;
		this->freeRentItem++;
		this->Customer::rentItem(Item_Name, item_list);
		//Reduce the Exchange point
		this->reward -= VIP_EXCHANGE_CONDITION;
		cout << "WARNING:Total Free Rent Items awarded: " << freeRentItem << endl;
		cout << endl;
	}
	
	//Case 2: If they do NOT have enough exchange point, rent an item will increase their point
	else {
		this->Customer::rentItem(Item_Name, item_list);
		this->reward += VIP_POINTS;
		cout << "CONGRATULATIONS!!!: VIP customer: " << this->getName() << " rented item successfully, you reward balance received 10 points!" << endl;
		cout << "WARNING: Your current Reward Points are " << reward << endl;

		//If their point reach 100 after this Rent, Announce them about their next free renting
		if (reward == VIP_EXCHANGE_CONDITION) {
			cout << "CONGRATULATIONS!!!: You got 100 reward points, now you can get a free rent item for your next purchase!" << endl;
		}
		else {
			cout << "If you have 100 Reward Points, you would be awarded with a free rent Item!" << endl;
		}
		cout << endl;
	}
}

//Returning function for VIP Member
void VipMember::returnItem(const string Item_Name) {
	this->Customer::returnItem(Item_Name);
	cout << "CONGRATULATIONS!!!: VIP customer " << this->getName() << " successfully returned an item!" << endl;
	//Reduce the number of reting items

}

//Checking Reward Point function for VIP Member
void VipMember::checkRewardPoints() {
	cout << "Your total reward points are: " << this->reward << endl;
}

//Printing details Function for VIP Member
void VipMember::details() {
	cout << "Customer ID: " << this->getId() <<
		"\nType: VIP" <<
		"\nReward Points :" << this->reward <<
		"\nName: " << this->getName() <<
		"\nAddress: " << this->getAddress() <<
		"\nPhone Number: " << this->getPhoneNumber() <<
		"\nCurrent Renting: "<< endl;
	this->showRentalList();
}