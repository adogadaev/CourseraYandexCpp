#pragma once

#include <array>
#include <stdexcept>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
  explicit StackVector(size_t a_size = 0) {
	  if (a_size > capacity_) {
		  throw invalid_argument("StackVector: size > capacity");
	  }
	  size_= a_size;
  }

  T& operator[](size_t index) {
	  return array_[index];
  }

  const T& operator[](size_t index) const {
	  return array_[index];
  }

  auto begin() { return array_.begin(); }
  auto end() { return next(array_.begin(), size_); }
  auto begin() const { return array_.cbegin(); }
  auto end() const { return next(array_.cbegin(), size_); }

  size_t Size() const {
	  return size_;
  }

  size_t Capacity() const {
	  return capacity_;
  }

  void PushBack(const T& value) {
	  if (size_ == capacity_) {
		  throw overflow_error("PushBack: size == capacity");
	  }
	  array_[size_] = value;
	  size_++;
  }

  T PopBack() {
	  if (size_ == 0) {
		  throw underflow_error("PopBack: size == 0");
	  }
	  size_--;
	  return array_[size_];
  }

private:
  array<T, N> array_;
  size_t size_;
  const size_t capacity_ = N;
};

