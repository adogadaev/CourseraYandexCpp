/*
 * main.cpp
 *
 *  Created on: Oct 14, 2018
 *      Author: Anton Dogadaev
 */
#include <map>
#include <string>
#include <iostream>

using namespace std;

map<char, int> buildCharCounters(const string& word) {
	map<char, int> counter;
	for (char c : word) {
		counter[c]++;
	}
	return counter;
}

int main() {
	int pair_num;
	string word1, word2;

	cin >> pair_num;
	for (int i = 0; i < pair_num; i++) {
		cin >> word1 >> word2;
		map<char, int> counter1 = buildCharCounters(word1);
		map<char, int> counter2 = buildCharCounters(word2);
		if (counter1 == counter2) {
			cout << "YES" << endl;
		}
		else {
			cout << "NO" << endl;
		}
	}
	return 0;
}



