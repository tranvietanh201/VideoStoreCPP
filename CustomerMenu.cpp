#include "CustomerMenu.h"
#include "GuestMember.h"
#include "RegularMember.h"
#include "VipMember.h"
#include "InputValidation.h"
#include "Utilities.h"


void customerMenu(LinkedListItem&i_list, LinkedListCustomer&cust_list, string i_file_name, string cust_file_name) {

	 do{
		cout << "*--------------------- Customer Menu --------------------*" << endl;
		cout << "| 1. Add a new customer                                  |" << endl;
		cout << "| 2. Delete a customer                                   |" << endl;
		cout << "| 3. Update a customer                                   |" << endl;
		cout << "| 4. Search a customer                                   |" << endl;
		cout << "| 5. Back to main menu                                   |" << endl;
		cout << "| Exit.                                                  |" << endl;
		cout << "----------------------------------------------------------" << endl;
		cout << "Please Choose an option: ";
		string choice;
		cin >> choice;

		// Add a new customer menu
		if (choice == "1") {
			cout << "*------------------ Add a new customer -------------------*" << endl;
			Customer *c = customerCreateMenu(cust_list);
			cout << "*--------------------------------------------------------*" << endl;
			cout << "*------------------ Add a new customer ------------------*" << endl;
			c->details();
			cout << "*--------------------------------------------------------*" << endl;
			cout << "WARNING: Customer will be added to database. Type 'yes' to confirm: ";
			cin >> choice;
			if (choice == "yes") {
				cust_list.addCustomer(c);
				cout << "SUCCESS: Customer is added." << endl;
			}
			else {
				cout << "FAIL: No customer is added." << endl;
			}
		}

		// Delete customer menu
		else if (choice == "2") {
			do {
				cout << "*------------------- Delete Customer -------------------*" << endl;
				cout << "|1. Delete Customer By ID                               |" << endl;
				cout << "|2. Delete Customer By name                             |" << endl;
				cout << "|3. Back To Customer Menu                               |" << endl;
				cout << "*-------------------------------------------------------*" << endl;
				cout << "Please Enter an option: ";
				cin >> choice;

				if (choice == "1") {
					do {
						cout << "Please: Enter customer's ID to delete: ";
						cin >> choice;
						// Check ID format
						if (validateCustomerID(choice, "choice"))
							break;
					}while (true);
					// Find item through the list here
					CustomerNode *cust_found = cust_list.searchCustomerByID(choice);
					// If-else case: If item found, show item's detail. If item not found, print error message then back to item menu.
					if (cust_found != NULL) {
                        cout << "*------------------------------------*" << endl;
					    cust_found->data->details();
                        cout << "*------------------------------------*" << endl;

                        // Not allow to delete if customer still have rent item
                        if (cust_found->data->getNumberOfRental() != 0) {
                            cout << "WARNING: Customer must return all the items before being deleted" << endl;
                        }

                        else {
                            // Delete is a dangerous action. So the program make it harder to delete an item. Just like Github.
                            cout
                                    << "WARNING: Do you really want to delete the customer ? Type 'yes' to confirm action: ";
                            cin >> choice;
                            if (choice == "yes" || choice == "Yes") {
                                cust_list.deleteCustomer(cust_found->data->getId());
                                cout << "SUCCESS: Customer has been deleted." << endl;
                            } else
                                cout << "FAIL: No deletion has taken place. Return to item menu." << endl;
                        }
					}
					else {
						cout << "ERROR: INVALID Customer." << endl;
					}
				}
				else if (choice == "2") {
				    cin.ignore();
					do {
						cout << "Please Enter customer's name to delete: ";
						getline(cin, choice);
						// Check title format
						if (validateCustomerName(choice, "choice"))
							break;
					}while (true);
					// Find item through the list here
					LinkedListCustomer list_found = cust_list.searchCustomerByName(choice);
					// If-else case: If item found, show item's detail. If item not found, print error message then back to item menu.
                    if (list_found.getHead() != NULL) {
                        // Case 1: Found more than 1 customer with matching name
                        if (list_found.getHead()->next != NULL) {
                            list_found.printAllCustomer();
                            do {
                                cout << "WARNING: Found more than 1 customers with matching names.\n Please Enter customer ID to proceed: ";
                                cin >> choice; // Get the customer ID
                                if (validateCustomerID(choice, "choice")) {
                                    break;
                                }
                            }while (true);

                        }
                        else {
                            // Case 2: Found only 1 customer with matching name. The choice will be customer ID in the Head of the list.
                            choice = list_found.getHead()->data->getId(); // Get the customer ID
                        }

                        CustomerNode *cust_found = cust_list.searchCustomerByID(choice);

                        if (cust_found != NULL) {
                            cust_found->data->details();

                            if (cust_found->data->getNumberOfRental() != 0) {
                                cout << "ERROR: Customer must return all the items" << endl;
                            }
                            else {
                                // Delete is a dangerous action. So the program make it harder to delete an item. Just like Github.
                                cout << "WARNING: Do you really want to delete the customer ? Type 'yes' to confirm action: ";
                                cin >> choice;
                                if (choice == "yes" || choice == "Yes") {
                                    cust_list.deleteCustomer(cust_found->data->getId());
                                    cout << "SUCCESS: Customer has been deleted." << endl;
                                }
                                else
                                    cout << "FAIL: No deletion has taken place. Return to item menu." << endl;
                            }
                        }
                        else {
                            cout << "ERROR: INVALID Customer." << endl;
                        }

                    }
					else {
                        cout << "ERROR: INVALID Customer." << endl;
					}
				}
				else if (choice == "3") {
					break;
				}
				else {
					cout << "ERROR: Invalid choice. Please try again." << endl;
				}
			}while (true);

		}

		// Update customer menu
		else if (choice == "3") {

			while (true) {
				cout << "*-------------------- Update Customer --------------------*" << endl;
				cout << "|1. Update Customer By ID                                 |" << endl;
				cout << "|2. Update Customer By name                               |" << endl;
				cout << "|3. Back to Customer Menu                                 |" << endl;
				cout << "*---------------------------------------------------------*" << endl;
				cout << "Please Enter an option: ";
				cin >> choice;

				if (choice == "1") {
					cin.ignore();
					do {
						cout << "Please Enter customer's ID to update: ";
						getline(cin, choice);
						if (validateCustomerID(choice, "choice"))
							break;
					}while (true);
					// Find item through the list here
					CustomerNode *custm = cust_list.searchCustomerByID(choice);
					// If-else case: If item found, show item's detail. If item not found, print error message then back to item menu.
					//
					if (custm != NULL) {
							// Call update function
							customerUpdateMenu(custm);
					}
					else {
						// Will implement choice id again
						cout << "ERROR: INVALID Customer." << endl;
					}
				}
				else if (choice == "2") {
					cin.ignore();
					do {
						cout << "Please Enter customer's name to update: ";
						getline(cin, choice);
						if (validateCustomerName(choice, "choice"))
							break;
					}while (true);
					// Find item through the list here
					LinkedListCustomer list_found = cust_list.searchCustomerByName(choice);
					// If-else case: If customer found, show customer's detail. If customer not found, print error message then back to customer menu.
					//
					if (list_found.getHead() != NULL) {
						// Case 1: Found more than 1 customer with matching name
						if (list_found.getHead()->next != NULL) {
							list_found.printAllCustomer();
							do {
								cout << "WARNING: Found more than 1 customers with matching names.\nEnter customer ID to proceed: ";
								cin >> choice; // Get the customer ID
								if (validateCustomerID(choice, "choice")) {
									break;
								}
							}while (true);

						}
						else {
							// Case 2: Found only 1 customer with matching name. The choice will be customer ID in the Head of the list.
							choice = list_found.getHead()->data->getId(); // Get the customer ID
						}

						CustomerNode *custm = cust_list.searchCustomerByID(choice);

						if (custm != NULL) {
								// Call update function
								customerUpdateMenu(custm);

						}
						else {
							cout << "ERROR: INVALID Customer." << endl;
						}

					}
					else {
						cout << "ERROR: INVALID Customer." << endl;
					}
				}
				else if (choice == "3") {
					break;
				}
				else {
					cout << "ERROR: Invalid choice. Please try again." << endl;
				}
			}

		}

		// Search customer 
		else if (choice == "4") {
			// User decide to leave the menu through a while loop
			do {
				cout << "*                    Search a customer                    *" << endl;
				cout << "|1. Search a Customer By ID                               |" << endl;
				cout << "|2. Search a Customer By name                             |" << endl;
				cout << "|3. Back to Customer Menu                                 |" << endl;
				cout << "*                                                         *" << endl;
				cout << "Please Enter an option: ";
				cin >> choice;
				if (choice == "1") {
					do{
						cout << "Enter customer's ID: ";
						cin >> choice;
						if (validateCustomerID(choice, "choice"))
							break;
					}while (true);
					// Find item through the list here

					CustomerNode *obj = cust_list.searchCustomerByID(choice);
					if (obj != NULL) {
						obj->data->details();
					}
					else {
						cout << "Customer ID not found" << endl;
					}
				}
				else if (choice == "2") {
					cin.ignore();
					do {
						cout << "Enter customer's name: ";
						getline(cin, choice);
						if (validateCustomerName(choice, "choice"))
							break;
					}while (true);
					// Parse customer list
					LinkedListCustomer list_found = cust_list.searchCustomerByName(choice);
					if (list_found.getHead() != NULL)
						list_found.printAllCustomer();
					else
						cout << "Customer name not found" << endl;
				}
				else if (choice == "3") {
					break;
				}
				else {
					cout << "ERROR: Invalid choice." << endl;
				}
				cout << "Please confirm search information (Type y/n): ";
				cin >> choice;
				if (choice == "y") {
					cout << endl;
					// update
				}
				else {
					cout << "*---------------------------------------------------------*" << endl;
					cout << endl; //
					// Exit the loop
					break;
				}
			}while (true);

		}


		// Back to main menu
		else if (choice == "5") {
			break;
		}

		// Close program
		else if (choice == "Exit") {
			closeProgram(i_list, cust_list, i_file_name, cust_file_name);
		}
		else {
			cout << "Invalid choice. Please try again." << endl;
		}
	}while (true);

}

