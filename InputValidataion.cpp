#include "InputValidation.h"
#include <iostream>
#include <string>

using namespace std;

// All validating functions will return true if input is in correct format, false otherwise

//---------------------------------------- Validate Customer Input ----------------------------------------

//Validate Customer ID Input
bool validateCustomerID(string CustomerInput, string CustomerMode) {
	if (CustomerInput[0] != 'C' &&
		CustomerInput[0] != 'c') {
		if (CustomerMode == "input") {
			cout << "ERROR: Id must start with 'C'. \nPlease try again." << endl;
		}
		return false;
	}

	if (CustomerInput.length() != 4) {
		if (CustomerMode == "input") {
			cout << "ERROR: Wrong format.\n Please try again." << endl;
		}
		return false;
	}
	int temp = 1;
	while (temp < 4) {
		if (!isdigit(CustomerInput[temp])) {
			if (CustomerMode == "input") {
				cout << "ERROR: 'xxx' number has already been taken.\n Please try again." << endl;
			}
			return false;
		}
		temp++;
	}
	return true;
}

// Validate Customer's name Input. Ipunt Name cannot contains special characters
bool validateCustomerName(string CustomerInput, string CustomerMode) {
	int j = 0;
	while (j < CustomerInput.length()) {
		//Use ASCII table to set the range of character, if it's outside the range -> they are special characters
		if (!((CustomerInput[j] >= 65
			&& CustomerInput[j] <= 90) ||
			(CustomerInput[j] >= 97 &&
				CustomerInput[j] <= 122) ||
			CustomerInput[j] == 32)) {
			if (CustomerMode == "input") {
				cout << "ERROR: Name cannot contain special characters.\n Please try again." << endl;
			}
			return false;
		}
		j++;
	}
	return true;
}

//Validate Customer's Address Input
bool validateCustomerAddress(string CustomerInput, string CustomerMode) {
	int j = 0;
	while (j < CustomerInput.length()) {
		//Using ASCII table to set the conditions
		if ((CustomerInput[j] >= 33 && CustomerInput[j] <= 43) ||
			(CustomerInput[j] >= 58 && CustomerInput[j] <= 64) ||
			(CustomerInput[j] >= 91 && CustomerInput[j] <= 96) ||
			(CustomerInput[j] >= 123)) {

			if (CustomerMode == "input") {
				cout << "ERROR: Address cannot contain special characters.\n Please try again." << endl;
			}

			return false;
		}
		j++;
	}
	return true;
}

//Validate Customer's Phone Number input
bool validateCustomerPhoneNumber(string CustomerInput, string CustomerMode) {

	// Because the specification did not mention about the format of the phone number like maxium of digit.
	// So we will assume base on database files that it only contains 10 digits.
	if (CustomerInput.length() != 10) {
		if (CustomerMode == "input") {
			cout << "ERROR: Wrong format, Phone Number must contain 10 digits.\n Please try again." << endl;
		}
		return false;
	}
	int k = 0;
	while (k < 10) {
		if (!isdigit(CustomerInput[k])) {
			if (CustomerMode == "input") {
				cout << "ERROR: Phone number must only contains 10 digits.\n Please try agian." << endl;
			}
			return false;
		}
		k++;
	}
	return true;
}

//Validate Customer's Number of Rental Inpout
bool validateCustomerNumberOfRental(string CustomerInput, string CustomerMode) {
	// Number of copies must be a string contains digit only
	int k = 0;
	while (k < CustomerInput.length()) {
		if (!isdigit(CustomerInput[k])) {
			if (CustomerMode == "input") {
				cout << "ERROR: Number of rental can only contain digits.\n Please try again." << endl;
			}
			return false;
		}
		k++;
	}
	return true;
}

//Validate Customer's Type Input
bool validateCustomerType(string CustomerInput, string CustomerMode) {
	if (CustomerInput.length() == 0) {
		return false;
	}
	if (CustomerInput != "guest" &&
		CustomerInput != "regular" &&
		CustomerInput != "vip" &&
		CustomerInput != "Guest" &&
		CustomerInput != "Regular" &&
		CustomerInput != "VIP") {
		if (CustomerMode == "input") {
			cout << "ERROR: Type must be 'Guest', 'Regular' or 'VIP'.\n Please try again." << endl;
		}
		return false;
	}
	return true;
}

//---------------------------------------- Validate Item Input ----------------------------------------

