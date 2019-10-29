/*
 * main.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>

using namespace std;

int main() {
	int a, b, tmp, r;

	cin >> a >> b;
	if (a < b) {
		tmp = a;
		a = b;
		b = tmp;
	}

	do {
		r = a % b;
		a = b;
		b = r;
	} while (r != 0);
	cout << a;

	return 0;
}