Customer *customerCreateMenu(LinkedListCustomer&cust_list) {
	string *inp_array = new string[5];

	// Validate customer
	do {
		cout << "1. Enter customer's ID(Cxxx): ";
		cin >> inp_array[0];

		// Format validation
		if (validateCustomerID(inp_array[0], "choice")) {
			// ID validation
			CustomerNode *duplicateID = cust_list.searchCustomerByID(inp_array[0]);
			if (duplicateID != NULL) {
				cout << "Customer's ID collision. Please type another ID" << endl;
			}
			else {
				break;
			}
		}

	}while (true);

	cin.ignore();
	// Validate user's choice 
	 do{
		cout << "2. Enter customer's name: ";
		getline(cin, inp_array[1]);
		if (validateCustomerName(inp_array[1],"choice"))
			break;
	}while (true);
	// Validate user's choice
	do{
		cout << "3. Enter customer's address: ";
		getline(cin, inp_array[2]);
		if (validateCustomerAddress(inp_array[2],"choice"))
			break;
	}while (true);

	// Validate user's choice
	do{
		cout << "4. Enter customer's phone number (10 digits): ";
		// Validation
		cin >> inp_array[3];
		if (validateCustomerPhoneNumber(inp_array[3],"choice"))
			break;
	}while (true);

	// Validate user's choice
	do {
		cout << "5. Enter customer's type (Guest, Regular, VIP): ";
		cin >> inp_array[4];
		if (validateCustomerType(inp_array[4],"choice"))
			break;
	}while (true);

	Customer *obj;

	// Create customer object with each customer type.
	if (inp_array[4] == "Guest") {
		obj= new GuestMember(inp_array[0], inp_array[1], inp_array[2], inp_array[3], 0);
	}
	else if (inp_array[4] == "Regular") {
		obj = new RegularMember(inp_array[0], inp_array[1], inp_array[2], inp_array[3], 0);
	}
	else {
		obj = new VipMember(inp_array[0], inp_array[1], inp_array[2], inp_array[3], 0);
	}
	// Free up space
	delete[] inp_array;
	return obj;
}

