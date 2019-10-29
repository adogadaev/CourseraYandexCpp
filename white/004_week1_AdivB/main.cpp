/*
 * main.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: Anton Dogadaev
 */

#include <iostream>

using namespace std;

int main() {
	int num, denom;

	cin >> num >> denom;

	if (denom == 0) {
		cout << "Impossible";
		return 0;
	}
	else {
		cout << (num / denom);
	}

	return 0;
}




