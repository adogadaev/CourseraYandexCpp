/*
 * main.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: Anton Dogadaev
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	vector<string> vStr;
	string minstr;

	vStr.resize(3);
	for (int i = 0; i < 3; i++) {
		cin >> vStr[i];
	}

	minstr = *min_element(vStr.begin(), vStr.end());
	cout << minstr;

	return 0;
}




