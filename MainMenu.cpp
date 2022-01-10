#include <iostream>
#include <string>
#include <fstream>

#include "MainMenu.h"
#include "InputValidation.h"
#include "ItemMenu.h"
#include "LinkedListItem.h"
#include "CustomerMenu.h"
#include "LinkedListCustomer.h"
#include "RegularMember.h"
#include "VipMember.h"


using namespace std;

//Print Customer By Type Function
void printByType(LinkedListCustomer cust_list) {
	LinkedListCustomer guest_list, vip_list, regular_list;
	CustomerNode* temporary;
	temporary = cust_list.getHead();
	//Create a loop and set condition if found the customers with the same customer's type
	for (; temporary != NULL;) {
		if (temporary->data->getType() == "Guest") {
			guest_list.addCustomer(temporary->data);
		}
		else if (temporary->data->getType() == "Regular") {
			regular_list.addCustomer(temporary->data);
		}
		else if (temporary->data->getType() == "VIP") {
			vip_list.addCustomer(temporary->data);
		}
		temporary = temporary->next;
	}
	cout << "******************** Guest Customer *********************" << endl;
	guest_list.printAllCustomer();

	cout << "******************** Regular Customer *********************" << endl;
	regular_list.printAllCustomer();

	cout << "******************** VIP Customer ********************" << endl;
	vip_list.printAllCustomer();

}

