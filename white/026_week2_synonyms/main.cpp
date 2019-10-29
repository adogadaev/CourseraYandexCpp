/*
 * main.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

int main() {
	int num;
	string command;
	map<string, set<string>> synonyms;

	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> command;
		if (command == "ADD") {
			string word1, word2;

			cin >> word1 >> word2;
			synonyms[word1].insert(word2);
			synonyms[word2].insert(word1);
		}
		else if (command == "COUNT") {
			string word;

			cin >> word;
			cout << synonyms[word].size() << endl;
		}
		else if (command == "CHECK") {
			string word1, word2;

			cin >> word1 >> word2;
			if (synonyms[word1].count(word2) == 0) {
				cout << "NO" << endl;
			}
			else {
				cout << "YES" << endl;
			}
		}
	}
	return 0;
}



