/*
 * main.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>

using namespace std;

int main() {
	int a, b;

	cin >> a >> b;
	if (a % 2 != 0) {
		a++;
	}
	for (int i = a; i <= b; i+=2) {
		cout << i << " ";
	}
	return 0;
}



