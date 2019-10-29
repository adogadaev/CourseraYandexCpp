/*
 * main.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Anton Dogadaev
 */
#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Student {
	string name;
	string surname;
	unsigned int bday;
	unsigned int bmonth;
	unsigned int byear;

	Student(const string& n, const string& s,
			unsigned int d, unsigned int m, unsigned int y) :
			name(n), surname(s), bday(d), bmonth(m), byear(y) {}
};

int main() {
	unsigned int stud_num, req_num;
	string name, surname;
	unsigned int day, month, year;
	string req;
	unsigned int stud_idx;
	vector<Student> students;

	cin >> stud_num;
	for (unsigned int i = 0; i < stud_num; i++) {
		cin >> name >> surname >> day >> month >> year;
		students.push_back({name, surname, day, month, year});
	}
	cin >> req_num;
	for (unsigned int i = 0; i < req_num; i++) {
		cin >> req >> stud_idx;
		stud_idx--;
		if (req == "name" && stud_idx < students.size()) {
			cout << students[stud_idx].name << " "
				 << students[stud_idx].surname << endl;
		} else if (req == "date" && stud_idx < students.size()) {
			cout << students[stud_idx].bday << "."
				 << students[stud_idx].bmonth << "."
				 << students[stud_idx].byear << endl;
		} else {
			cout << "bad request" << endl;
		}
	}

	return 0;
}