//Main Menu Function
void mainMenu(LinkedListItem& item_list, LinkedListCustomer& cust_list, string item_file_name, string cust_file_name) {

	do {

		string choice;

		cout << "****************** Welcome to Genie's video store ******************" << endl;
		cout << "* 1. Add a new item, update or delete an existing item.            *" << endl;
		cout << "* 2. Add a new customer, update or delete an existing customer.    *" << endl;
		cout << "* 3. Promote an existing customer.                                 *" << endl;
		cout << "* 4. Rent an item.                                                 *" << endl;
		cout << "* 5. Return an item.                                               *" << endl;
		cout << "* 6. Display all items.                                            *" << endl;
		cout << "* 7. Display out-of-stock items.                                   *" << endl;
		cout << "* 8. Display all customers.                                        *" << endl;
		cout << "* 9. Display group of customers.                                   *" << endl;
		cout << "* 10. Exit the program                                             *" << endl;
		cout << "********************************************************************" << endl;

		cout << "Please, select an option: ";
		cin >> choice;

		if (choice == "1") {
			itemMenu(item_list, cust_list, item_file_name, cust_file_name);
		}
		else if (choice == "2") {
			customerMenu(item_list, cust_list, item_file_name, cust_file_name);
		}
		else if (choice == "3") {

			cout << "*************** Promote a customer ***************" << endl;
			cout << "* 1. Promote Customer By ID                      *" << endl;
			cout << "* 2. Promote Customer By name                    *" << endl;
			cout << "* 3. Return To Main Menu                         *" << endl;
			cout << "**************************************************" << endl;

			cout << "Please, choose an option:  ";
			cin >> choice;

			CustomerNode* cust_found;

			if (choice == "1") {
				// Find the customer by ID. Implement find by name later
				do {
					cout << "WARNING: Enter customer's ID: ";
					cin >> choice;
					if (validateCustomerID(choice, "choice"))
						break;
				} while (true);
				cust_found = cust_list.searchCustomerByID(choice);
			}
			else if (choice == "2") {
				cin.ignore();
				do {
					cout << "Please Enter the customer's name: ";
					getline(cin, choice);
					if (validateCustomerName(choice, "choice"))
						break;
				} while (true);
				LinkedListCustomer l_found = cust_list.searchCustomerByName(choice);
				if (l_found.getHead() != NULL) {
					//Case 1: Multiple Customers with the same matching name
					if (l_found.getHead()->next != NULL) {
						l_found.printAllCustomer();
						do {
							//Ask for enter the customer's ID
							cout << "WARNING: Found more than 1 customers with matching names.\n WARNING: Please, enter the customer ID to proceed: ";
							cin >> choice; // Get the customer ID
							if (validateCustomerID(choice, "choice")) {
								break;
							}
						} while (true);

					}
					else {
						// Case 2: Only 1 customer with that name
						choice = l_found.getHead()->data->getId(); // Get the customer ID
					}

					cust_found = l_found.searchCustomerByID(choice);
				}
				else {
					cout << "ERROR: Invalid Customer." << endl;
				}
			}

			if (cust_found != NULL) {
				if (cust_found->data->getType() != "VIP") {
					// Check the condition
					if (cust_found->data->getNumberOfReturnedItems() >= 3) {
						// Store object data to keep for promotion
						string  Id = cust_found->data->getId(), Name = cust_found->data->getName(), Address = cust_found->data->getAddress(), PhNo = cust_found->data->getPhoneNumber();
						int number_of_rental = cust_found->data->getNumberOfRental();
						LinkedListRental* temp_rental = cust_found->data->getRentalList1();

						// Check the customer current type
						if (cust_found->data->getType() == "Guest") {
							delete cust_found->data; // Delete old object in heap
							cust_found->data = new RegularMember(Id, Name, Address, PhNo, number_of_rental);
							cust_found->data->setRentalList(*temp_rental);
							cout << "CONGRATULATIONS!!! " << cust_found->data->getName() << " has been promoted to Regular member." << endl;
						}
						else {
							delete cust_found->data; // Delete old object in heap
							cust_found->data = new VipMember(Id, Name, Address, PhNo, number_of_rental);
							cust_found->data->setRentalList(*temp_rental);
							cout << "CONGRATULATIONS!!! " << cust_found->data->getName() << " has been promoted to VIP member." << endl;
						}
					}
					else {
						cout << "UNSUCCESSED!!! Customer has not met the conditions" << endl;
					}
				}
				else {
					cout << "UNSUCCESSED!!! Customer has already been a VIP member" << endl;
				}
			}
			else {
				cout << "ERROR: Invalid Customer." << endl;
			}
		}

		else if (choice == "4") {
			cout << "******************* Rent Item ********************" << endl;
			cout << "* 1. Rent Item By ID                             *" << endl;
			cout << "* 2. Rent Item By Name                           *" << endl;
			cout << "* 3. Return To Main Menu                         *" << endl;
			cout << "**************************************************" << endl;
			cout << "WARNING: Search the customer that wants to rent an item." << endl;
			cout << "Please Enter an option: ";

			cin >> choice;
			cout << endl;
			cout << "**************************************************" << endl;
			string k; //Item ID
			string i_c; // Customer ID

			CustomerNode* cust_found;

			if (choice == "1" || choice == "2") {
				//Search customer by ID
				if (choice == "1") {
					cout << "Please enter the customer's ID: ";
					cin.ignore();

					getline(cin, i_c);

					cust_found = cust_list.searchCustomerByID(i_c);
				}
				//Search customer by name
				else if (choice == "2") {
					cin.ignore();
					do {
						cout << "Please enter the customer's name: ";
						getline(cin, choice);
						// Check title format
						if (validateCustomerName(choice, "choice"))
							break;
					} while (true);
					// Find item through the list here
					LinkedListCustomer l_found = cust_list.searchCustomerByName(choice);
					if (l_found.getHead() != NULL) {
						// Case 1: Multiple customers with the same matching name
						if (l_found.getHead()->next != NULL) {
							l_found.printAllCustomer();
							do {
								cout << "WARNING: Found more than 1 customers with matching names.\nWARNING: Enter customer ID to proceed: ";
								cin >> choice; // Get the customer ID
								if (validateCustomerID(choice, "choice")) {
									break;
								}
							} while (true);

						}
						else {
							// Case 2: Only 01 Customer with that name
							choice = l_found.getHead()->data->getId(); // Get the customer ID
						}

						cust_found = cust_list.searchCustomerByID(choice);

					}
				}

				if (cust_found != NULL) {
					cust_found->data->details(); // Show customer details

					cout << "******************* Rent Item ********************" << endl;
					cout << "* Rent an item                                   |" << endl;
					cout << "* 1. Rent an Item By ID                          |" << endl;
					cout << "* 2. Rent an Item By title                       |" << endl;
					cout << "**************************************************" << endl;
					cout << "Please Choose an option: ";

					cin >> choice;
					// Find item by ID

					if (choice == "1" || choice == "2") {

						if (choice == "1") {
							do {
								cout << "Please Enter the item's ID: ";
								cin >> k;
								// Check title format
								if (validateItemID(k, "choice"))
									break;
							} while (true);

						}
						else if (choice == "2") {
							cin.ignore();
							do {
								cout << "Please Enter the item's title: ";
								getline(cin, k);
								// Check title format
								if (validateTitle(k, "choice"))
									break;
							} while (true);

							LinkedListItem l_found = item_list.searchItemByTitle(k);

							if (l_found.getHead() != NULL) {
								// Case 1: Multiple items with the same matching titles
								if (l_found.getHead()->next != NULL) {
									l_found.printItem();
									do {
										cout << "WARNING: Found more than 1 items with matching titles.\n Please Enter item's ID to proceed: ";

										cin >> k; // Get the item ID
										if (validateItemID(k, "choice")) {
											break;
										}
									} while (true);

								}
								else {
									// Case 2: Found only 1 item with matching title
									k = l_found.getHead()->data->getId(); // Get the item ID
								}

							}
						}

						ItemElement* item = item_list.searchItemByID(k);
						if (item != NULL) {
							int isAvailable = item->data->getNumberOfCopies();
							if (isAvailable != 0) {
								cust_found->data->rentItem(item->data->getId(), item_list);
							}
							else {
								cout << "UNSUCCESSED: " << item->data->getTitle() << " is unavailable." << endl;
							}
						}
						else {
							cout << "ERROR: Item not found." << endl;
						}
					}
					else {
						cout << "ERROR: Invalid choice." << endl;
					}
				}
				else {
					cout << "ERROR: Invalid Customer." << endl;
				}
			}
			// Back to main menu
			else if (choice == "3") {

			}
			else {
				cout << "ERROR: Invalid choice. Please try again." << endl;
			}
		}
		else if (choice == "5") {
			cout << "****************** Return items *******************" << endl;
			cout << "* 1. Return Item By ID                            *" << endl;
			cout << "* 2. Return Item By name                          *" << endl;
			cout << "* 3. Back to Main Menu                            *" << endl;
			cout << "***************************************************" << endl;

			cout << "Search the customer that wants to return an item. Please Enter an option : ";

			cin >> choice;
			string k;
			string i_c;

			// Search customer by id

			if (choice == "1") {
				cout << "Please enter the customer's ID: ";
				cin.ignore();
				getline(cin, i_c);
				CustomerNode* cust_found = cust_list.searchCustomerByID(i_c);
				if (cust_found != NULL) {
					cout << "******************* Return Item ********************" << endl;
					cust_found->data->details();
					cout << "****************************************************" << endl;
					cout << "Please enter the item's ID: ";

					getline(cin, k);

					bool isValidateItem = validateItemID(k, "choice");
					if (isValidateItem) {
						bool isHaveThisId = cust_found->data->getRentalList1()->isListHaveId(k);
						if (isHaveThisId) {
							ItemElement* item = item_list.searchItemByID(k);
							item->data->returning();
							cust_found->data->returnItem(k);
						}
						else {
							cout << "ERROR: Item's ID is not in " << cust_found->data->getName() << " rental list" << endl;
						}
					}
				}
				else {
					cout << "ERROR: Invalid Customer." << endl;
				}
			}
			// Search customer by name
			else if (choice == "2") {

				cin.ignore();
				do {
					cout << "Please enter the customer's name: ";
					getline(cin, choice);
					// Check title format
					if (validateCustomerName(choice, "choice"))
						break;
				} while (true);
				// Find item through the list here
				LinkedListCustomer l_found = cust_list.searchCustomerByName(choice);

				if (l_found.getHead() != NULL) {

					if (l_found.getHead()->next != NULL) {
						l_found.printAllCustomer();
						do {
							cout << "WARNING: Found more than 1 customers with matching names.\n WARNING: Please Enter the customer's ID to proceed: ";
							cin >> choice; // Get the customer ID
							if (validateCustomerID(choice, "choice")) {
								break;
							}
						} while (true);

					}
					else {
						// Case 2: Only 1 customer with matching name.
						choice = l_found.getHead()->data->getId(); // Get the customer ID
					}

					CustomerNode* cust_found = cust_list.searchCustomerByID(choice);
					if (cust_found != NULL) {
						cout << "******************* Return Item ********************" << endl;
						cust_found->data->details();
						cout << "****************************************************" << endl;
						cout << "Please enter the returning item's ID: ";

						getline(cin, k);

						bool isValidateItem = validateItemID(k, "choice");
						if (isValidateItem) {
							bool isHaveThisId = cust_found->data->getRentalList1()->isListHaveId(k);
							if (isHaveThisId) {
								ItemElement* item = item_list.searchItemByID(k);
								item->data->returning();
								cust_found->data->returnItem(k);
							}
							else {
								cout << "ERROR: Item's ID cannot be found in " << cust_found->data->getName() << " rental list" << endl;
							}
						}
					}
					else {
						cout << "ERROR: Invalid Customer." << endl;
					}
				}

			}
			else if (choice == "3") {

			}
			else {
				cout << "ERROR: Invalid choice. Please enter again." << endl;
			}
		}
		else if (choice == "6") {
			cout << "***************** Display all items ****************" << endl;
			cout << "* Display All Items                                *" << endl;
			cout << "* 1. Display all item by ID                        *" << endl;
			cout << "* 2. Display all item by Title                     *" << endl;
			cout << "****************************************************" << endl;

			cout << "Please Choose an option: ";
			cin >> choice;

			if (choice == "1") {
				LinkedListItem tempItemList(item_list);
				tempItemList.sortedByID();
				tempItemList.printItem();
			}
			else if (choice == "2") {
				LinkedListItem tempItemList(item_list);
				tempItemList.sortedByTitle();
				tempItemList.printItem();
			}
			else {
				cout << "ERROR: Invalid choice." << endl;
			}
		}
		else if (choice == "7") {
			// Display out of stock
			cout << "*************** Out of stock items ****************" << endl;
			item_list.printOutOfStockItem();

			cout << "***************************************************" << endl;
		}
		else if (choice == "8") {
			cout << "**************** Display all customers ****************" << endl;
			cout << "| 1. Display all customer by ID                       |" << endl;
			cout << "| 2. Display all customer by Name                     |" << endl;
			cout << "*******************************************************" << endl;

			cout << "Please Choose an option : ";
			cin >> choice;

			if (choice == "1") {
				LinkedListCustomer tempCustomerList(cust_list);
				tempCustomerList.sortedByID();
				tempCustomerList.printAllCustomer();
			}
			else if (choice == "2") {
				LinkedListCustomer tempCustomerList(cust_list);
				tempCustomerList.sortedByName();
				tempCustomerList.printAllCustomer();
			}
			else {
				cout << "ERROR: Invalid choice." << endl;
			}
		}
		//Display Group Of Customer
		else if (choice == "9") {
			printByType(cust_list);
		}

		//Exit the program
		else if (choice == "Exit" || choice == "10") {
			closeProgram(item_list, cust_list, item_file_name, cust_file_name);
		}

		else {
			cout << "WARNING: Invalid choice" << endl;
		}

	} while (true);
}

