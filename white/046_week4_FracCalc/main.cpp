/*
 * main.cpp
 *
 *  Created on: Oct 19, 2018
 *      Author: Anton Dogadaev
 */
#include <exception>
#include <iostream>
#include <map>
#include <sstream>
#include <set>
#include <vector>

using namespace std;

class Rational {
public:
	Rational() {
		// Реализуйте конструктор по умолчанию
		mNumer = 0;
		mDenom = 1;
	}

	Rational(int numerator, int denominator) {
		// Реализуйте конструктор
		if (denominator == 0) {
			throw invalid_argument("Invalid argument");
		}
		if (numerator == 0) {
			mNumer = 0;
			mDenom = 1;
		} else {
			int gcd = getGcd(numerator, denominator);
			mNumer = numerator / gcd;
			mDenom = denominator / gcd;
			if (mDenom < 0) {
				mNumer *= (-1);
				mDenom *= (-1);
			}
		}
	}

	int Numerator() const {
		// Реализуйте этот метод
		return mNumer;
	}

	int Denominator() const {
		// Реализуйте этот метод
		return mDenom;
	}

private:
	// Добавьте поля
	int mNumer;
	int mDenom;

	int getGcd(int a, int b) {
		if (a < b) {
			int tmp = a;
			a = b;
			b = tmp;
		}
		int r;
		do {
			r = a % b;
			a = b;
			b = r;
		} while (r != 0);

		return a;
	}
};

bool operator==(const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() == rhs.Numerator() &&
			lhs.Denominator() == rhs.Denominator());
}

bool operator<(const Rational& lhs, const Rational& rhs) {
	return (lhs.Numerator() * rhs.Denominator()
			< rhs.Numerator() * lhs.Denominator());
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Denominator() +
			rhs.Numerator() * lhs.Denominator(),
			lhs.Denominator() * rhs.Denominator());
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Denominator() -
			rhs.Numerator() * lhs.Denominator(),
			lhs.Denominator() * rhs.Denominator());
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.Numerator() * rhs.Numerator(),
			lhs.Denominator() * rhs.Denominator());
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	if (lhs.Denominator() == 0 || rhs.Numerator() == 0) {
		throw domain_error("Division by zero");
	}
	return Rational(lhs.Numerator() * rhs.Denominator(),
			lhs.Denominator() * rhs.Numerator());
}

ostream& operator<<(ostream& out, const Rational& frac) {
	out << frac.Numerator() << '/' << frac.Denominator();
	return out;
}

istream& operator>>(istream& in, Rational& frac) {
	int numer, denom;
	char c;

	if ((in >> numer) && (in >> c) && (c == '/') && (in >> denom)) {
		frac = Rational(numer, denom);
	}
	return in;
}

int main() {
	Rational frac1, frac2;
	string op_code;

	try {
		cin >> frac1 >> op_code >> frac2;
		if (op_code == "+") {
			cout << frac1 + frac2 << endl;
		} else if (op_code == "-") {
			cout << frac1 - frac2 << endl;
		} else if (op_code == "*") {
			cout << frac1 * frac2 << endl;
		} else if (op_code == "/") {
			cout << frac1 / frac2 << endl;
		}
	} catch (exception& e) {
		cout << e.what() << endl;
	}

	return 0;
}
