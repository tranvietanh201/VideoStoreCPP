#include "InputValidation.h"
#include <iostream>
#include <string>

using namespace std;

// All validating functions will return true if input is in correct format, false otherwise

//---------------------------------------- Validate Customer Input ----------------------------------------

//Validate Customer ID Input
bool validateCustomerID(string CustomerInput, string mod) {
	if (CustomerInput[0] != 'C' &&
		CustomerInput[0] != 'c') {
		if (mod == "input") {
			cout << "ERROR: Id must start with 'C'. \nPlease try again." << endl;
		}
		return false;
	}

	if (CustomerInput.length() != 4) {
		if (mod == "input") {
			cout << "ERROR: Wrong format.\n Please try again." << endl;
		}
		return false;
	}
	int temp = 1;
	while (temp < 4) {
		if (!isdigit(CustomerInput[temp])) {
			if (mod == "input") {
				cout << "ERROR: 'xxx' number has already been taken.\n Please try again." << endl;
			}
			return false;
		}
		temp++;
	}
	return true;
}

// Validate Customer's name Input. Ipunt Name cannot contains special characters
bool validateCustomerName(string CustomerInput, string mod) {
	int j = 0;
	while (j < CustomerInput.length()) {
		//Use ASCII table to set the range of character, if it's outside the range -> they are special characters
		if (!((CustomerInput[j] >= 65
			&& CustomerInput[j] <= 90) ||
			(CustomerInput[j] >= 97 &&
				CustomerInput[j] <= 122) ||
			CustomerInput[j] == 32)) {
			if (mod == "input") {
				cout << "ERROR: Name cannot contain special characters.\n Please try again." << endl;
			}
			return false;
		}
		j++;
	}
	return true;
}

//Validate Customer's Address Input
bool validateCustomerAddress(string CustomerInput, string mod) {
	int j = 0;
	while (j < CustomerInput.length()) {
		//Using ASCII table to set the conditions
		if ((CustomerInput[j] >= 33 && CustomerInput[j] <= 43) ||
			(CustomerInput[j] >= 58 && CustomerInput[j] <= 64) ||
			(CustomerInput[j] >= 91 && CustomerInput[j] <= 96) ||
			(CustomerInput[j] >= 123)) {

			if (mod == "input") {
				cout << "ERROR: Address cannot contain special characters.\n Please try again." << endl;
			}

			return false;
		}
		j++;
	}
	return true;
}

//Validate Customer's Phone Number input
bool validateCustomerPhoneNumber(string CustomerInput, string mod) {

	// Because the specification did not mention about the format of the phone number like maxium of digit.
	// So we will assume base on database files that it only contains 10 digits.
	if (CustomerInput.length() != 10) {
		if (mod == "input") {
			cout << "ERROR: Wrong format, Phone Number must contain 10 digits.\n Please try again." << endl;
		}
		return false;
	}
	int k = 0;
	while (k < 10) {
		if (!isdigit(CustomerInput[k])) {
			if (mod == "input") {
				cout << "ERROR: Phone number must only contains 10 digits.\n Please try agian." << endl;
			}
			return false;
		}
		k++;
	}
	return true;
}

//Validate Customer's Number of Rental Inpout
bool validateCustomerNumberOfRental(string CustomerInput, string mod) {
	// Number of copies must be a string contains digit only
	int k = 0;
	while (k < CustomerInput.length()) {
		if (!isdigit(CustomerInput[k])) {
			if (mod == "input") {
				cout << "ERROR: Number of rental can only contain digits.\n Please try again." << endl;
			}
			return false;
		}
		k++;
	}
	return true;
}

//Validate Customer's Type Input
bool validateCustomerType(string CustomerInput, string mod) {
	if (CustomerInput.length() == 0) {
		return false;
	}
	if (CustomerInput != "guest" &&
		CustomerInput != "regular" &&
		CustomerInput != "vip" &&
		CustomerInput != "Guest" &&
		CustomerInput != "Regular" &&
		CustomerInput != "VIP") {
		if (mod == "input") {
			cout << "ERROR: Type must be 'Guest', 'Regular' or 'VIP'.\n Please try again." << endl;
		}
		return false;
	}
	return true;
}

//---------------------------------------- Validate Item Input ----------------------------------------

