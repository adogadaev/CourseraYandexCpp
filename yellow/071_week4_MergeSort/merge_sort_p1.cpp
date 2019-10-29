/*
 * merge_sort_p1.cpp
 *
 *  Created on: Nov 28, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <vector>
#include <iterator>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	if (range_end - range_begin < 2) {
		return;
	}

	using templ_type = typename RandomIt::value_type;
	vector<templ_type> elements(range_begin, range_end);
	auto p1_end = elements.begin() + elements.size() / 2;
	MergeSort(elements.begin(), p1_end);
	MergeSort(p1_end, elements.end());

	merge(elements.begin(), p1_end, p1_end, elements.end(),
			range_begin);
}


