/*
 * main.cpp
 *
 *  Created on: Nov 3, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <random>
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

bool IsPalindrom(const string& str) {
	// Вы можете вставлять сюда различные реализации функции,
	// чтобы проверить, что ваши тесты пропускают корректный код
	// и ловят некорректный
	int len = str.length();
	for (int i = 0; i < (len / 2); i++) {
		if (str[i] != str[len - i - 1]) {
			return false;
		}
	}
	return true;
}

string gen_random_str(string addition = "", uint32_t len = 0) {
	string alphanum =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
	alphanum += addition;
	mt19937 gen{static_cast<long unsigned int>(time(0))};
	uniform_real_distribution<> unif_len(1, 40);
	uniform_real_distribution<> unif_letter(0, sizeof(alphanum) - 1);
	string s;

	int str_len = (len == 0) ? unif_len(gen) : len;
	for (int i = 0; i < str_len; ++i) {
		s += alphanum[(uint32_t)unif_letter(gen)];
	}

	return s;
}

void TestCornerCases() {
	string s = "";
	Assert(IsPalindrom(s), "Empty string should be a palindrom");
	for (int i = 0; i < 100; i++) {
		s = gen_random_str(" ", 1);
		Assert(IsPalindrom(s), "Empty string should be a palindrom");
	}
}

void TestValidPalindroms() {
	for (int i = 0; i < 1000; i++) {
		string s = gen_random_str(" ");
		string s_reversed(s);
		reverse(s_reversed.begin(), s_reversed.end());
		string palindrom = s + s_reversed;
		Assert(IsPalindrom(palindrom),
				"str|rev_str should be accepted as a palindrom");

		palindrom = s + gen_random_str(" ", 1) + s_reversed;
		Assert(IsPalindrom(palindrom),
				"str|rand_char|rev_str should be accepted as a palindrom");
	}
}

void TestUnvalidPalindroms() {
	for (int i = 0; i < 1000; i++) {
		string s = gen_random_str();
		string s_reversed(s);
		reverse(s_reversed.begin(), s_reversed.end());
		string query;

		query = " " + s + s_reversed;
		AssertEqual(IsPalindrom(query), false,
				"<space>str|rev_str should not be accepted as a palindrom");
		query = s + s_reversed + " ";
		AssertEqual(IsPalindrom(query), false,
				"str|rev_str<space> should not be accepted as a palindrom");
		query = " " + s + gen_random_str("", 1) + s_reversed;
		AssertEqual(IsPalindrom(query), false,
				"<space>str|rand_char|rev_str should not be accepted as a palindrom");
		query = s + gen_random_str("", 1) + s_reversed + " ";
		AssertEqual(IsPalindrom(query), false,
				"str|rand_char|rev_str<space> should not be accepted as a palindrom");

		query = "a" + s + s_reversed + "b";
		AssertEqual(IsPalindrom(query), false,
				"<a>str|rev_str<b> should not be accepted as a palindrom");
	}

	for (int i = 0; i < 1000; i++) {
		string s = gen_random_str("", 100);
		string s_reversed(s);
		reverse(s_reversed.begin(), s_reversed.end());
		string query;

		query =  s + "acabr" + s_reversed;
		AssertEqual(IsPalindrom(query), false,
				"str|<acabr>|rev_str should not be accepted as a palindrom");
	}

	string str = "1234ac4321";
	AssertEqual(IsPalindrom(str), false,
			"1234ac4321 should not be accepted as a palindrom");
}

int main() {
	TestRunner runner;
	// добавьте сюда свои тесты
	runner.RunTest(TestCornerCases, "TestCornerCases");
	runner.RunTest(TestValidPalindroms, "TestValidPalindroms");
	runner.RunTest(TestUnvalidPalindroms, "TestUnvalidPalindroms");
	return 0;
}




