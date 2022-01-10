#include "ItemMenu.h"
#include "Item.h"
#include <iostream>

#include "InputValidation.h"
#include "MainMenu.h"
#include <string>
#include "LinkedListItem.h"

using namespace std;


void itemMenu(LinkedListItem& i_list, LinkedListCustomer& cust_list, string i_file_name, string cust_file_name) {

	do {
		cout << "************************ Item Menu ***********************" << endl;
		cout << "* 1. Add a new item.                                     *" << endl;
		cout << "* 2. Delete an item.                                     *" << endl;
		cout << "* 3. Update an item.                                     *" << endl;
		cout << "* 4. Increase item's stock.                              *" << endl;
		cout << "* 5. Show all item in stock.                             *" << endl;
		cout << "* 6. Search an item.                                     *" << endl;
		cout << "* 7. Back to main menu.                                  *" << endl;
		cout << "**********************************************************" << endl;
		cout << "Choose an option: ";

		string choice;
		cin >> choice;

		//Case 1: Add a new item
		if (choice == "1") {
			// Create a new item
			cout << "********************* Add a new item *********************" << endl;
			Item* new_item = itemCreateMenu(i_list);
			cout << "**********************************************************" << endl;
			// Insert item into linked list here
			cout << "*                     Adding a new item" << endl;
			cout << "* Item " << new_item->getId() << endl;
			cout << "* 1. Title: " << new_item->getTitle() << endl;
			cout << "* 2. Type: " << new_item->getRentalType() << endl;
			cout << "* 3. Loan's type: " << new_item->getLoanType() << endl;
			cout << "* 4. Number of copies: " << new_item->getNumberOfCopies() << endl;
			cout << "* 5. Rental fee: " << new_item->getRentalFee() << endl;
			if (new_item->getGenre() != "") {
				cout << "* 6. Genre: " << new_item->getGenre() << endl;
			}
			cout << "**********************************************************" << endl;

			cout << "WARNING: This item will be added to the database. Please type 'yes' to confirm: ";
			cin >> choice;
			if (choice == "yes" || choice == "Yes") {
				i_list.addItem(new_item);
				cout << "SUCCESS!!!: Item added." << endl;
			}
			else {
				cout << "FAIL!!!: No item added." << endl;
			}
			cout << "**********************************************************" << endl;
			cout << endl; 
		}

		//Case 2: Delete an Item
		else if (choice == "2") {
			do {
				cout << "********************** Delete Item ***********************" << endl;
				cout << "* 1. Delete Item By ID                                   *" << endl;
				cout << "* 2. Delete Item By title                                *" << endl;
				cout << "* 3. Back to Item Menu                                   *" << endl;
				cout << "**********************************************************" << endl;
				cout << "Enter an option: ";
				cin >> choice;

				//Case 2.1: Delete item by ID
				if (choice == "1") {
					do {
						cout << "Enter the item's ID want to delete: ";
						cin >> choice;

						//Validate Item's ID input
						if (validateItemID(choice, "choice"))
							break;
					} while (true);

					//Check if the item is in the list
					ItemElement* item_found = i_list.searchItemByID(choice);

					CustomerNode* cust_renting = cust_list.getHead();

					//If the item is found, Display the item's details. Otherwise, print an error message
					//Then return to Item menu
					if (item_found != NULL) {
						item_found->data->printDetail();

						//Set a count variable in order to count the number of items which are being rented
						int counter = 0;

						for (; cust_renting != NULL;) {

							LinkedListRental* temp_r_list = cust_renting->data->getRentalList1();
							RentalListNode* tmp_rent_itm = temp_r_list->getHead();

							while (tmp_rent_itm != NULL) {

								if (tmp_rent_itm->getItem() == item_found->data->getId()) {

									//Check if the Item is being rented or not at the moment
									if (counter == 0) {
										cout << "FAIL!!!: Item is currently rent by: " << cust_renting->data->getName();
									}
									else {
										cout << ", " << cust_renting->data->getName();
									}
									counter++;
									break;
								}
								tmp_rent_itm = tmp_rent_itm->getNext();
							}
							cust_renting = cust_renting->next;
						}
						cout << endl;
						//If the item is not rented by any customer, start deleting
						if (counter == 0) {
							cout << "WARNING: Do you really want to delete the item ? Type 'yes' to confirm action: ";
							cin >> choice;
							if (choice == "yes" || choice == "Yes") {
								i_list.deleteItem(item_found->data->getId());
								cout << "SUCCESS!!!: Item has been deleted." << endl;
							}
							else
								cout << "FAIL!!!: Delete Failed. Returning to item menu." << endl;
						}

						//If the item is rented by an customer, It cannot be deleted -> print error message.
						else {
							cout << "WARNING: The item is rent by customers. Please return the item before start delete process." << endl;
						}
					}
					else {
						cout << "ERROR: INVALID Item." << endl;
					}
				}
				//Case 2.2: Delete Item by Name
				else if (choice == "2") {
					do {
						cout << "WARNING: Enter item's title that you want to delete: ";
						cin >> choice;

						//Validate the Item's title input
						if (validateTitle(choice, "choice"))
							break;
					} while (true);

					//Find the item in the Item's Link List
					LinkedListItem found_list = i_list.searchItemByTitle(choice);

					//If the item is found, Display the item's details. Otherwise, print an error message
					if (found_list.getHead() != NULL) {
						if (found_list.getHead()->next != NULL) {
							found_list.printItem();
							do {
								//In case, multiple customers has the same name, Input the ID to contiue delete process
								cout << "WARNING: Found more than 1 item with matching name.\n Warning: Enter item ID to continue: ";
								cin >> choice; // Input the customer's ID
								if (validateTitle(choice, "choice")) {
									break;
								}
							} while (true);
						}

						else {
							choice = found_list.getHead()->data->getId();
						}

						ItemElement* item_found = found_list.searchItemByID(choice);
						CustomerNode* cust_renting = cust_list.getHead();

						if (item_found != NULL) {
							item_found->data->printDetail();

							//Set a count variable in order to count the number of items which are being rented
							int counter = 0; 

							for (; cust_renting != NULL; cust_renting = cust_renting->next) {

								LinkedListRental* temp_r_list = cust_renting->data->getRentalList1();
								RentalListNode* tmp_rent_itm = temp_r_list->getHead();

								while (tmp_rent_itm != NULL) {
									//Check if the item is being rent by a customer or not
									if (tmp_rent_itm->getItem() == item_found->data->getId()) {
										cout << "FAIL!!!: Item is rent by: " << cust_renting->data->getName() << endl;
										counter++;
									}
									tmp_rent_itm = tmp_rent_itm->getNext();
								}
							}
							//If the item is not rented by any customer, start deleting
							if (counter == 0) {
								cout << "WARNING: Do you really want to delete the item ? Type 'yes' to confirm action: ";
								cin >> choice;
								if (choice == "yes" || choice == "Yes") {
									i_list.deleteItem(item_found->data->getId());
									cout << "SUCCESS!!!: Item has been deleted." << endl;
								}
								else
									cout << "FAIL!!!: Delete Failed. Returning to item menu." << endl;
							}
							//If the item is rented by an customer, It cannot be deleted -> print error message.
							else {
								cout << "WARNING: The item is still being rent by customers. Please return the item before proceed to delete." << endl;
							}
						}
						else {
							cout << "ERROR: INVALID Item." << endl;
						}
					}
					else {
						cout << "ERROR: INVALID Item." << endl;
					}
				}
				//Exit the Delete Menu
				else if (choice == "3") {
					break;
				}
				else {
					cout << "ERROR: Invalid choice. Please try again." << endl;
				}
			} while (true);
		}
		//Case 3: Update Item's Data
		else if (choice == "3") {

			do {
				cout << "********************** Update Item ***********************" << endl;
				cout << "*1. Update Item By ID                                    *" << endl;
				cout << "*2. Update Item By title                                 *" << endl;
				cout << "*3. Back to Item Menu                                    *" << endl;
				cout << "**********************************************************" << endl;
				cout << "Enter an option: ";
				cin >> choice;

				//Case 3.1: Update Item by ID
				if (choice == "1") {
					do {
						cout << "Enter item's ID that you want to update: ";
						cin >> choice;
						//Validate Item's ID input
						if (validateItemID(choice, "choice"))
							break;
					} while (true);

					//Find the item in the Item's Link List
					ItemElement* item = i_list.searchItemByID(choice);

					//If the item is found, Display the item's details. Otherwise, print an error message
					if (item != NULL) {
						do {
							//Update Function is called
							itemUpdateMenu(item);
							item->data->printDetail();
							cout << "WARNING: Continue to update ? (y/n): ";
							cin >> choice;
						} while (true);
					}
					else {
						// Will implement choice id again
						cout << "ERROR: INVALID Item." << endl;
					}
				}
				//Case 3.2: Update Item by Title
				else if (choice == "2") {
					cin.ignore();
					do {
						cout << "Enter item's title that you want to update: ";
						getline(cin, choice);
						if (validateTitle(choice, "choice"))
							break;
					} while (true);

					//Find the item in the Item's Link List
					LinkedListItem found_list = i_list.searchItemByTitle(choice);

					//If the item is found, Display the item's details. Otherwise, print an error message
					if (found_list.getHead() != NULL) {
						//In case, multiple customers has the same name, Input the ID to contiue delete process
						if (found_list.getHead()->next != NULL) {
							found_list.printItem();
							do {
								cout << "WARNING: Found more than 1 item with matching title.\nEnter item ID to proceed: ";
								cin >> choice; // Get the customer ID
								if (validateItemID(choice, "choice")) {
									break;
								}
							} while (true);

						}
						else {
							//Only 1 customer with matching name. The choice will be customer ID in the Head of the list.

							choice = found_list.getHead()->data->getId(); // Get the customer ID
						}

						ItemElement* item = found_list.searchItemByID(choice);

						if (item != NULL) {
							//Update function
							itemUpdateMenu(item);

						}
						else {
							cout << "ERROR: INVALID Item." << endl;
						}

					}
					else {
						cout << "ERROR: INVALID Item." << endl;
					}
				}
				else if (choice == "3") {
					break;
				}
				else {
					cout << "ERROR: Invalid choice. Please try again." << endl;
				}
			} while (true);
		}
		//Case 4: Adding more Stock (Number of copies)
		else if (choice == "4") {

			do {
				cout << "********************** Increase Stock **********************" << endl;
				cout << "* 1. Increase by ID                                        *" << endl;
				cout << "* 2. Increase by title                                     *" << endl;
				cout << "* 3. Back to Item Menu                                     *" << endl;
				cout << "************************************************************" << endl;
				cout << "Enter an option: ";
				cin >> choice;

				if (choice == "1" || choice == "2") {
					if (choice == "1") {
						do {
							cout << "Enter Item's ID you want to Increase Stock: ";
							cin >> choice;
							//Validate Item's ID input
							if (validateItemID(choice, "choice"))
								break;
						} while (true);
						// Find the item through Item's Linked List
					}
					else {

						cin.ignore();
						do {
							cout << "Enter Item's title you want to Incrase Stock: ";
							getline(cin, choice);
							if (validateTitle(choice, "choice"))
								break;
						} while (true);

						// Find the item through Item's Linked List
						LinkedListItem found_list = i_list.searchItemByTitle(choice);
						//In case, multiple item has the same name, Input the ID to contiue delete process
						if (found_list.getHead() != NULL) {
							//Found more than 1 item with matching title
							if (found_list.getHead()->next != NULL) {
								found_list.printItem();
								do {
									cout << "WARNING: Found more than 1 item with matching title.\nEnter item ID to proceed: ";
									cin >> choice; // Get the item ID
									if (validateItemID(choice, "choice")) {
										break;
									}
								} while (true);

							}
							else {
								//Found only 1 item with matching title. The choice will be Item ID in the Head of the list.
								choice = found_list.getHead()->data->getId(); // Get the item ID
							}
						}


					}
					ItemElement* item = i_list.searchItemByID(choice);
					if (item != NULL) {
						do {
							cout << "Enter number of stock arrived:  ";
							cin >> choice;
							if (validateNumberOfCopies(choice, "choice")) {
								item->data->increaseStock(stoi(choice));
								item->data->printDetail();
								cout << "SUCCESS!!!: Item's stock has been increased." << endl;
								break;
							}

						} while (true);
					}
					else {
						cout << "ERROR: INVALID Item." << endl;
					}
				}
				//Return to Item Menu
				else if (choice == "3") {
					break;
				}
				else {
					cout << "ERROR: Invalid choice. Please try again." << endl;
				}

			} while (true);

		}
		//Case 5: Display List of Items
		else if (choice == "5") {
			cout << "******************* List of items ********************" << endl;
			i_list.printItem();
		}

		//Case 6: Seach for an Item
		else if (choice == "6") {

			do {
				cout << "********************* Search an item **********************" << endl;
				cout << "* 1. Search an Item By ID                                 *" << endl;
				cout << "* 2. Search an Item By Title                              *" << endl;
				cout << "* 3. Back to Item Menu                                    *" << endl;
				cout << "***********************************************************" << endl;
				cout << "Enter an option: ";
				cin >> choice;

				//Case 6.1: Search an Item By ID
				if (choice == "1") {
					do {
						cout << "Enter the item's ID you want to search: ";
						cin >> choice;
						if (validateItemID(choice, "choice"))
							break;
					} while (true);

					//Find the Item through the Linked List
					ItemElement* item = i_list.searchItemByID(choice);
					if (item != NULL) {
						item->data->printDetail();
					}
					else {
						cout << "ERROR: INVALID Item's ID." << endl;
					}
				}
				//Case 6.1: Seach an Item By Title
				else if (choice == "2") {
					do {
						cout << "Enter the item's Title you want to search: ";
						cin.ignore();
						getline(cin, choice);
						if (validateTitle(choice, "choice"))
							break;
					} while (true);

					//Find the Item through Linked List
					LinkedListItem found_list = i_list.searchItemByTitle(choice);
					if (found_list.getHead() != NULL)
						found_list.printItem();
					else
						cout << "ERROR: INVALID Item's Title." << endl;
				}
				//Exit To Item Menu
				else if (choice == "3") {
					break;
				}
				else {
					cout << "ERROR: INVALID choice." << endl;
					itemMenu(i_list, cust_list, i_file_name, cust_file_name);
				}
				cout << "WARNING: Continue to search ? (y/n): ";
				cin >> choice;

				if (choice == "y") {
					cout << endl;
					
				}
				else {
					cout << "****************************************************" << endl;
					cout << endl;
					// Break out the update loop
					break;
				}
			} while (true);
		}

		//Case 7: Exit the Item Menu, Return to Main Menu
		else if (choice == "7") {
			break;
		}
		// Close program.
		else if (choice == "Exit") {
			closeProgram(i_list, cust_list, i_file_name, cust_file_name);
		}
		else {
			cout << "ERROR: Invalid choice" << endl;
		}
	} while (true);
}

