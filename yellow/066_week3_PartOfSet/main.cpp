/*
 * main.cpp
 *
 *  Created on: Nov 25, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

template <typename T>
vector<T> FindGreaterElements(const set<T>& elements,
							  const T& border) {
	auto it = find_if(elements.begin(), elements.end(),
						  [border](T val){ return (val > border); });

	return {it, elements.end()};
}

int main() {
	for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
		cout << x << " ";
	}
	cout << endl;

	string to_find = "Python";
	cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
	return 0;
}
