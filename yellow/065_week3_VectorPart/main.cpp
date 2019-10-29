/*
 * main.cpp
 *
 *  Created on: Nov 25, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void PrintVectorPart(const vector<int>& numbers) {
	auto it = find_if(numbers.begin(), numbers.end(),
					  [](int val){ return (val < 0); });
	while (it != numbers.begin()) {
		it--;
		cout << *it << " ";
	}
	cout << endl;
}

int main() {
	PrintVectorPart({6, 1, 8, -5, 4});
	PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
	PrintVectorPart({6, 1, 8, 5, 4});
	return 0;
}