void customerUpdateMenu(CustomerNode *custm) {
	string choice;

	do {
		cout << "*                      Update Customer                       *" << endl;
		custm->data->details();
		cout << "Please choose an option: ";
		cin >> choice;

		if (choice == "1") {
			cin.ignore();
			do{
				cout << "Enter customer's name: ";
				// getline since name contains spaces
				getline(cin, choice);
				if (validateCustomerName(choice, "choice")) {
					custm->data->setName(choice);
					break;
				}
			}while (true);
		}
		else if (choice == "2") {
			cin.ignore();
			do {
				cout << "Enter customer's address: ";
				// getline since address contains spaces
				getline(cin, choice);
				if (validateCustomerAddress(choice, "choice")) {
					custm->data->setAddress(choice);
					break;
				}
			}while (true);
		}
		else if (choice == "3") {
			do {
				cout << "Enter customer's phone number (10 digits): ";
				cin >> choice;
				if (validateCustomerPhoneNumber(choice, "choice")) {
					custm->data->setPhoneNumber(choice);
					break;
				}
			}
while (true);
		}
		else {
			cout << "ERROR: Invalid choice. Please try again." << endl;
		}
		cout << "PROMPT: Continue to update? (y/n): ";
		cin >> choice;
		if (choice == "y") {
			// Continue to update
		}
		else {
			// Break out the update loop
			break;
		}
	}while (true);
	return;
}
