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

int GetDistinctRealRootCount(double a, double b, double c) {
	// Вы можете вставлять сюда различные реализации функции,
	// чтобы проверить, что ваши тесты пропускают корректный код
	// и ловят некорректный
	if (a == 0 && b == 0) {
		return 0;
	} else if (a == 0) {
		return 1;
	}
	double d = b*b - 4 * a * c;
	int roots_num = (d > 0) ? 2 : (d == 0) ? 1 : 0;
	return roots_num;
}

void TestDiscrPositive() {
	double a = 2;
	double b = 4;
	double c = 1;
	string hint = "a=" + to_string(a) +
				  ", b=" + to_string(b) +
				  ", c=" + to_string(c);
	AssertEqual(GetDistinctRealRootCount(a, b, c), 2, hint);
}

void TestDiscrZero() {
	double a = 2;
	double b = 4;
	double c = 2;
	string hint = "a=" + to_string(a) +
				  ", b=" + to_string(b) +
				  ", c=" + to_string(c);
	AssertEqual(GetDistinctRealRootCount(a, b, c), 1, hint);
}

void TestDiscrNeg() {
	double a = 10;
	double b = 4;
	double c = 2;
	string hint = "a=" + to_string(a) +
				  ", b=" + to_string(b) +
				  ", c=" + to_string(c);
	AssertEqual(GetDistinctRealRootCount(a, b, c), 0, hint);
}

void TestBoundaries() {
	double a = 10;
	double b = 4;
	double c = 2;
	string hint = "a=" + to_string(a) +
				  ", b=" + to_string(b) +
				  ", c=" + to_string(c);
	int roots_num = GetDistinctRealRootCount(a, b, c);
	Assert(roots_num >= 0 && roots_num <= 2, hint);
	a = 2;
	b = 4;
	c = 2;
	hint = "a=" + to_string(a) +
		   ", b=" + to_string(b) +
		   ", c=" + to_string(c);
	roots_num = GetDistinctRealRootCount(a, b, c);
	Assert(roots_num >= 0 && roots_num <= 2, hint);
	a = 2;
	b = 4;
	c = 1;
	hint = "a=" + to_string(a) +
		   ", b=" + to_string(b) +
		   ", c=" + to_string(c);
	roots_num = GetDistinctRealRootCount(a, b, c);
	Assert(roots_num >= 0 && roots_num <= 2, hint);
}

void TestLinearEq() {
	double a = 0;
	double b = 4;
	double c = 2;
	string hint = "a=" + to_string(a) +
				  ", b=" + to_string(b) +
				  ", c=" + to_string(c);
	AssertEqual(GetDistinctRealRootCount(a, b, c), 1, hint);
}

void TestNotEq() {
	double a = 0;
	double b = 0;
	double c = 2;
	string hint = "a=" + to_string(a) +
				  ", b=" + to_string(b) +
				  ", c=" + to_string(c);
	AssertEqual(GetDistinctRealRootCount(a, b, c), 0, hint);
}

int main() {
	TestRunner runner;
	// добавьте сюда свои тесты
	runner.RunTest(TestDiscrPositive, "TestDiscrPositive");
	runner.RunTest(TestDiscrZero, "TestDiscrZero");
	runner.RunTest(TestDiscrNeg, "TestDiscrNeg");
	runner.RunTest(TestBoundaries, "TestBoundaries");
	runner.RunTest(TestLinearEq, "TestLinearEq");
	runner.RunTest(TestNotEq, "TestNotEq");
	return 0;
}




