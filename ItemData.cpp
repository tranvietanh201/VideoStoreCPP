#include<iostream>
#include<fstream>
#include <string>

#include "ItemData.h"
#include "GameItem.h"
#include "DVDItem.h"
#include "RecordItem.h"
#include "InputValidation.h"

using namespace std;

void ItemData(LinkedListItem& IL, string FN) {
	string sm;
	int lp = 0;
	ifstream Item_file;
	Item_file.open(FN);
	if (Item_file)
	{
		while (getline(Item_file, sm))
		{
			lp++;
			string temporary_list[10];
			if (sm[0] == 'I') {

				string temporary_list[7] = { " ", " ", " ", " ", " ", " ", " " };
				string d = ",", tok;
				int pos = 0, tmp = 0;
				while ((pos = sm.find(d)) != string::npos) {
					tok = sm.substr(0, pos);
					temporary_list[tmp] = tok;
					sm.erase(0, pos + d.length());
					tmp++;
				}
				Item* i;
				temporary_list[tmp] = sm;
				// begin the validate for the this case
				// validate the id first

				if (!validateItemID(temporary_list[0], "readFile")) {
					cout << "WARNING: Item may not have appropriate ID at line " << lp
						<< "\nThe item will not be added to the record. Please go and check the database again." << endl;
				}

				else if (!validateTitle(temporary_list[1], "readFile")) {
					cout << "WARNING: Item may not have appropriate title at line " << lp
						<< "\nThe item will not be added to the record. Please go and check the database again." << endl;
				}

				else if (!validateRentalType(temporary_list[2], "readFile")) {
					cout << "WARNING: Item may not have appropriate type at line " << lp
						<< "\nThe item will not be added to the record. Please go and check the database again." << endl;
				}

				else if (!validateLoanType(temporary_list[3], "readFile")) {
					cout << "WARNING: Item may not have appropriate loan period at line " << lp
						<< "\nThe item will not be added to the record. Please go and check the database again." << endl;
				}

				else if (!validateNumberOfCopies(temporary_list[4], "readFile")) {
					cout << "WARNING: Item may not have appropriate number of copies at line " << lp
						<< "\nThe item will not be added to the record. Please go and check the database again." << endl;
				}

				else if (!validateRentalFee(temporary_list[5], "readFile")) {
					cout << "WARNING: Item may not have appropriate rental fee at line " << lp
						<< "\nThe item will not be added to the record. Please go and check the database again." << endl;
				}

				else {
					if (temporary_list[2] == "Game") {
						i = new GameItem(temporary_list[0],
							temporary_list[1],
							temporary_list[2],
							temporary_list[3],
							stoi(temporary_list[4]),
							stod(temporary_list[5]));
						IL.addItem(i);
					}

					else if (temporary_list[2] == "DVD") {
						if (!validateGenre(temporary_list[6], "readFile")) {
							cout << "WARNING: The item may not have appropriate genres at line " << lp
								<< "\nThe item will not be added to the record. Please go and check the database again." << endl;
						}

						else {
							i = new DVDItem(temporary_list[0],
								temporary_list[1],
								temporary_list[2], temporary_list[3],
								stoi(temporary_list[4]),
								stod(temporary_list[5]),
								temporary_list[6]);
							IL.addItem(i);
						}

					}

					else {
						if (!validateGenre(temporary_list[6], "readFile")) {
							cout << "WARNING: The item may not have appropriate genres at line " << lp
								<< "\nThe item will not be added to the record. Please go and check the database again." << endl;
						}

						else {
							i = new RecordItem(temporary_list[0],
								temporary_list[1],
								temporary_list[2],
								temporary_list[3],
								stoi(temporary_list[4]),
								stod(temporary_list[5]),
								temporary_list[6]);
							IL.addItem(i);
						}
					}
				}
			}
			else {
				cout << "WARNING: The item may not have appropriate ID at line " << lp
					<< "\nThe item will not be added to the record. Please go and check the database again." << endl;
			}
		}
		//Close file
		Item_file.close();
	}
}