//Create Item: Sub Menu
Item* itemCreateMenu(LinkedListItem& i_list) {
	string* inp_array = new string[7];

	// While loop is implemented to validate user's choice before moving to next field.
	do {
		cout << "1. Enter item ID(Ixxx-yyyy): ";
		// Implemented validation. Still need further testing
		cin >> inp_array[0];
		if (validateItemID(inp_array[0], "choice")) {
			// Check if ID is existed in database
			ItemElement* duplicateID = i_list.searchItemByID(inp_array[0]);
			if (duplicateID != NULL) {
				cout << "ERROR: Item's ID has already been used. Please enter another ID" << endl;
			}
			else {
				break;
			}
		}
	} while (true);

	do {
		cout << "2. Enter item's title: ";
		// Implemented validation. Still need further testing
		cin.ignore();
		// Title can contains spaces so need to use getline in this case
		getline(cin, inp_array[1]);
		if (validateTitle(inp_array[1], "choice"))
			break;
	} while (true);

	do {
		cout << "3. Enter item's type(Game, DVD or Record): ";
		// Implemented validation. Still need further testing
		cin >> inp_array[2];
		if (validateRentalType(inp_array[2], "choice"))
			break;
	} while (true);

	do {
		cout << "4. Enter item's loan type(2-day or 1-week): ";
		// Implemented validation. Still need further testing
		cin >> inp_array[3];
		if (validateLoanType(inp_array[3], "choice"))
			break;
	} while (true);

	do {
		cout << "5. Enter item's number of copies: ";
		// Implemented validation. Still need further testing
		cin >> inp_array[4];
		if (validateNumberOfCopies(inp_array[4], "choice"))
			break;
	} while (true);

	do {
		cout << "6. Enter item's rental fee: ";
		// Implemented validation. Still need further testing
		cin >> inp_array[5];
		if (validateRentalFee(inp_array[5], "choice"))
			break;
	} while (true);

	do {
		if (inp_array[2] == "Game") {
			GameItem* new_item = new GameItem(inp_array[0], inp_array[1], inp_array[2], inp_array[3], stod(inp_array[4]), stod(inp_array[5]));
			delete[] inp_array; // free the heap after used
			return new_item;
			break;
		}
		else if (inp_array[2] == "DVD") {
			cout << "7. Enter item's genre (Action, Horror, Comedy or Drama): ";
			// Implemented validation. Still need further testing
			cin >> inp_array[6];
			if (validateGenre(inp_array[6], "choice")) {
				DVDItem* new_item = new DVDItem(inp_array[0], inp_array[1], inp_array[2], inp_array[3], stod(inp_array[4]), stod(inp_array[5]), inp_array[6]);
				delete[] inp_array; // free the heap after used
				return new_item;
				break;
			}
		}
		else {
			cout << "7. Enter item's genre (Action, Horror, Comedy or Drama): ";
			cin >> inp_array[6];
			// Implemented validation. Still need further testing
			if (validateGenre(inp_array[6], "choice")) {
				RecordItem* new_item = new RecordItem(inp_array[0], inp_array[1], inp_array[2], inp_array[3], stod(inp_array[4]), stod(inp_array[5]), inp_array[6]);
				delete[] inp_array; // free the heap after used
				return new_item;
				break;
			}

		}
	} while (true);
}

