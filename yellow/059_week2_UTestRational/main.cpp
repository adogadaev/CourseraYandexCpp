/*
 * main.cpp
 *
 *  Created on: Nov 3, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv.first << ": " << kv.second;
	}
	return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u;
		if (!hint.empty()) {
			os << " hint: " << hint;
		}
		throw runtime_error(os.str());
	}
}

void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << test_name << " OK" << endl;
		} catch (exception& e) {
			++fail_count;
			cerr << test_name << " fail: " << e.what() << endl;
		} catch (...) {
			++fail_count;
			cerr << "Unknown exception caught" << endl;
		}
	}

	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	int fail_count = 0;
};

class Rational {
public:
	// Вы можете вставлять сюда различные реализации,
	// чтобы проверить, что ваши тесты пропускают корректный код
	// и ловят некорректный

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

void TestDefaultConstructor() {
	Rational r;
	Assert(r.Numerator() == 0 && r.Denominator() == 1,
			"Rational() != 0/1");
}

void TestOptimizedFractions() {
	{
		Rational r(3, 10);
		Assert(r.Numerator() == 3 && r.Denominator() == 10,
				"Rational(3, 10) != 3/10");
	}

	{
		Rational r(8, 12);
		Assert(r.Numerator() == 2 && r.Denominator() == 3,
				"Rational(8, 12) != 2/3");
	}

	{
		Rational r(-4, 6);
		Assert(r.Numerator() == -2 && r.Denominator() == 3,
				"Rational(-4, 6) != -2/3");
	}

	{
		Rational r(4, -6);
		Assert(r.Numerator() == -2 && r.Denominator() == 3,
				"Rational(4, -6) != -2/3");
	}

	{
		Rational r(0, 15);
		Assert(r.Numerator() == 0 && r.Denominator() == 1,
				"Rational(0, 15) != 0/1");
	}

	{
		Rational r(-10, -100);
		Assert(r.Numerator() == 1 && r.Denominator() == 10,
				"Rational(-10, -100) != 1/10");
	}

	{
		Rational r(-11, -134);
		Assert(r.Numerator() == 11 && r.Denominator() == 134,
				"Rational(-11, -134) != 11/134");
	}
}

int main() {
	TestRunner runner;
	// добавьте сюда свои тесты
	runner.RunTest(TestDefaultConstructor, "TestDefaultConstructor");
	runner.RunTest(TestOptimizedFractions, "TestOptimizedFractions");
	return 0;
}