//Validate Item ID input
bool validateItemID(string ItemInput, string ItemMode) {
	if (ItemInput[0] != 'I' && ItemInput[0] != 'i') {
		if (ItemMode == "input") {
			cout << "ERROR: Item's ID must start with 'I'.\n Please try again." << endl;
		}
		else if (ItemMode == "readFile") {
			cout << "";
		}

		return false;
	}

	//Validate item's -XXX number, if exist, return failed
	int j = 1;
	while (j < 4)
	{
		if (!isdigit(ItemInput[j])) {
			if (ItemMode == "input") {
				cout << "ERROR: 'xxx' has already been taken.\nPlease try again." << endl;
			}
			else if (ItemMode == "readFile") {
				cout << "";
			}

			return false;
		}
		j++;
	}

	//Validate item's ID format
	if (ItemInput[4] != '-' || ItemInput.length() != 9) {
		if (ItemMode == "input") {
			cout << "ERROR: Wrong format.\n Please try again." << endl;
		}
		else if (ItemMode == "readFile") {
			cout << "";
		}

		return false;
	}
	string y;
	int i = 5;
	while (i < 9) {
		//Validate  Item's ID YYYY chars are digits
		y.push_back(ItemInput[i]);
		if (!isdigit(ItemInput[i])) {
			if (ItemMode == "input") {
				cout << "ERROR: 'yyyy' should represent the year.\n Please try again." << endl;
			}
			else if (ItemMode == "readFile") {
				cout << "";
			}

			return false;
		}
		i++;
	}
	//Validate Item's ID YYYY, As year 
	if (stoi(y) > 2021 || stoi(y) < 1900) {
		if (ItemMode == "input") {
			cout << "ERROR: 'Year must be between 1900 and 2021.\n Please try again." << endl;
		}
		else if (ItemMode == "readFile") {
			cout << "";
		}

		return false;
	}
	return true;
}

//Validate Item's Title
bool validateTitle(string ItemInput, string ItemMode) {
	//Title cannot contain "," since it is used to seperate data in the .txt file
	int j = 0;
	while (j < ItemInput.length()) {
		if (ItemInput[j] == ',') {
			if (ItemMode == "input") {
				cout << "ERROR: Item's title cannot contain Comma (,).\n Please try again." << endl;
			}
			else if (ItemMode == "readFile") {
				cout << "";
			}

			return false;
		}
		j++;
	}
	return true;
}

//Validate Item's Rental Type (Game, DVD, Record)
bool validateRentalType(string ItemInput, string ItemMode) {
	// Genre can only in three categories: Game, DVD, Record
	if (ItemInput != "game" &&
		ItemInput != "dvd" &&
		ItemInput != "record" &&
		ItemInput != "Game" &&
		ItemInput != "DVD" &&
		ItemInput != "Record") {
		if (ItemMode == "input") {
			cout << "ERROR: Rental type must be 'Game' 'DVD' or 'Record'.\nPlease try again." << endl;
		}
		else if (ItemMode == "readFile") {
			cout << "";
		}
		return false;
	}
	return true;
}

//Validate Item's Loan Type (2-day, 1-week)
bool validateLoanType(string ItemInput, string ItemMode) {
	// Loan type can only in two categories: 2-days and 1-week
	if (ItemInput != "2-day" && ItemInput != "1-week") {
		if (ItemMode == "input") {
			cout << "ERROR: Loan type must be 2-day or 1-week.\n Please try again." << endl;
		}
		else if (ItemMode == "readFile") {
			cout << "";
		}
		return false;
	}
	return true;
}

//Validate Item's Number of copies 
bool validateNumberOfCopies(string ItemInput, string ItemMode) {
	//Item's number of copies should be a string which contains only numbers
	int j = 0;
	while (j < ItemInput.length()) {
		if (!isdigit(ItemInput[j])) {
			if (ItemMode == "input") {
				cout << "ERROR: Number of Copies can only be number.\n Please try again." << endl;
			}
			else if (ItemMode == "readFile") {
				cout << "";
			}

			return false;
		}
		j++;
	}
	return true;
}

//Validate Item's Rental Fees
bool validateRentalFee(string ItemInput, string ItemMode) {
	int d = 0;
	//Check the input's length. If = 0, it is an empty string
	if (ItemInput.length() == 0) {
		if (ItemMode == "input") {
			cout << "ERROR: Wrong format of fee.\n Please try again." << endl;
		}
		else if (ItemMode == "readFile") {
			cout << "";
		}
		return false;
	}

	int k = 0;
	while (k < ItemInput.length()) {
		if (!isdigit(ItemInput[k])) {
			if (ItemInput[k] == '.' && d < 1) {
				d++;
			}
			else {
				if (ItemMode == "input") {
					cout << "ERROR: Wrong Format of fee.\nPlease try again." << endl;
				}
				else if (ItemMode == "readFile") {
					cout << "";
				}
				return false;
			}
		}
		k++;
	}
	return true;
}

//Validate Item's Gerne
bool validateGenre(string ItemInput, string ItemMode) {
	// Genre can only in four categories: Horror, Comedy, Drama, Action
	if (ItemInput != "Horror" &&
		ItemInput != "Comedy" &&
		ItemInput != "Drama" &&
		ItemInput != "Action") {
		if (ItemMode == "input") {
			cout << "ERROR: Item Genre must be 'Horror', 'Comedy', 'Drama' or 'Action'.\n Please try again." << endl;
		}
		else if (ItemMode == "readFile") {
			cout << "";
		}
		return false;
	}
	return true;
}