//Update Item: Sub Menu
void itemUpdateMenu(ItemElement* ptr) {
	string choice;

	do {
		cout << "*********************** Update Item ************************" << endl;
		cout << "* Item ID: " << ptr->data->getId() << endl;
		cout << "* Type: " << ptr->data->getRentalType() << endl;
		cout << "* 1. Item title: " << ptr->data->getTitle() << endl;
		cout << "* 2. Item loan's type: " << ptr->data->getLoanType() << endl;
		cout << "* 3. Item number of copies: " << ptr->data->getNumberOfCopies() << endl;
		cout << "* 4. Item rental fee: " << ptr->data->getRentalFee() << endl;
		if (ptr->data->getRentalType() != "Game") {
			cout << "* 5. Item genre: " << ptr->data->getGenre() << endl;
		}
		cout << "Please Select an option: ";
		cin >> choice;

		if (choice == "1") {
			do {
				cout << "Please Enter item's title: ";
				cin.ignore();
				// Title can contains spaces so need to use getline in this case
				getline(cin, choice);
				if (validateTitle(choice, "choice")) {
					ptr->data->setTitle(choice);
					break;
				}
			} while (true);
		}

		else if (choice == "2") {
			do {
				cout << "Please Enter item's loan type(2-day or 1-week): ";
				cin >> choice;
				if (validateLoanType(choice, "choice")) {
					ptr->data->setLoanType(choice);
					break;
				}
			} while (true);
		}
		else if (choice == "3") {
			while (true) {
				cout << "PLease Enter item's number of copies: ";
				cin >> choice;
				if (validateNumberOfCopies(choice, "choice")) {
					ptr->data->setNumberOfCopies(stoi(choice));
					break;
				}
			}
		}
		else if (choice == "4") {
			do {
				cout << "Pleaes Enter item's rental fee: ";
				cin >> choice;
				if (validateRentalFee(choice, "choice")) {
					ptr->data->setRentalFee(stod(choice));
					break;
				}
			} while (true);
		}
		else if (choice == "5" && (ptr->data->getRentalType() == "DVD" || ptr->data->getRentalType() == "Record")) {
			do {
				cout << "Please Enter item's genre(Action, Horror, Comedy or Drama): ";
				cin >> choice;
				if (validateGenre(choice, "choice")) {
					ptr->data->setGenre(choice);
					break;
				}
			} while (true);
		}
		else {
			cout << "ERROR: INVALID choice. Please try again." << endl;
		}
		cout << "WARNING: Continue to update ? (y/n): ";
		cin >> choice;
		if (choice == "y" || choice =="Y") {
			// Continue to update
		}
		else {
			// Break out the update loop
			break;
		}
	} while (true);

	return;
}
