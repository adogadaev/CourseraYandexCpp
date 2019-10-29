/*
 * main.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Anton Dogadaev
 */
#include <fstream>
#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
	int rows, columns, num;
	const string in_path = "input.txt";
	ifstream in(in_path);

	if (in.is_open() == false) {
		return -1;
	}
	in >> rows >> columns;
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			in >> num;
			cout << setw(10) << num;
			if (j == (columns - 1)) {
				cout << endl;
			} else {
				in.ignore(1);
				cout << ' ';
			}
		}
	}
	in.close();

	return 0;
}

