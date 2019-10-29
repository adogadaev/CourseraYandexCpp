/*
 * main.cpp
 *
 *  Created on: Dec 1, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <deque>
#include <string>

using namespace std;

int main() {
	int num;
	int eq_num;
	cin >> num;
	cin >> eq_num;

	deque<string> d;
	string op_code;
	d.push_back(to_string(num));
	for (int i = 0; i < eq_num; i++) {
		d.push_front("(");
		d.push_back(")");
		cin >> op_code >> num;
		d.push_back(" ");
		d.push_back(op_code);
		d.push_back(" ");
		d.push_back(to_string(num));
	}
	for (size_t i = 0; i < d.size(); i++) {
		cout << d[i];
	}
	cout << endl;

	return 0;
}

//int main() {
//	int num;
//	int eq_num;
//	cin >> num;
//	cin >> eq_num;
//
//	deque<string> d;
//	string op_code;
//	d.push_back(to_string(num));
//	bool low_priority_flag = false;
//	for (int i = 0; i < eq_num; i++) {
//		cin >> op_code >> num;
//		if (low_priority_flag == true && (op_code == "*" || op_code == "/")) {
//			d.push_front("(");
//			d.push_back(")");
//			low_priority_flag = false;
//		}
//		d.push_back(" ");
//		d.push_back(op_code);
//		d.push_back(" ");
//		d.push_back(to_string(num));
//		if (op_code == "+" || op_code == "-") {
//			low_priority_flag = true;
//		}
//	}
//	for (size_t i = 0; i < d.size(); i++) {
//		cout << d[i];
//	}
//	cout << endl;
//
//	return 0;
//}



