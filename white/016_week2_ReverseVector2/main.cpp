/*
 * main.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: Anton Dogadaev
 */
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

vector<int> Reversed(const vector<int>& v) {
	vector<int> copyv = v;
	reverse(copyv.begin(), copyv.end());

	return copyv;
}

int main() {
	vector<int> numbers = {1, 5, 3, 4, 2};
	vector<int> copyv = Reversed(numbers);
	for (auto i : copyv) {
		cout << i << " ";
	}

	return 0;
}



