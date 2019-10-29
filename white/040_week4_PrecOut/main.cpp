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
	const string path = "input.txt";
	ifstream in(path);
	double val;

	cout << fixed << setprecision(3);
	if (in) {
		in >> val;
	}
	while (in) {
		cout << val << endl;
		in >> val;
	}
	in.close();

	return 0;
}



