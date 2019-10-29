/*
 * main.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <vector>

#define QUIET 0
#define WORRY 1

using namespace std;

int main() {
	int op_num;
	vector<int> queue(0);
	string oper_str;
	int oper_code;

	cin >> op_num;
	for (int i = 0; i < op_num; i++) {
		cin >> oper_str;
		if (oper_str == "WORRY") {
			cin >> oper_code;
			queue[oper_code] = WORRY;
		}
		else if (oper_str == "QUIET") {
			cin >> oper_code;
			queue[oper_code] = QUIET;
		}
		else if (oper_str == "COME") {
			cin >> oper_code;
			size_t prev_size = queue.size();
			queue.resize(prev_size + oper_code, QUIET);
		}
		else if (oper_str == "WORRY_COUNT") {
			int worry_count = 0;
			for (auto m : queue) {
				if (m == WORRY) {
					worry_count++;
				}
			}
			cout << worry_count << endl;
		}
	}
	return 0;
}




