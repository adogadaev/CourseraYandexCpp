/*
 * main.cpp
 *
 *  Created on: Oct 15, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <map>
#include <set>
#include <string>

using namespace std;

set<string> BuildMapValuesSet(const map<int, string>& m) {
	set<string> s;
	for (const auto& map_item : m) {
		s.insert(map_item.second);
	}
	return s;
}

/*
int main() {
	set<string> values = BuildMapValuesSet({
	    {1, "odd"},
	    {2, "even"},
	    {3, "odd"},
	    {4, "even"},
	    {5, "odd"}
	});

	for (const string& value : values) {
	  cout << value << endl;
	}

	return 0;
}
*/


