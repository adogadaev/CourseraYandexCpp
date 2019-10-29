/*
 * main2.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Anton Dogadaev
 */
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
	const string in_path = "input.txt";
	const string out_path = "output.txt";
	string line;

	ifstream in(in_path);
	ofstream out(out_path);
	if (in.is_open() && out.is_open()) {
		while (getline(in, line)) {
			out << line << endl;
		}

	}
	in.close();
	out.close();

	return 0;
}



