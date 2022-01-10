#pragma once

#include "string"

using namespace std;

class Item {

private:
	string Id, Title, rental_type, rental_status, loan_type, genre;
	int number_of_copies;
	double rental_fee;

public:
	string getId() const;

	string getTitle() const;

	string getRentalType() const;

	string getLoanType() const;

	int getNumberOfCopies() const;

	double getRentalFee() const;

	string getRentalStatus() const;

	string getGenre() const;

	void setId(const string Id);

	void setTitle(const string Title);

	void setRentalType(const string rental_type);

	void setLoanType(const string loan_type);

	void setNumberOfCopies(int number_of_copies);

	void setRentalFee(double rental_fee);

	void setRentalStatus(string rental_status);

	Item();

	Item(string Id, string Title, string rental_type, string loan_type, int number_of_copies, double rental_fee);

	Item(Item& obj);

	bool renting();

	bool returning();

	bool increaseStock(int n);

	//Check the stock number and set the item's status
	bool checkStockAndSetRentalStatus();

	//Polymorphism - Virtual Functions
	virtual void printDetail();
	virtual string getGenre();
	virtual void setGenre(string g);
};
