#include "test_runner.h"

#include <cstdint>
#include <iterator>
#include <list>
#include <numeric>
#include <vector>
#include <iostream>
#include <utility>

using namespace std;

template <typename RandomIt>
void MakeJosephusPermutationCopy(RandomIt first, RandomIt last, uint32_t step_size) {
  vector<typename RandomIt::value_type> pool(first, last);
  size_t cur_pos = 0;
  while (!pool.empty()) {
    *(first++) = pool[cur_pos];
    pool.erase(pool.begin() + cur_pos);
    if (pool.empty()) {
      break;
    }
    cur_pos = (cur_pos + step_size - 1) % pool.size();
  }
}

template <typename RandomIt>
void move_data(RandomIt from, RandomIt to) {
	while (from != to) {
		swap(*from, *(from - 1));
		from--;
	}
}

void advance_iter(list<size_t>::iterator& it, size_t steps, list<size_t>::iterator begin, list<size_t>::iterator end, size_t& id) {
	for (size_t i = 0; i < steps; i++) {
		it = next(it);
		id++;
		if (it == end) {
			it = begin;
			id = 0;
		}
	}
}

template <typename RandomIt>
void MakeJosephusPermutationSizeT(RandomIt first, RandomIt last, uint32_t step_size) {
  list<size_t> positions;
  for (size_t i = 0; i < (size_t)(last - first); ++i) {
	  positions.push_back(i);
  }
  auto next_kill_it = positions.begin();
  size_t id = 0;
  while (!positions.empty()) {
	  auto cur_kill_it = next_kill_it;
	  move_data(first + id, first);
	  first++;

	  advance_iter(next_kill_it, 1, positions.begin(), positions.end(), id);
	  positions.erase(cur_kill_it);
	  if (id != 0) {
		  id--;
	  }

	  if (positions.empty()) {
		  break;
	  }

	  advance_iter(next_kill_it, step_size - 1, positions.begin(), positions.end(), id);
  }
}

template <typename Container, typename Iter>
void advance_iter(Iter& it, size_t steps, Container& c) {
	for (size_t i = 0; i < steps; i++) {
		it = next(it);
		if (it == c.end()) {
			it = c.begin();
		}
	}
}

template <typename RandomIt>
void MakeJosephusPermutation(RandomIt first, RandomIt last, uint32_t step_size) {
  list<typename RandomIt::value_type> positions;
  for (auto it = first; it != last; ++it) {
	  positions.push_back(move(*it));
  }
  auto next_kill_it = positions.begin();
  while (!positions.empty()) {
	  auto cur_kill_it = next_kill_it;
	  *(first++) = move(*cur_kill_it);

	  advance_iter(next_kill_it, 1, positions);
	  positions.erase(cur_kill_it);
	  if (positions.empty()) {
		  break;
	  }
	  advance_iter(next_kill_it, step_size - 1, positions);
  }
}

vector<int> MakeTestVector() {
  vector<int> numbers(10);
  iota(begin(numbers), end(numbers), 0);
  return numbers;
}

void TestIntVector() {
  const vector<int> numbers = MakeTestVector();
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 1);
    ASSERT_EQUAL(numbers_copy, numbers);
  }
  {
    vector<int> numbers_copy = numbers;
    MakeJosephusPermutation(begin(numbers_copy), end(numbers_copy), 3);
    ASSERT_EQUAL(numbers_copy, vector<int>({0, 3, 6, 9, 4, 8, 5, 2, 7, 1}));
  }
}

// Это специальный тип, который поможет вам убедиться, что ваша реализация
// функции MakeJosephusPermutation не выполняет копирование объектов.
// Сейчас вы, возможно, не понимаете как он устроен, однако мы расскажем,
// почему он устроен именно так, далее в блоке про move-семантику —
// в видео «Некопируемые типы»

struct NoncopyableInt {
  int value;

  NoncopyableInt(int value) : value(value) {}

  NoncopyableInt(const NoncopyableInt&) = delete;
  NoncopyableInt& operator=(const NoncopyableInt&) = delete;

  NoncopyableInt(NoncopyableInt&&) = default;
  NoncopyableInt& operator=(NoncopyableInt&&) = default;
};

bool operator == (const NoncopyableInt& lhs, const NoncopyableInt& rhs) {
  return lhs.value == rhs.value;
}

ostream& operator << (ostream& os, const NoncopyableInt& v) {
  return os << v.value;
}

void TestAvoidsCopying() {
  vector<NoncopyableInt> numbers;
  numbers.push_back({1});
  numbers.push_back({2});
  numbers.push_back({3});
  numbers.push_back({4});
  numbers.push_back({5});

  MakeJosephusPermutation(begin(numbers), end(numbers), 2);

  vector<NoncopyableInt> expected;
  expected.push_back({1});
  expected.push_back({3});
  expected.push_back({5});
  expected.push_back({4});
  expected.push_back({2});

  ASSERT_EQUAL(numbers, expected);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestIntVector);
  RUN_TEST(tr, TestAvoidsCopying);
  return 0;
}
