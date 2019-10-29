/*
 * main.cpp
 *
 *  Created on: Oct 31, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <utility>
#include <string>

using namespace std;

template <typename Collection>
string Join(const Collection& c, char d) {
	stringstream ss;
	bool first = true;
	for (const auto& i : c) {
		if (!first) {
			ss << d;
		}
		first = false;
		ss << i;
	}
	return ss.str();
}

template <typename First, typename Second>
ostream& operator<<(ostream& out, const pair<First, Second>& p) {
	return out << '(' << p.first << ',' << p.second << ')';
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& vi) {
	return out << '[' << Join(vi, ',') << ']';
}

template <typename Key, typename Value>
ostream & operator << (ostream& out, const map<Key, Value>& m) {
	return out << '{' << Join(m, ',') << '}';
}

template <typename T>
T Max(T a, T b) {
	if (b < a) {
		return a;
	}
	return b;
}

int main() {
	vector<double> vi = {1.4, 2, 3};
	cout << vi << endl;
	map<int, double> m = {{1, 2.5}, {3, 4}};
	cout << m << endl;
	vector<vector<int>> v = {{1, 2}, {3, 4}};
	cout << v << endl;

	cout << Max<double>(2, 3.5) << endl;
	cout << max<double>(2, 3.5) << endl;

	return 0;
}



