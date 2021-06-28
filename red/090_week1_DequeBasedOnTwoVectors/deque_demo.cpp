#include <vector>
#include <stdexcept>

#include "test_runner.h"

template<typename T>
class Deque {
public:
	Deque() {}

	bool Empty() const {
		if (m_vPushFront.empty() && m_vPushBack.empty()) {
			return true;
		}
		return false;
	}

	size_t Size() const {
		return m_vPushFront.size() + m_vPushBack.size();
	}

	T& operator[](size_t index) {
		return At(index);
	}

	const T& operator[](size_t index) const {
		return At(index);
	}

	T& At(size_t index) {
		if (index < m_vPushFront.size()) {
			return *prev(m_vPushFront.end(), index + 1);
		}
		else if (index < m_vPushFront.size() + m_vPushBack.size()) {
			return *next(m_vPushBack.begin(), index - m_vPushFront.size());
		}
		throw std::out_of_range("out of range");
	}

	const T& At(size_t index) const {
		if (index < m_vPushFront.size()) {
			return *prev(m_vPushFront.cend(), index + 1);
		}
		else if (index < m_vPushFront.size() + m_vPushBack.size()) {
			return *next(m_vPushBack.cbegin(), index - m_vPushFront.size());
		}
		throw std::out_of_range("out of range");
	}

	T& Front() {
		return At(0);
	}

	const T& Front() const {
		return At(0);
	}

	T& Back() {
		return At(Size() - 1);
	}

	const T& Back() const {
		return At(Size() - 1);
	}

	void PushFront(const T& v) {
		m_vPushFront.push_back(v);
	}

	void PushBack(const T& v) {
		m_vPushBack.push_back(v);
	}
private:
	std::vector<T> m_vPushFront, m_vPushBack;
};

void TestDeque() {
	Deque<int> dq;

	ASSERT_EQUAL(dq.Size(), 0u);
	try {
		cout << dq.At(0) << endl;
		ASSERT(false);
	} catch(const std::out_of_range& oor) {
		ASSERT(true);
	}

	dq.PushFront(100);
	dq.PushBack(111);
	dq.PushFront(200);
	dq.PushBack(222);
	dq.PushFront(300);
	dq.PushBack(333);

	for (size_t i = 0; i < dq.Size(); i++) {
		cout << dq[i] << " ";
	}
	cout << endl;

	dq[2] = 1914;
	dq[3] = 1918;
	for (size_t i = 0; i < dq.Size(); i++) {
		cout << dq[i] << " ";
	}
	cout << endl;

	Deque<vector<double>> dq2;
	vector<double> v = {1.1, 2.2, 3.3};
	dq2.PushFront(v);
	dq2.PushBack(v);
	for (size_t i = 0; i < dq2.Size(); i++) {
		for (size_t j = 0; j < dq2[i].size(); j++) {
			cout << dq2[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestDeque);
	return 0;
}
