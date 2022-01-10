#include "Item.h"
#include "GameItem.h"
#include "DVDItem.h"
#include "RecordItem.h"
#include <iostream>

using namespace std;

//Constructors
Item::Item() { //Assume this is a black item
	this->Id = "";
	this->Title = "";
	this->rental_type = "";
	this->loan_type = "";
}

Item::Item(string Id, string Title, string rental_type, string loan_type, int number_of_copies, double rental_fee) {
	this->Id = Id;
	this->Title = Title;
	this->rental_type = rental_type;
	this->loan_type = loan_type;
	this->number_of_copies = number_of_copies;
	this->rental_fee = rental_fee;
	checkStockAndSetRentalStatus();
}

Item::Item(Item& obj) {
	this->Id = obj.Id;
	this->Title = obj.Title;
	this->rental_type = obj.rental_type;
	this->loan_type = obj.loan_type;
	this->number_of_copies = obj.number_of_copies;
	this->rental_fee = obj.rental_fee;
	checkStockAndSetRentalStatus();

}

//Getters for this class
string Item::getId() const {
	return Id;
}

string Item::getTitle() const {
	return Title;
}


string Item::getRentalType() const {
	return rental_type;
}


string Item::getLoanType() const {
	return loan_type;
}


int Item::getNumberOfCopies() const {
	return number_of_copies;
}

double Item::getRentalFee() const {
	return rental_fee;
}

string Item::getRentalStatus() const {
	return rental_status;
}

string Item::getGenre() {
	return "";
}

//Setters for this class
void Item::setId(string Id) {
	this->Id = Id;
}

void Item::setTitle(string Title) {
	this->Title = Title;
}

void Item::setRentalType(string rental_type) {
	this->rental_type = rental_type;
}

void Item::setLoanType(string loan_type) {
	this->loan_type = loan_type;
}

void Item::setNumberOfCopies(int number_of_copies) {
	this->number_of_copies = number_of_copies;
	checkStockAndSetRentalStatus();
}

void Item::setRentalFee(double rental_fee) {
	this->rental_fee = rental_fee;
}

void Item::setRentalStatus(string rental_status) {
	this->rental_status = rental_status;
}

void Item::setGenre(string g) {
	this->genre = genre;
}

//Checking the stock and Rental Status
bool Item::checkStockAndSetRentalStatus() {
	//Check if the Item's number of copy are larger than 0
	if (number_of_copies > 0) {
		this->setRentalStatus("Available");
		return true;
	}
	//If number of  copy = 0 => the Item is Unavaiable or borrowed
	else {
		this->setRentalStatus("Borrowed");
		return false;
	}
}

//Renting Functions
bool Item::renting() {
	if (number_of_copies > 0) {
		//Decrease the Item's number of copy
		number_of_copies--;

		//check if this item can be rented
		checkStockAndSetRentalStatus();
		// return true if it can be rented
		return true;
	}
	//Otherwise, retrurn false
	else {
		return false;
	}
}

//Returning Functions
bool Item::returning() {
	//Increase the Item's number of copy
	number_of_copies++;

	//Update the stock and rental status
	checkStockAndSetRentalStatus();
	return true;
}

//Increasing Stock function
bool Item::increaseStock(int n) {
	number_of_copies += n;
	
	//Update the stock and rental status
	checkStockAndSetRentalStatus();
	return true;
}

//Printing Item Details
void Item::printDetail() {
		cout <<"ID: "<< this->Id <<
			"\nTittle: " << this->Title <<
			"\nRental Type: " << this->rental_type <<
			"\nLoan Type: " << this->loan_type <<
			"\nNumber of copies: " << this->number_of_copies <<
			"\nRental Fee: " << this->rental_fee <<
			"\nRental Status: " << this->rental_status <<endl;
}

//--------------------------------------- DVD Item ---------------------------------------

//Constructors
DVDItem::DVDItem(string Id, string Title, string rental_type, string loan_type, int number_of_copies, double rental_fee,string g) : Item(Id, Title, rental_type, loan_type, number_of_copies, rental_fee) {
	this->g = g;
}

//Getters and Setters
string DVDItem::getGenre() {
	return g;
}
void DVDItem::setGenre(string g) {
	this->g = g;
}

//Printing DVD Item Functions
void DVDItem::printDetail() {
	cout <<"ID: "<< this->getId() <<
		"\nTittle: " << this->getTitle() <<
		"\nRental Type: " << this->getRentalType() <<
		"\nLoan Type: " << this->getLoanType() <<
		"\nNo of copies: " << this->getNumberOfCopies() <<
		"\nRental Fee: " << this->getRentalFee() <<
		"\nGenre: " << this->getGenre() <<
		"\nRental status: " << this->getRentalStatus() <<
		"\n" << endl;
}

//--------------------------------------- Game Item ---------------------------------------
//Constructors 
GameItem::GameItem(string Id, string Title, string rental_type, string loan_type, int number_of_copies, double rental_fee) : Item(Id, Title, rental_type, loan_type, number_of_copies, rental_fee) {

}

//Printing Detail of Game Item Function
void GameItem::printDetail() {

	cout <<"ID: "<< this->getId() <<
		"\nTittle: " << this->getTitle() <<
		"\nRental Type: " << this->getRentalType() <<
		"\nLoan Type: " << this->getLoanType() <<
		"\nNumber of copies: " << this->getNumberOfCopies() <<
		"\nRental fee: " << this->getRentalFee() <<
		"\nRental Status: " << this->getRentalStatus() <<
		"\n" << endl;
}

//--------------------------------------- Record Item ---------------------------------------

//Constructors
RecordItem::RecordItem(string Id, string Title, string rental_type, string loan_type, int number_of_copies, double rental_fee, string g) : Item(Id, Title, rental_type, loan_type, number_of_copies, rental_fee) {
	this->g = g;
}

//Getter and Setter
string RecordItem::getGenre() {
	return g;
}
void RecordItem::setGenre(string g) {
	this->g = g;
}

//Printing Details of Record Item Function
void RecordItem::printDetail() {
	cout <<"ID: "<< this->getId() <<
		"\nTittle: " << this->getTitle() <<
		"\nRental Type: " << this->getRentalType() <<
		"\nLoan Type: " << this->getLoanType() <<
		"\nNumber of copies: " << this->getNumberOfCopies() <<
		"\nRental Fee: " << this->getRentalFee() <<
		"\nGenere: " << this->getGenre() <<
		"\nRental Status: " << this->getRentalStatus() <<
		"\n" << endl;

}
