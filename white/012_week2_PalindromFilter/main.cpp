/*
 * main.cpp
 *
 *  Created on: Oct 12, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

bool IsPalindrom(string str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	int len = str.length();
	for (int i = 0; i < (len / 2); i++) {
		if (str[i] != str[len - i - 1]) {
			return false;
		}
	}
	return true;
}

vector<string> PalindromFilter(vector<string> words, int minLength) {
	vector<string> palindroms;

	for (size_t i = 0; i < words.size(); i++) {
		if (IsPalindrom(words[i]) && words[i].length() >= (size_t)minLength) {
			palindroms.push_back(words[i]);
		}
	}

	return palindroms;
}

int main() {
	string str;
	vector<string> words, palindroms;
	int minLength;

	while (true) {
		cin >> str;
		if (str[str.length()-1] == ',') {
			str.resize(str.length()-1);
			words.push_back(str);
		}
		else {
			words.push_back(str);
			break;
		}
	}
	cin >> minLength;

	palindroms = PalindromFilter(words, minLength);
	for (size_t i = 0; i < palindroms.size(); i++) {
		cout << palindroms[i];
		if (i != (palindroms.size() - 1)) {
			cout << ", ";
		}
	}

	return 0;
}



