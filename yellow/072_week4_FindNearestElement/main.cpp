/*
 * main.cpp
 *
 *  Created on: Nov 29, 2018
 *      Author: Anton Dogadaev
 */
#include <set>
#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

// set<int>::const_iterator —
// тип итераторов для константного множества целых чисел
set<int>::const_iterator FindNearestElement(
		const set<int>& numbers,
		int border) {
//	auto low_bound = lower_bound(numbers.begin(), numbers.end(),
//							border);
	auto low_bound = numbers.lower_bound(border);
	if (low_bound == numbers.end()) {
		if (numbers.empty() == true) {
				return numbers.end();
		} else {
			return prev(low_bound);
		}
	} else if (low_bound == numbers.begin()) {
		return low_bound;
	}
	auto prev_bound = prev(low_bound);
	uint32_t delta_low = abs(border - *low_bound);
	uint32_t delta_prev = abs(border - *prev_bound);
	if (delta_low < delta_prev) {
		return low_bound;
	}
	return prev_bound;
}

int main() {
	set<int> numbers = {1, 4, 6};
	cout <<
			*FindNearestElement(numbers, 0) << " " <<
			*FindNearestElement(numbers, 3) << " " <<
			*FindNearestElement(numbers, 5) << " " <<
			*FindNearestElement(numbers, 6) << " " <<
			*FindNearestElement(numbers, 100) << endl;

	set<int> empty_set;

	cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << endl;
	return 0;
}

