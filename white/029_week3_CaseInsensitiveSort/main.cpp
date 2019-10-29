/*
 * main.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int num;
	string str;
	vector<string> v;

	cin >> num;
	for (int i = 0; i < num; i++) {
		cin >> str;
		v.push_back(str);
	}
//	sort(v.begin(), v.end(), [](string x, string y) {
//		transform(x.begin(), x.end(), x.begin(), ::tolower);
//		transform(y.begin(), y.end(), y.begin(), ::tolower);
//		return (x < y);
	sort(v.begin(), v.end(), [](const string& x, const string& y) {
		return lexicographical_compare(x.begin(), x.end(), y.begin(), y.end(),
				[](char c1, char c2) { return (tolower(c1) < tolower(c2)); });
	});
	for (const auto& s : v) {
		cout << s << ' ';
	}

	return 0;
}



