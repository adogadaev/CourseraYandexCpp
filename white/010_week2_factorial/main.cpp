/*
 * main.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <cstdlib>

using namespace std;

int Factorial(int num) {
	int fact = 1;
	for (int i = 0; i < num; i++) {
		fact *= (num - i);
	}
	return fact;
}

int main() {
	int num;

	cin >> num;
	cout << Factorial(num);

	return 0;
}



