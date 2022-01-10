#include<iostream>
#include<fstream>
#include <string>

#include "CustomerInfo.h"
#include "Customer.h"
#include "GuestMember.h"
#include "RegularMember.h"
#include "VipMember.h"
#include "InputValidation.h"

using namespace std;

void CustomerData(LinkedListCustomer& CL, string FN) {
	string a;
	ifstream myfile(FN);
	if (myfile)
	{
		// Initialize pointer to a customer
		Customer* obj = NULL;
		LinkedListRental* l;
		int temp3 = 0, lp = 0, cn;
		// Track the line number
		 // Check if the number of rental is matching with list of rentals

		while (getline(myfile, a))  // same as: while (getline( myfile, line ).good())
		{
			lp++;
			if (a[0] == 'C') {
				cn = 0;
				// Customer infomation in txt file will be store in the string array
				string lt[6], t, d = ",";
				// This attribute will help to find the comma
				size_t position = 0;
				int temporary = 0;
				// If comma still exist, continue looping
				while ((position = a.find(d)) != string::npos) {
					t = a.substr(0, position);
					if (t == "") // Check if there is any missing information
						lt[temporary] = "N/A";
					else
						lt[temporary] = t;
					a.erase(0, position + d.length());
					temporary++;
				}
				lt[temporary] = a;

				// Validate cusomer information format in each column

				do {
					if (!validateCustomerID(lt[0], "readFile")) {
						cout << "Error: This customer with the ID: " << lt[0] << " don't have the correct value in 'ID' at line " << lp << "\nThe customer will not be added to the record.Recheck the database file." << endl;
						break;
					}

					if (!validateCustomerName(lt[1], "readFile")) {
						cout << "Error: This customer with the ID: " << lt[0] << " don't have the correct value in 'Name' at line " << lp << "\nThe customer will not be added to the record.Recheck the database file." << endl;
						break;

					}

					if (!validateCustomerAddress(lt[2], "readFile")) {
						cout << "Error: This customer with the ID: " << lt[0] << " don't have the correct value in 'Address' at line " << lp << "\nThe customer will not be added to the record.Recheck the database file." << endl;
						break;
					}

					if (!validateCustomerPhoneNumber(lt[3], "readFile")) {
						cout << "Error: This customer with the ID: " << lt[0] << " don't have the correct value in 'Phone Number' at line " << lp << "\nThe customer will not be added to the record.Recheck the database file." << endl;
						break;
					}

					if (!validateCustomerNumberOfRental(lt[4], "readFile")) {
						cout << "Error: This customer with the ID: " << lt[0] << " don't have the correct value in 'Number of rental' at line " << lp << "\nThe customer will not be added to the record.Recheck the database file." << endl;
						break;
					}

					if (!validateCustomerType(lt[5], "readFile")) {
						cout << "Error: This customer with the ID: " << lt[0] << " don't have the correct value in 'Type' at line " << lp << "\nThe customer will not be added to the record.Recheck the database file." << endl;
						break;
					}
					// Finish validating customer information format

					// If passing all the validation, a customer object will be created and add to the customer list in the program
					if (lt[5] == "Guest") {
						obj = new GuestMember(lt[0], lt[1], lt[2], lt[3], stoi(lt[4]));
					}
					else if (lt[5] == "Regular") {
						obj = new RegularMember(lt[0], lt[1], lt[2], lt[3], stoi(lt[4]));
					}
					else {
						obj = new VipMember(lt[0], lt[1], lt[2], lt[3], stoi(lt[4]));
					}
					l = obj->getRentalList1(); // Get list of the current customer
					CL.addCustomer(obj); // Add customer to the customer list in program
					break;
				} while (true);
			}

			else if (a[0] == 'I') {
				if (obj != NULL) {
					if (cn != obj->getNumberOfRental()) {
						l->addItem(a);
						cn++;
					}
					// If rental number not match (number of rental is lower than the list of rentals)
					else {
						cout << "Error: Customer with ID " << obj->getId() << " have matching number different from the list of rentals." << endl;
						cout << "WARNING: Only " << obj->getNumberOfRental() << " items were recorded during running program " << "for customer with the Id " << obj->getId() << endl;
						cout << "Check the database files please" << endl;
					}
				}
				// Only add the item to customer'rental list up to his/her number of rental.

			}

		}
		myfile.close();
	}
}
