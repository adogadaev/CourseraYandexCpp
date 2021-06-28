#include "test_runner.h"
#include "profile.h"

#include <future>
#include <numeric>
#include <vector>

using namespace std;

template <typename Iterator>
class Paginator {
private:
	class IteratorRange {
	public:
		IteratorRange(Iterator f, Iterator l) : first(f), last(l), size_(distance(first, last)) {}

		Iterator begin() const { return first; }
		Iterator end() const { return last; }

		size_t size() const { return size_; }
	private:
		Iterator first, last;
		size_t size_;
	};
public:
	Paginator(Iterator begin, Iterator end, size_t page_size) {
		while (begin != end) {
			size_t dist = distance(begin, end);
			mPages.push_back({begin, next(begin, min(page_size, dist))});
			begin = next(begin, min(page_size, dist));
		}
	}

	auto begin() const { return mPages.begin(); }
	auto end() const { return mPages.end(); }

	size_t size() const { return mPages.size(); }
private:
	vector<IteratorRange> mPages;
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator{c.begin(), c.end(), page_size};
}

int64_t CalculateMatrixSum(const vector<vector<int>>& matrix) {
	// Реализуйте эту функцию
	int64_t sum = 0;
	const size_t thread_num = 8;
	size_t page_size = (matrix.size() >= thread_num) ? (matrix.size() / thread_num) : 1;
	vector<future<int64_t>> work;

	for (auto page : Paginate(matrix, page_size)) {
		work.push_back(
			async([page] {
				int64_t interim_sum = 0;
				for (const auto& row : page) {
					interim_sum += accumulate(row.begin(), row.end(), (int64_t)0);
				}

				return interim_sum;
			})
		);
	}
	for (auto& t : work) {
		sum += t.get();
	}

	return sum;
}

void TestCalculateMatrixSum() {
	const vector<vector<int>> matrix = {
			{1, 2, 3, 4},
			{5, 6, 7, 8},
			{9, 10, 11, 12},
			{13, 14, 15, 16}
	};
	{
		LOG_DURATION("TestCalculateMatrixSum");
		ASSERT_EQUAL(CalculateMatrixSum(matrix), 136);
	}
}

void TestCalculateBigMatrixSum() {
	vector<vector<int>> matrix(9000);
	for (size_t i = 0; i < 9000; ++i) {
		matrix.push_back(vector<int>(9000));
		for (size_t j = 0; j < 9000; ++j) {
			matrix[i].push_back(j);
		}
	}

	{
		LOG_DURATION("TestCalculateBigMatrixSum");
		ASSERT_EQUAL(CalculateMatrixSum(matrix), 364459500000);
	}
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestCalculateMatrixSum);
	RUN_TEST(tr, TestCalculateBigMatrixSum);
}
