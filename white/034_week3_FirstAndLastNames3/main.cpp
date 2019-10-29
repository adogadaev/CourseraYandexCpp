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
	Person(const string& fname, const string& lname, int birth_year) {
		mBirthYear = birth_year;
		mFirstName[mBirthYear] = fname;
		mLastName[mBirthYear] = lname;
	}

	void ChangeFirstName(int year, const string& first_name) {
		// добавить факт изменения имени на first_name в год year
		if (year >= mBirthYear) {
			mFirstName[year] = first_name;
		}
	}
	void ChangeLastName(int year, const string& last_name) {
		// добавить факт изменения фамилии на last_name в год year
		if (year >= mBirthYear) {
			mLastName[year] = last_name;
		}
	}
	string GetFullName(int year) const {
		// получить имя и фамилию по состоянию на конец года year
		return RetrieveNameString(year, false);
	}
	string GetFullNameWithHistory(int year) const {
		// получить все имена и фамилии по состоянию на конец года year
		return RetrieveNameString(year, true);
	}
private:
	// приватные поля
	map<int, string> mFirstName;
	map<int, string> mLastName;
	int mBirthYear;

	string RetrieveNameString(int year, bool fullHistory) const {
		if (year < mBirthYear) {
			return "No person";
		}

		string first_name_history = BuildNameHistory(mFirstName, year, fullHistory);
		string last_name_history = BuildNameHistory(mLastName, year, fullHistory);

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

	string BuildNameHistory(const map<int, string>& names, int year,
							bool fullHistory) const {
		string history = "";
		auto it = find_if(names.rbegin(), names.rend(),
						[year](const auto& item) {
							return (item.first <= year);
						});

		for (int i = 0; it != names.rend(); it++) {
			if (i == 0) {
				history += it->second;
				i++;
				if (fullHistory == false) {
					break;
				}
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
	Person person("Polina", "Sergeeva", 1960);
	for (int year : {1959, 1960}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	person.ChangeFirstName(1965, "Appolinaria");
	person.ChangeLastName(1967, "Ivanova");
	for (int year : {1965, 1967}) {
		cout << person.GetFullNameWithHistory(year) << endl;
	}

	return 0;
}



