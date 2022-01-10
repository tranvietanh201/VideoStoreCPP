#pragma once

#include <string>
#include <iostream>


using namespace std;

//Validate Customer input

bool validateCustomerID(string CustomerInput, string CustomerMode);

bool validateCustomerName(string CustomerInput, string CustomerMode);

bool validateCustomerAddress(string CustomerInput, string CustomerMode);

bool validateCustomerPhoneNumber(string CustomerInput, string CustomerMode);

bool validateCustomerNumberOfRental(string CustomerInput, string CustomerMode);

bool validateCustomerType(string CustomerInput, string CustomerMode);

//Validate Item Input

bool validateItemID(string ItemInput, string ItemMode);

bool validateTitle(string ItemInput, string ItemMode);

bool validateRentalType(string ItemInput, string ItemMode);

bool validateLoanType(string ItemInput, string ItemMode);

bool validateNumberOfCopies(string ItemInput, string ItemMode);

bool validateRentalFee(string ItemInput, string ItemMode);

bool validateGenre(string inp, string ItemMode);

