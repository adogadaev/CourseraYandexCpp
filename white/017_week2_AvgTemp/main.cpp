/*
 * main.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Anton Dogadaev
 */
#include <vector>
#include <iostream>

using namespace std;

vector<int> getOutput(const vector<int>& days) {
	int avg_temp = 0;
	vector<int> out;

	for (auto d : days) {
		avg_temp += d;
	}
	avg_temp /= days.size();
	for (size_t i = 0; i < days.size(); i++) {
		if (days[i] > avg_temp) {
			out.push_back(i);
		}
	}

	return out;
}

int main() {
	int n;

	cin >> n;
	vector<int> days(n);
	for (int& d : days) {
		cin >> d;
	}
	vector<int> out = getOutput(days);
	cout << out.size() << endl;
	for (auto d : out) {
		cout << d << " ";
	}

	return 0;
}


