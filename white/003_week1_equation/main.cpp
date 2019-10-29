/*
 * main.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: Anton Dogadaev
 */

#include <iostream>
#include <math.h>

using namespace std;

int main() {
	double a, b, c;

	cin >> a >> b >> c;
	if (a != 0) {
		double x1, x2;
		double discr;

		discr = pow(b,2) - 4*a*c;
		if (discr > 0) {
			x1 = (-b + sqrt(discr)) / (2*a);
			x2 = (-b - sqrt(discr)) / (2*a);
			cout << x1 << " " << x2;
		}
		else if (discr == 0) {
			cout << (-b / (2*a));
		}
	}
	else if (b != 0) {
		cout << (-c / b);
	}

	return 0;
}


