#include "Utilities.h"
#include <iostream>
#include <string>

using namespace std;

string toLowerCase(string inp) {
    int temp= 0;
	while (temp < inp.length())
	{
		if (inp.at(temp) >= 'A' && inp.at(temp) <= 'Z')
			inp.at(temp) += 32;
        temp++;
	}
	return inp;
}
