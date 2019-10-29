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

class Person {
public:
	// Вы можете вставлять сюда различные реализации класса,
	// чтобы проверить, что ваши тесты пропускают корректный код
	// и ловят некорректный
	void ChangeFirstName(int year, const string& first_name) {
		// добавить факт изменения имени на first_name в год year
		mFirstName[year] = first_name;
	}
	void ChangeLastName(int year, const string& last_name) {
		// добавить факт изменения фамилии на last_name в год year
		mLastName[year] = last_name;
	}
	string GetFullName(int year) {
		// получить имя и фамилию по состоянию на конец года year
		auto first_name_it = find_if(mFirstName.rbegin(), mFirstName.rend(),
				[year](const auto& item) {
			return (item.first <= year);
		});
		auto last_name_it =	find_if(mLastName.rbegin(), mLastName.rend(),
				[year](const auto& item) {
			return (item.first <= year);
		});
		if (first_name_it == mFirstName.rend() && last_name_it == mLastName.rend()) {
			return "Incognito";
		}
		else if (first_name_it == mFirstName.rend()) {
			return (last_name_it->second + " with unknown first name");
		}
		else if (last_name_it == mLastName.rend()) {
			return (first_name_it->second + " with unknown last name");
		}
		return (first_name_it->second + " " + last_name_it->second);
	}
private:
	// приватные поля
	map<int, string> mFirstName;
	map<int, string> mLastName;
};

string gen_random_str() {
	static const char alphanum[] =
				"0123456789"
				"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
				"abcdefghijklmnopqrstuvwxyz";
	mt19937 gen;
	uniform_real_distribution<> unif_len(1, 40);
	uniform_real_distribution<> unif_letter(0, sizeof(alphanum) - 1);
	string s;

	for (int i = 0; i < unif_len(gen); ++i) {
		s += alphanum[(uint32_t)unif_letter(gen)];
	}

	return s;
}

int get_random_year() {
	mt19937 gen;
	uniform_real_distribution<> unif(-1000000, 1000000);

	return (int)unif(gen);
}

void TestNameFirst() {
	Person person;
	string full_name;

	int init_year = get_random_year();
	string name1 = gen_random_str();
	string surname1 = gen_random_str();
	string name2 = gen_random_str();
	string surname2 = gen_random_str();

	person.ChangeFirstName(init_year + 65, name1);
	person.ChangeLastName(init_year + 67, surname1);

	full_name = person.GetFullName(init_year);
	AssertEqual(full_name, "Incognito",
			"Test for Incognito");
	full_name = person.GetFullName(init_year + 65);
	AssertEqual(full_name, name1 + " with unknown last name",
			"Test for (first name)/(unknown last name)");
	full_name = person.GetFullName(init_year + 90);
	AssertEqual(full_name, name1 + " " + surname1,
			"Test for (first name)/(last name)");

	person.ChangeFirstName(init_year + 70, name2);

	full_name = person.GetFullName(init_year + 69);
	AssertEqual(full_name, name1 + " " + surname1,
			"Test for (first name)/(last name)");
	full_name = person.GetFullName(init_year + 70);
	AssertEqual(full_name, name2 + " " + surname1,
			"Test for (first name)/(last name)");

	person.ChangeLastName(init_year + 68, surname2);

	full_name = person.GetFullName(init_year + 69);
	AssertEqual(full_name, name1 + " " + surname2,
			"Test for (first name)/(last name)");
	full_name = person.GetFullName(init_year + 70);
	AssertEqual(full_name, name2 + " " + surname2,
			"Test for (first name)/(last name)");
}

void TestSurnameFirst() {
	Person person;
	string full_name;

	int init_year = get_random_year();
	string name1 = gen_random_str();
	string surname1 = gen_random_str();
	string name2 = gen_random_str();
	string surname2 = gen_random_str();

	person.ChangeFirstName(init_year + 67, name1);
	person.ChangeLastName(init_year + 65, surname1);

	full_name = person.GetFullName(init_year);
	AssertEqual(full_name, "Incognito",
			"Test for Incognito");
	full_name = person.GetFullName(init_year + 65);
	AssertEqual(full_name, surname1 + " with unknown first name",
			"Test for (first name)/(unknown last name)");
	full_name = person.GetFullName(init_year + 90);
	AssertEqual(full_name, name1 + " " + surname1,
			"Test for (first name)/(last name)");

	person.ChangeFirstName(init_year + 70, name2);

	full_name = person.GetFullName(init_year + 69);
	AssertEqual(full_name, name1 + " " + surname1,
			"Test for (first name)/(last name)");
	full_name = person.GetFullName(init_year + 70);
	AssertEqual(full_name, name2 + " " + surname1,
			"Test for (first name)/(last name)");

	person.ChangeLastName(init_year + 68, surname2);

	full_name = person.GetFullName(init_year + 69);
	AssertEqual(full_name, name1 + " " + surname2,
			"Test for (first name)/(last name)");
	full_name = person.GetFullName(init_year + 70);
	AssertEqual(full_name, name2 + " " + surname2,
			"Test for (first name)/(last name)");
}

int main() {
	TestRunner runner;

	// добавьте сюда свои тесты
	runner.RunTest(TestNameFirst, "TestNameFirst");
	runner.RunTest(TestSurnameFirst, "TestSurnameFirst");

	return 0;
}




