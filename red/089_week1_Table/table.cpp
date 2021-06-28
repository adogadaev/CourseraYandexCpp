#include <vector>
#include <utility>
#include <sstream>

#include "test_runner.h"

using namespace std;

// Реализуйте здесь шаблонный класс Table
template<typename T>
class Table {
public:
	Table(size_t str, size_t cols) {
		Resize(str, cols);
	}

	vector<T>& operator[](size_t index) {
		return m_table[index];
	}

	const vector<T>& operator[](size_t index) const {
		return m_table[index];
	}

	void Resize(size_t str, size_t cols) {
		m_table.resize(str);
		for (auto& s : m_table) {
			s.resize(cols);
		}
		if (cols == 0) {
			m_table.resize(0);
		}
	}

	pair<size_t, size_t> Size() const {
		return {m_table.size(), (m_table.size() == 0) ? 0 : m_table[0].size()};
	}

private:
	vector<vector<T>> m_table;
};

void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
  t.Resize(0, 0);
  ASSERT_EQUAL(t.Size().first, 0u);
  ASSERT_EQUAL(t.Size().second, 0u);

  Table<int> t2(3, 3);
  t2[0][0] = 1; t2[0][1] = 2; t2[0][2] = 3;
  t2[1][0] = 4; t2[1][1] = 5; t2[1][2] = 6;
  t2[2][0] = 7; t2[2][1] = 8; t2[2][2] = 9;
  ostringstream os;
  for (size_t i = 0; i < t2.Size().first; i++) {
	  for (size_t j = 0; j < t2.Size().second; j++) {
		  os << t2[i][j];
	  }
	  os << "\n";
  }
  ASSERT_EQUAL(os.str(), "123\n456\n789\n");

  t2.Resize(2, 2);
  os.str("");
  for (size_t i = 0; i < t2.Size().first; i++) {
	for (size_t j = 0; j < t2.Size().second; j++) {
	  os << t2[i][j];
	}
	os << "\n";
  }
  ASSERT_EQUAL(os.str(), "12\n45\n");

  t2.Resize(2, 0);
  ASSERT_EQUAL(t2.Size().first, 0u);
  ASSERT_EQUAL(t2.Size().second, 0u);

  t2.Resize(0, 2);
  ASSERT_EQUAL(t2.Size().first, 0u);
  ASSERT_EQUAL(t2.Size().second, 0u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
