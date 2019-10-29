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
	string GetFullNameWithHistory(int year) {
		// получить все имена и фамилии по состоянию на конец года year
		string first_name_history = BuildNameHistory(mFirstName, year);
		string last_name_history = BuildNameHistory(mLastName, year);

		if (first_name_history == "" && last_name_history == "") {
			return "Incognito";
		}
		else if (first_name_history == "") {
			return (last_name_history + " with unknown first name");
		}
		else if (last_name_history == "") {
			return (first_name_history + " with unknown last name");
		}
		return (first_name_history + " " + last_name_history);
	}
private:
	// приватные поля
	map<int, string> mFirstName;
	map<int, string> mLastName;

	string BuildNameHistory(const map<int, string>& names, int year) {
		string history = "";
		auto it = find_if(names.rbegin(), names.rend(),
						[year](const auto& item) {
							return (item.first <= year);
						});

		for (int i = 0; it != names.rend(); it++) {
			if (i == 0) {
				history += it->second;
				i++;
			}
			else {
				string cur_name = it->second;
				string prev_name = prev(it)->second;
				if (prev_name != cur_name) {
					if (i == 1) {
						history += " (";
					}
					else {
						history += ", ";
					}
					history += cur_name;
					i++;
					if (next(it) == names.rend()) {
						history += ")";
					}
				}
			}
		}
		return history;
	}
};

int main() {
//	Person person;
//
//	person.ChangeFirstName(1965, "Polina");
//	person.ChangeLastName(1967, "Sergeeva");
//	for (int year : {1900, 1965, 1990}) {
//		cout << person.GetFullName(year) << endl;
//	}
//
//	person.ChangeFirstName(1970, "Appolinaria");
//	for (int year : {1969, 1970}) {
//		cout << person.GetFullName(year) << endl;
//	}
//
//	person.ChangeLastName(1968, "Volkova");
//	for (int year : {1969, 1970}) {
//		cout << person.GetFullName(year) << endl;
//	}

//	Person person;
//
//	person.ChangeFirstName(1900, "Eugene");
//	person.ChangeLastName(1900, "Sokolov");
//	person.ChangeLastName(1910, "Sokolov");
//	person.ChangeFirstName(1920, "Evgeny");
//	person.ChangeLastName(1930, "Sokolov");
//	cout << person.GetFullNameWithHistory(1940) << endl;

	Person person;

	person.ChangeFirstName(1965, "Polina");
	person.ChangeLastName(1967, "Sergeeva");
	for (int year : {1900, 1965, 1990}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1970, "Appolinaria");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1968, "Volkova");
	for (int year : {1969, 1970}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1990, "Polina");
	person.ChangeLastName(1990, "Volkova-Sergeeva");
	cout << person.GetFullNameWithHistory(1990) << endl;

	person.ChangeFirstName(1966, "Pauline");
	cout << person.GetFullNameWithHistory(1966) << endl;

	person.ChangeLastName(1960, "Sergeeva");
	for (int year : {1960, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeLastName(1961, "Ivanova");
	cout << person.GetFullNameWithHistory(1967) << endl;

	return 0;
}



