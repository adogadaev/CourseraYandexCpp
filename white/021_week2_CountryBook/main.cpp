/*
 * main.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Anton Dogadaev
 */
#include <map>
#include <string>
#include <iostream>

using namespace std;

int main() {
	int req_num;
	string command;
	map<string, string> book;

	cin >> req_num;
	for (int i = 0; i < req_num; i++) {
		cin >> command;
		if (command == "CHANGE_CAPITAL") {
			string country, new_capital;

			cin >> country >> new_capital;
			if (book.count(country) == 0) {
				// country is not in the book
				cout << "Introduce new country " << country << " with capital "
					 << new_capital << endl;
				book[country] = new_capital;
			}
			else {
				// country exists in the book
				if (book[country] == new_capital) {
					cout << "Country " << country
						 << " hasn't changed its capital" << endl;
				}
				else {
					cout << "Country " << country
						 << " has changed its capital from " << book[country]
						 << " to " << new_capital << endl;
					book[country] = new_capital;
				}
			}
		}
		else if (command == "RENAME") {
			string old_country_name, new_country_name;

			cin >> old_country_name >> new_country_name;
			if (book.count(old_country_name) == 0
				|| book.count(new_country_name) > 0) {
				cout << "Incorrect rename, skip" << endl;
			}
			else {
				cout << "Country " << old_country_name << " with capital "
					 << book[old_country_name] << " has been renamed to "
					 << new_country_name << endl;
				//auto nodeHandler = book.extract(old_country_name);
				//nodeHandler.key() = new_country_name;
				//book.insert(move(nodeHandler));
				book[new_country_name] = book[old_country_name];
				book.erase(old_country_name);
			}
		}
		else if (command == "ABOUT") {
			string country;

			cin >> country;
			if (book.count(country) == 0) {
				cout << "Country " << country << " doesn't exist" << endl;
			}
			else {
				cout << "Country " << country << " has capital "
					 << book[country] << endl;
			}
		}
		else if (command == "DUMP") {
			if (book.size() > 0) {
				for (const auto& record : book) {
					cout << record.first << "/" << record.second << " ";
				}
				cout << endl;
			}
			else {
				cout << "There are no countries in the world" << endl;
			}
		}
	}
	return 0;
}

