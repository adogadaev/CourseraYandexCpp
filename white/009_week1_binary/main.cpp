/*
 * main.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: Anton Dogadaev
 */
#include <vector>
#include <iostream>

using namespace std;

int main() {
	int num;
	vector<int> binary;

	cin >> num;
	do {
		binary.push_back(num%2);
		num /= 2;
	} while (num != 0);
	for (unsigned int i = 0; i < binary.size(); i++) {
		cout << binary[binary.size()-i-1];
	}
	return 0;
}



