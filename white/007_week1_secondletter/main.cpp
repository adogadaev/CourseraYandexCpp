/*
 * main.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <string>

using namespace std;

int main() {
	string str;
	int num = 0;
	unsigned int i;

	cin >> str;
	for (i = 0; i < str.length(); i++) {
		if (str[i] == 'f') {
			num++;
		}
		if (num == 2) {
			break;
		}
	}
	if (num == 0) {
		cout << "-2";
	}
	else if (num == 1) {
		cout << "-1";
	}
	else {
		cout << i;
	}

	return 0;
}






