/*
 * main.cpp
 *
 *  Created on: Oct 13, 2018
 *      Author: Anton Dogadaev
 */
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void MoveStrings(vector<string> &source, vector<string> &destination) {
	destination.insert(destination.end(), source.begin(), source.end());
	source.clear();
}

int main() {
	vector<string> source = {"a", "b", "c"};
	vector<string> destination = {"z"};
	MoveStrings(source, destination);
	for (auto s : destination) {
		cout << s << " ";
	}
	cout << endl;
	for (auto s : source) {
		cout << s << " ";
	}
	cout << endl;

	return 0;
}



