/*
 * main.cpp
 *
 *  Created on: Oct 29, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>

using namespace std;

int main() {
	uint64_t num, density;
	uint64_t w, h, d;
	uint64_t mass = 0;

	cin >> num >> density;
	for (uint32_t i = 0; i < num; i++) {
		cin >> w >> h >> d;
		mass += (w*h*d*density);
	}

	cout << mass;

	return 0;
}



