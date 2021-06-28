#include "test_runner.h"
#include <algorithm>
#include <iterator>
#include <memory>
#include <vector>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end) {
	// Напишите реализацию функции,
	// не копируя сортируемые элементы
	if (distance(range_begin, range_end) < 2) {
		return;
	}

	using templ_type = typename RandomIt::value_type;
	vector<templ_type> elements(make_move_iterator(range_begin),
								make_move_iterator(range_end));

	auto p1_end = elements.begin() + elements.size() / 3;
	auto p2_end = elements.begin() + 2 * elements.size() / 3;
	MergeSort(elements.begin(), p1_end);
	MergeSort(p1_end, p2_end);
	MergeSort(p2_end, elements.end());

	vector<templ_type> tempv;
	merge(make_move_iterator(elements.begin()), make_move_iterator(p1_end),
		  make_move_iterator(p1_end), make_move_iterator(p2_end),
		  back_inserter(tempv));
	merge(make_move_iterator(tempv.begin()), make_move_iterator(tempv.end()),
		  make_move_iterator(p2_end), make_move_iterator(elements.end()),
		  range_begin);
}

void TestIntVector() {
	vector<int> numbers = {6, 1, 3, 9, 1, 9, 8, 12, 1};
	MergeSort(begin(numbers), end(numbers));
	ASSERT(is_sorted(begin(numbers), end(numbers)));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestIntVector);
	return 0;
}
