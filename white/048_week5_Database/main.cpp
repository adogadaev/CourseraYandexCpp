/*
 * main.cpp
 *
 *  Created on: Oct 20, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <string>
#include <sstream>
#include <regex>

using namespace std;

class Date {
public:
	Date() : mYear(0), mMonth(0), mDay(0) {}
	Date(string str) {
		int year, month, day;
		const char delim = '-';
		char c;

		checkStrFormat(str);
		stringstream ss(str);
		if (ss >> year && (ss >> c && c == delim) &&
			ss >> month && (ss >> c && c == delim) &&
			ss >> day) {
			mYear = year;
			checkMonthFormat(month);
			mMonth = month;
			checkDayFormat(day);
			mDay = day;
		} else {
			throw invalid_argument("Wrong date format: " + str);
		}
	}

	int GetYear() const {
		return mYear;
	}
	int GetMonth() const {
		return mMonth;
	}
	int GetDay() const {
		return mDay;
	}
private:
	int mYear;
	int mMonth;
	int mDay;

	void checkStrFormat(string str) {
		int nums_registered = 0;
		const char delim = '-';
		bool neg_sign_detected = false;
		bool recording_digits = false;
		for (size_t i = 0; i < str.length(); i++) {
			if (str[i] == delim && neg_sign_detected == false && recording_digits == false) {
				neg_sign_detected = true;
			} else if (isdigit(str[i]) != 0 && recording_digits == false) {
				recording_digits = true;
			} else if (str[i] == delim && recording_digits == true) {
				neg_sign_detected = false;
				recording_digits = false;
				nums_registered++;
			} else if (isdigit(str[i]) == 0) {
				throw invalid_argument("Wrong date format: " + str);
			}

		}
		if (nums_registered != 2 || recording_digits == false) {
			throw invalid_argument("Wrong date format: " + str);
		}
	}
	void checkMonthFormat(int month) {
		if (month < 1 || month > 12) {
			throw invalid_argument("Month value is invalid: " + to_string(month));
		}
	}
	void checkDayFormat(int day) {
		if (day < 1 || day > 31) {
			throw invalid_argument("Day value is invalid: " + to_string(day));
		}
	}
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear()) {
		return true;
	} else if (lhs.GetYear() == rhs.GetYear() &&
			   lhs.GetMonth() < rhs.GetMonth()) {
		return true;
	} else if (lhs.GetYear() == rhs.GetYear() &&
			   lhs.GetMonth() == rhs.GetMonth() &&
			   lhs.GetDay() < rhs.GetDay()) {
		return true;
	}
	return false;
}

class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		mDb[date].insert(event);
	}
	bool DeleteEvent(const Date& date, const string& event) {
		if (mDb.count(date) > 0 && mDb.at(date).count(event) > 0) {
			mDb.at(date).erase(event);
			if (mDb.at(date).size() == 0) {
				mDb.erase(date);
			}
			return true;
		}
		return false;
	}
	int  DeleteDate(const Date& date) {
		int events = 0;
		if (mDb.count(date) > 0) {
			events = mDb.at(date).size();
		}
		mDb.erase(date);
		return events;
	}

	set<string> Find(const Date& date) const {
		if (mDb.count(date) > 0) {
			return mDb.at(date);
		} else {
			return {};
		}
	}

	void Print() const {
		if (mDb.size() != 0) {
			for (const auto& EventsInDay : mDb) {
				for (const auto& event : EventsInDay.second) {
					cout << setw(4) << setfill('0') << EventsInDay.first.GetYear() << '-';
					cout << setw(2) << setfill('0') << EventsInDay.first.GetMonth() << '-';
					cout << setw(2) << setfill('0') << EventsInDay.first.GetDay() << ' ';
					cout << event << endl;
				}
			}
		} else {
			cout << endl;
		}
	}
private:
	map<Date, set<string>> mDb;
};

int main() {
	Database db;

	string command;
	while (getline(cin, command)) {
		// Считайте команды с потока ввода и обработайте каждую
		stringstream ss(command);
		string command_name;
		string sDate;
		string sEvent;

		if (ss >> command_name) {
			if (command_name == "Add") {
				if (ss >> sDate && ss >> sEvent) {
					try {
						Date date(sDate);
						db.AddEvent(date, sEvent);
					} catch (invalid_argument& e) {
						cout << e.what() << endl;
					}
				}
			} else if (command_name == "Del") {
				if (ss >> sDate) {
					try {
						Date date(sDate);
						if (ss >> sEvent) {
							bool deleted = db.DeleteEvent(date, sEvent);
							if (deleted == true) {
								cout << "Deleted successfully" << endl;
							} else {
								cout << "Event not found" << endl;
							}
						} else {
							int deletedEvents = db.DeleteDate(date);
							cout << "Deleted " << deletedEvents << " events" << endl;
						}
					} catch (invalid_argument& e) {
						cout << e.what() << endl;
					}
				}
			} else if (command_name == "Find") {
				if (ss >> sDate) {
					try {
						Date date(sDate);
						set<string> events = db.Find(date);
						if (events.size() == 0) {
							cout << endl;
						} else {
							for (const string& ev : events) {
								cout << ev << endl;
							}
						}
					} catch (invalid_argument& e) {
						cout << e.what() << endl;
					}
				}
			} else if (command_name == "Print") {
				db.Print();
			} else {
				cout << "Unknown command: " << command_name << endl;
			}
		}
	}

	return 0;
}
