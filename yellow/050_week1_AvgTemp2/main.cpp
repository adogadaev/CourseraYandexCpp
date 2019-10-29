/*
 * main.cpp
 *
 *  Created on: Oct 29, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <vector>

using namespace std;

int main() {
	uint32_t N;
	vector<int64_t> vT;
	vector<uint32_t> days;
	int64_t cur_temp;
	int64_t sum = 0;
	int64_t avg_temp;

	cin >> N;
	for (uint32_t i = 0; i < N; i++) {
		cin >> cur_temp;
		vT.push_back(cur_temp);
		sum += cur_temp;
	}
	avg_temp = sum / static_cast<int64_t>(N);
	for (uint32_t i = 0; i < vT.size(); i++) {
		if (vT[i] > avg_temp) {
			days.push_back(i);
		}
	}
	cout << days.size() << endl;
	for (const auto& d: days) {
		cout << d << " ";
	}

	return 0;
}



