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

void Reverse(vector<int>& v) {
	reverse(v.begin(), v.end());
}

int main() {
	vector<int> numbers = {1, 5, 3, 4, 2};
	Reverse(numbers);
	for (auto i : numbers) {
		cout << i << " ";
	}

	return 0;
}




