/*
 * main.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <set>
#include <string>

using namespace std;

int main() {
	int n;
	string line;
	set<string> unique_lines;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> line;
		unique_lines.insert(line);
	}
	cout << unique_lines.size() << endl;

	return 0;
}



