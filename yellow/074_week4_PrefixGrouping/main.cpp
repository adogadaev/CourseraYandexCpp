/*
 * main.cpp
 *
 *  Created on: Nov 30, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

template <typename RandomIt>
pair<RandomIt, RandomIt> FindStartsWith(
		RandomIt range_begin, RandomIt range_end,
		char prefix) {
	string prefix_str(1, prefix);
	auto bounds = equal_range(range_begin, range_end, prefix_str,
			[](const string& x, const string& y) {
				return (x[0] < y[0]);
	});
	return bounds;
}

int main() {
	const vector<string> sorted_strings = {"moscow", "murmansk", "vologda"};

	const auto m_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), 'm');
	for (auto it = m_result.first; it != m_result.second; ++it) {
		cout << *it << " ";
	}
	cout << endl;

	const auto p_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), 'p');
	cout << (p_result.first - begin(sorted_strings)) << " " <<
			(p_result.second - begin(sorted_strings)) << endl;

	const auto z_result =
			FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
	cout << (z_result.first - begin(sorted_strings)) << " " <<
			(z_result.second - begin(sorted_strings)) << endl;

	return 0;
}

//template <typename RandomIt>
//pair<RandomIt, RandomIt> FindStartsWith(
//		RandomIt range_begin, RandomIt range_end,
//		const string& prefix) {
//	auto bounds = equal_range(range_begin, range_end, prefix,
//			[prefix](const string& x, const string& y) {
//				bool res =
//					(x.compare(0, prefix.length(), y, 0, prefix.length()) < 0) ?
//					true : false;
//				return res;
//	});
//	return bounds;
//}
//
//int main() {
//	const vector<string> sorted_strings = {"moscow", "motovilikha", "murmansk"};
//
//	const auto mo_result =
//			FindStartsWith(begin(sorted_strings), end(sorted_strings), "mo");
//	for (auto it = mo_result.first; it != mo_result.second; ++it) {
//		cout << *it << " ";
//	}
//	cout << endl;
//
//	const auto mt_result =
//			FindStartsWith(begin(sorted_strings), end(sorted_strings), "mt");
//	cout << (mt_result.first - begin(sorted_strings)) << " " <<
//			(mt_result.second - begin(sorted_strings)) << endl;
//
//	const auto na_result =
//			FindStartsWith(begin(sorted_strings), end(sorted_strings), "na");
//	cout << (na_result.first - begin(sorted_strings)) << " " <<
//			(na_result.second - begin(sorted_strings)) << endl;
//
//	return 0;
//}
