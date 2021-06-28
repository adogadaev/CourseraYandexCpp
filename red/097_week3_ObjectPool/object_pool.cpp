#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>
using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate() {
	  T* obj;
	  if (deallocated_.empty()) {
		  obj = new T;
	  } else {
		  obj = deallocated_.front();
		  deallocated_.pop_front();
	  }
	  allocated_.insert(obj);
	  return obj;
  }

  T* TryAllocate() {
	  if (deallocated_.empty()) {
		  return nullptr;
	  }
	  return Allocate();
  }

  void Deallocate(T* object) {
	  auto it = allocated_.find(object);
	  if (it == allocated_.end()) {
		  throw invalid_argument("Deallocate");
	  }
	  deallocated_.push_back(*it);
	  allocated_.erase(it);
  }

  ~ObjectPool() {
	  for (const auto& el : allocated_) {
		  delete el;
	  }
	  for (const auto& el : deallocated_) {
		  delete el;
	  }
	  allocated_.clear();
	  deallocated_.clear();
  }

private:
  // Добавьте сюда поля
  set<T*> allocated_;
  deque<T*> deallocated_;
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
