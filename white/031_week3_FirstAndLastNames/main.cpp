/*
 * main.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <string>

using namespace std;

class Person {
public:
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
		if (first_name_it == mFirstName.rend() &&
			last_name_it == mLastName.rend()) {
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

int main() {
	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullName(year) << endl;
	}

	return 0;
}

