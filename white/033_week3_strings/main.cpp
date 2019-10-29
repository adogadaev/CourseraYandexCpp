/*
 * main.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class ReversibleString {
public:
	ReversibleString() {}
	ReversibleString(const string& s) : mStr(s) {}

	void Reverse() {
		reverse(mStr.begin(), mStr.end());
	}
	string ToString() const {
		return mStr;
	}
private:
	string mStr;
};

//int main() {
//	ReversibleString s("live");
//	s.Reverse();
//	cout << s.ToString() << endl;
//
//	s.Reverse();
//	const ReversibleString& s_ref = s;
//	string tmp = s_ref.ToString();
//	cout << tmp << endl;
//
//	ReversibleString empty;
//	cout << '"' << empty.ToString() << '"' << endl;
//
//	return 0;
//}
