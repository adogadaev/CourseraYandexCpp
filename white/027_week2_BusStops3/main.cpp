/*
 * main.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
	int num;
	map<set<string>, int> lines;
	int cur_line_num = 1;

	cin >> num;
	for (int i = 0; i < num; i++) {
		int stops_num;
		string stop;
		set<string> cur_line;

		cin >> stops_num;
		for (int j = 0; j < stops_num; j++) {
			cin >> stop;
			cur_line.insert(stop);
		}
		if (lines.count(cur_line) == 0) {
			cout << "New bus " << cur_line_num << endl;
			lines[cur_line] = cur_line_num++;
		}
		else {
			cout << "Already exists for " << lines[cur_line] << endl;
		}
	}

	return 0;
}
