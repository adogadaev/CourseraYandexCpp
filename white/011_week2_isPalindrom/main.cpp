/*
 * main.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <string>
#include <iostream>

using namespace std;

bool IsPalindrom(string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	int len = str.length();
	for (int i = 0; i < (len / 2); i++) {
		if (str[i] != str[len - i - 1]) {
			return false;
		}
	}
	return true;
}

int main() {
	string str;

	cin >> str;

	if (IsPalindrom(str)) {
		cout << "true";
	}
	else {
		cout << "false";
	}

	return 0;
}



