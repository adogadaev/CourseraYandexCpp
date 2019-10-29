/*
 * main.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int num;
	int a;
	vector<int> v;

	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> a;
		v.push_back(a);
	}
	sort(v.begin(), v.end(), [](int x, int y){ return (abs(x) < abs(y)); });
	for (const auto& i : v) {
		cout << i << ' ';
	}

	return 0;
}



