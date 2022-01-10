// main.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include "GameItem.h"
#include "Item.h"
#include "RecordItem.h"
#include "DVDItem.h"
#include "MainMenu.h"
#include "LinkedListItem.h"
#include "ItemElement.h"
#include "ItemData.h"
#include "CustomerInfo.h"
#include "LinkedListCustomer.h"

using namespace std;



void closeWithFileError() {

	cout << "ERROR: Input database files are not correctly." << endl;
	cout << endl;

	// Display group information
	cout << "- - - - - - - - - - Group Information - - - - - - - - - -" << endl;
	cout << "|                 ASSIGNMENT 2 GROUP 18                 |" << endl;
	cout << "|                                                       |" << endl;
	cout << "|       s3699000, s3699000@rmit.edu.vn, An, Tran        |" << endl;
	cout << "|       s3795683, s3795683@rmit.edu.vn, Anh, Tran       |" << endl;
	cout << "|       s3741280, s3741280@rmit.edu.vn, Duong, Nguyen   |" << endl;
	cout << "|       s3705122, s3705122@rmit.edu.vn, Vu, Pham        |" << endl;
	cout << "- - - - - - - - - - - - - - - - - - - - - - - - - - - - -" << endl;
	// Stop the program
	cout << "Closing the program..." << endl;
	exit(0);
}

int main(int argc, char* argv[])
{

	LinkedListItem itemList; // Initialize item list
	LinkedListCustomer customerList; // Initialize customer list

	if (argc <= 2)
	{
		cout << "No command line arguments provided" << endl;
		closeWithFileError();
		return -1;
	}

	string f1 = argv[1];
	string f2 = argv[2];
	// Check input file's names
	if (f1 != "items.txt" || f2 != "customers.txt")
	{
		closeWithFileError();
		return -1;
	}

	ItemData(itemList, argv[1]); // Read item file
	CustomerData(customerList, argv[2]); // Read customer file

	mainMenu(itemList, customerList, argv[1], argv[2]); // Call main menu function


	return 0;
}