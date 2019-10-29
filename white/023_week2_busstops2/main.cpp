/*
 * main.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Anton Dogadaev
 */
#include <map>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

int main() {
	int req_num;
	int stops_num;
	int new_line_num = 1;
	map<vector<string>, int> map_lines;
	string stop;

	cin >> req_num;
	for (int i = 0; i < req_num; i++) {
		vector<string> cur_line;

		cin >> stops_num;
		for (int j = 0; j < stops_num; j++) {
			cin >> stop;
			cur_line.push_back(stop);
		}
		if (map_lines.count(cur_line) == 0) {
			cout << "New bus " << new_line_num << endl;
			map_lines[cur_line] = new_line_num;
			new_line_num++;
		}
		else {
			cout << "Already exists for " << map_lines[cur_line] << endl;
		}
	}

	return 0;
}



