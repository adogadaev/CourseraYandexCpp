/*
 * merge_sort_p2.cpp
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

	auto p1_end = elements.begin() + elements.size() / 3;
	auto p2_end = elements.begin() + 2 * elements.size() / 3;
	MergeSort(elements.begin(), p1_end);
	MergeSort(p1_end, p2_end);
	MergeSort(p2_end, elements.end());

	vector<templ_type> tempv;
	merge(elements.begin(), p1_end, p1_end, p2_end,
			back_inserter(tempv));
	merge(tempv.begin(), tempv.end(), p2_end, elements.end(),
			range_begin);
}

