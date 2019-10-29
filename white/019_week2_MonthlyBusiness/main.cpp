/*
 * main.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Anton Dogadaev
 */
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
	int op_num;
	int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	int cur_month = 0;
	vector<string> montly_business[31];
	string business, instruction;
	int day_num;

	cin >> op_num;
	for (int i = 0; i < op_num; i++) {
		cin >> instruction;
		if (instruction == "ADD") {
			cin >> day_num;
			cin >> business;
			montly_business[day_num-1].push_back(business);
		}
		else if (instruction == "NEXT") {
			int next_month = (cur_month + 1) % 12;
			int next_days = days_in_month[next_month];
			int cur_days = days_in_month[cur_month];
			if (next_days < cur_days) {
				for (int j = next_days; j < cur_days; j++) {
					montly_business[next_days - 1].insert(end(montly_business[next_days - 1]),
							begin(montly_business[j]), end(montly_business[j]));
					montly_business[j].clear();
				}
			}
			cur_month = next_month;
		}
		else if (instruction == "DUMP") {
			cin >> day_num;
			cout << montly_business[day_num-1].size();
			for (auto s : montly_business[day_num-1]) {
				cout << " " << s;
			}
			cout << endl;
		}
	}
	return 0;
}