void closeProgram(LinkedListItem& item_list, LinkedListCustomer& cust_list, string item_file_name, string cust_file_name) {
	// Save file
	ofstream itemFile;
	ofstream customerFile;

	itemFile.open(item_file_name);
	customerFile.open(cust_file_name);


	if (itemFile.fail() || customerFile.fail()) {
		cout << "Could not open file" << endl;
		return;
	}

	ItemElement* i_elm = item_list.getHead();
	CustomerNode* cust_node = cust_list.getHead();
	while (i_elm != NULL) {
		itemFile << i_elm->data->getId() << ",";
		itemFile << i_elm->data->getTitle() << ",";
		itemFile << i_elm->data->getRentalType() << ",";
		itemFile << i_elm->data->getLoanType() << ",";
		itemFile << i_elm->data->getNumberOfCopies() << ",";
		itemFile << i_elm->data->getRentalFee();
		if (i_elm->data->getRentalType() != "Game") {
			itemFile << "," << i_elm->data->getGenre();
		}
		itemFile << endl;
		delete i_elm->data;
		i_elm = i_elm->next;
	}

	while (cust_node != NULL) {
		customerFile << cust_node->data->getId() << ",";
		customerFile << cust_node->data->getName() << ",";
		customerFile << cust_node->data->getAddress() << ",";
		customerFile << cust_node->data->getPhoneNumber() << ",";
		customerFile << cust_node->data->getNumberOfRental() << ",";
		customerFile << cust_node->data->getType();
		LinkedListRental* rentalList = cust_node->data->getRentalList1();
		RentalListNode* item = rentalList->getHead();

		while (item != NULL) {
			customerFile << endl;
			customerFile << item->getItem();
			item = item->getNext();
		}

		// If not a last element then add new line so if it is a last element, we will not at new empty line to the file
		if (cust_node->next != NULL) {
			customerFile << endl;
		}
		delete cust_node->data;
		cust_node = cust_node->next;
	}
	customerFile.close();

	itemFile.close();

	// Display group information
	cout << "******************* Group Information *******************" << endl;
	cout << "*                                                       *" << endl;
	cout << "*               ASSIGNMENT 2 - GROUP 18                 *" << endl;
	cout << "*                                                       *" << endl;
	cout << "*      s3699000, s3699000@rmit.edu.vn, An, Tran         *" << endl;
	cout << "*      s3795683, s3795683@rmit.edu.vn, Anh, Tran        *" << endl;
	cout << "*      s3741280, s3741280@rmit.edu.vn, Duong, Nguyen    *" << endl;
	cout << "*      s3705122, s3705122@rmit.edu.vn, Vu, Pham         *" << endl;
	cout << "*                                                       *" << endl;
	cout << "*********************************************************" << endl;

	// Stop the program
	cout << "Closing the program..." << endl;
	exit(0);

}