//Validate Item ID input
bool validateItemID(string inp, string mod) {
	if (inp[0] != 'I' && inp[0] != 'i') {
		if (mod == "input") {
			cout << "ERROR: Item's ID must start with 'I'.\n Please try again." << endl;
		}
		else if (mod == "readFile") {
			cout << "";
		}

		return false;
	}

	//Validate item's -XXX number, if exist, return failed
	int j = 1;
	while (j < 4)
	{
		if (!isdigit(inp[j])) {
			if (mod == "input") {
				cout << "ERROR: 'xxx' has already been taken.\nPlease try again." << endl;
			}
			else if (mod == "readFile") {
				cout << "";
			}

			return false;
		}
		j++;
	}

	//Validate item's ID format
	if (inp[4] != '-' || inp.length() != 9) {
		if (mod == "input") {
			cout << "ERROR: Wrong format.\n Please try again." << endl;
		}
		else if (mod == "readFile") {
			cout << "";
		}

		return false;
	}
	string y;
	int i = 5;
	while (i < 9) {
		//Validate  Item's ID YYYY chars are digits
		y.push_back(inp[i]);
		if (!isdigit(inp[i])) {
			if (mod == "input") {
				cout << "ERROR: 'yyyy' should represent the year.\n Please try again." << endl;
			}
			else if (mod == "readFile") {
				cout << "";
			}

			return false;
		}
		i++;
	}
	//Validate Item's ID YYYY, As year 
	if (stoi(y) > 2021 || stoi(y) < 1900) {
		if (mod == "input") {
			cout << "ERROR: 'Year must be between 1900 and 2021.\n Please try again." << endl;
		}
		else if (mod == "readFile") {
			cout << "";
		}

		return false;
	}
	return true;
}

//Validate Item's Title
bool validateTitle(string inp, string mod) {
	//Title cannot contain "," since it is used to seperate data in the .txt file
	int j = 0;
	while (j < inp.length()) {
		if (inp[j] == ',') {
			if (mod == "input") {
				cout << "ERROR: Item's title cannot contain Comma (,).\n Please try again." << endl;
			}
			else if (mod == "readFile") {
				cout << "";
			}

			return false;
		}
		j++;
	}
	return true;
}

//Validate Item's Rental Type (Game, DVD, Record)
bool validateRentalType(string inp, string mod) {
	// Genre can only in three categories: Game, DVD, Record
	if (inp != "game" &&
		inp != "dvd" &&
		inp != "record" &&
		inp != "Game" &&
		inp != "DVD" &&
		inp != "Record") {
		if (mod == "input") {
			cout << "ERROR: Rental type must be 'Game' 'DVD' or 'Record'.\nPlease try again." << endl;
		}
		else if (mod == "readFile") {
			cout << "";
		}
		return false;
	}
	return true;
}

//Validate Item's Loan Type (2-day, 1-week)
bool validateLoanType(string inp, string mod) {
	// Loan type can only in two categories: 2-days and 1-week
	if (inp != "2-day" && inp != "1-week") {
		if (mod == "input") {
			cout << "ERROR: Loan type must be 2-day or 1-week.\n Please try again." << endl;
		}
		else if (mod == "readFile") {
			cout << "";
		}
		return false;
	}
	return true;
}

//Validate Item's Number of copies 
bool validateNumberOfCopies(string inp, string mod) {
	//Item's number of copies should be a string which contains only numbers
	int j = 0;
	while (j < inp.length()) {
		if (!isdigit(inp[j])) {
			if (mod == "input") {
				cout << "ERROR: Number of Copies can only be number.\n Please try again." << endl;
			}
			else if (mod == "readFile") {
				cout << "";
			}

			return false;
		}
		j++;
	}
	return true;
}

//Validate Item's Rental Fees
bool validateRentalFee(string inp, string mod) {
	int d = 0;
	//Check the input's length. If = 0, it is an empty string
	if (inp.length() == 0) {
		if (mod == "input") {
			cout << "ERROR: Wrong format of fee.\n Please try again." << endl;
		}
		else if (mod == "readFile") {
			cout << "";
		}
		return false;
	}

	int k = 0;
	while (k < inp.length()) {
		if (!isdigit(inp[k])) {
			if (inp[k] == '.' && d < 1) {
				d++;
			}
			else {
				if (mod == "input") {
					cout << "ERROR: Wrong Format of fee.\nPlease try again." << endl;
				}
				else if (mod == "readFile") {
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
bool validateGenre(string inp, string mod) {
	// Genre can only in four categories: Horror, Comedy, Drama, Action
	if (inp != "Horror" &&
		inp != "Comedy" &&
		inp != "Drama" &&
		inp != "Action") {
		if (mod == "input") {
			cout << "ERROR: Item Genre must be 'Horror', 'Comedy', 'Drama' or 'Action'.\n Please try again." << endl;
		}
		else if (mod == "readFile") {
			cout << "";
		}
		return false;
	}
	return true;
}