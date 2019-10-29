/*
 * main1.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Anton Dogadaev
 */
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
    {
        const Rational r(3, 10);
        if (r.Numerator() != 3 || r.Denominator() != 10) {
            cout << "Rational(3, 10) != 3/10" << endl;
            return 1;
        }
    }

    {
        const Rational r(8, 12);
        if (r.Numerator() != 2 || r.Denominator() != 3) {
            cout << "Rational(8, 12) != 2/3" << endl;
            return 2;
        }
    }

    {
        const Rational r(-4, 6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(-4, 6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(4, -6);
        if (r.Numerator() != -2 || r.Denominator() != 3) {
            cout << "Rational(4, -6) != -2/3" << endl;
            return 3;
        }
    }

    {
        const Rational r(0, 15);
        if (r.Numerator() != 0 || r.Denominator() != 1) {
            cout << "Rational(0, 15) != 0/1" << endl;
            return 4;
        }
    }

    {
        const Rational defaultConstructed;
        if (defaultConstructed.Numerator() != 0 || defaultConstructed.Denominator() != 1) {
            cout << "Rational() != 0/1" << endl;
            return 5;
        }
    }

    {
        Rational r1(4, 6);
        Rational r2(2, 3);
        bool equal = r1 == r2;
        if (!equal) {
            cout << "4/6 != 2/3" << endl;
            return 6;
        }
    }

    {
        Rational a(2, 3);
        Rational b(4, 3);
        Rational c = a + b;
        bool equal = c == Rational(2, 1);
        if (!equal) {
            cout << "2/3 + 4/3 != 2" << endl;
            return 7;
        }
    }

    {
        Rational a(5, 7);
        Rational b(2, 9);
        Rational c = a - b;
        bool equal = c == Rational(31, 63);
        if (!equal) {
            cout << "5/7 - 2/9 != 31/63" << endl;
            return 8;
        }
    }

    {
    	Rational a(2, 3);
    	Rational b(4, 3);
    	Rational c = a * b;
    	bool equal = c == Rational(8, 9);
    	if (!equal) {
    		cout << "2/3 * 4/3 != 8/9" << endl;
    		return 9;
    	}
    }

    {
    	Rational a(5, 4);
    	Rational b(15, 8);
    	Rational c = a / b;
    	bool equal = c == Rational(2, 3);
    	if (!equal) {
    		cout << "5/4 / 15/8 != 2/3" << endl;
    		return 10;
    	}
    }

    {
    	ostringstream output;
    	output << Rational(-6, 8);
    	if (output.str() != "-3/4") {
    		cout << "Rational(-6, 8) should be written as \"-3/4\"" << endl;
    		return 11;
    	}
    }

    {
    	istringstream input("5/7");
    	Rational r;
    	input >> r;
    	bool equal = r == Rational(5, 7);
    	if (!equal) {
    		cout << "5/7 is incorrectly read as " << r << endl;
    		return 12;
    	}
    }

    {
    	istringstream input("5/7 10/8");
    	Rational r1, r2;
    	input >> r1 >> r2;
    	bool correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    	if (!correct) {
    		cout << "Multiple values are read incorrectly: " << r1 << " " << r2 << endl;
    		return 13;
    	}

    	input >> r1;
    	input >> r2;
    	correct = r1 == Rational(5, 7) && r2 == Rational(5, 4);
    	if (!correct) {
    		cout << "Read from empty stream shouldn't change arguments: " << r1 << " " << r2 << endl;
    		return 14;
    	}
    }

    {
    	const set<Rational> rs = {{1, 2}, {1, 25}, {3, 4}, {3, 4}, {1, 2}};
    	if (rs.size() != 3) {
    		cout << "Wrong amount of items in the set" << endl;
    		return 15;
    	}

    	vector<Rational> v;
    	for (auto x : rs) {
    		v.push_back(x);
    	}
    	if (v != vector<Rational>{{1, 25}, {1, 2}, {3, 4}}) {
    		cout << "Rationals comparison works incorrectly" << endl;
    		return 16;
    	}
    }

    {
    	map<Rational, int> count;
    	++count[{1, 2}];
    	++count[{1, 2}];

    	++count[{2, 3}];

    	if (count.size() != 2) {
    		cout << "Wrong amount of items in the map" << endl;
    		return 17;
    	}
    }

    cout << "OK" << endl;
    return 0;
}




