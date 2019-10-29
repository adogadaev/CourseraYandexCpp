/*
 * main.cpp
 *
 *  Created on: Nov 25, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> SplitIntoWords(const string& s) {
	vector<string> result;

	for (auto it = begin(s); it != end(s);) {
		auto next_it = find(it, end(s), ' ');
		string tmp(it, next_it);
		result.push_back(tmp);
		it = next_it;
		if (it != end(s)) {
			it++;
		}
	}

	return result;
}

int main() {
	string s = "C Cpp Java Python";

	vector<string> words = SplitIntoWords(s);
	cout << words.size() << " ";
	for (auto it = begin(words); it != end(words); ++it) {
		if (it != begin(words)) {
			cout << "/";
		}
		cout << *it;
	}
	cout << endl;

	return 0;
}

