/*
 * main.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Anton Dogadaev
 */
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
	const string path = "input.txt";
	string line;
	ifstream in(path);
	if (in.is_open()) {
		while (getline(in, line)) {
			cout << line << endl;
		}

	}
	in.close();

	return 0;
}



