#pragma once

#include <algorithm>
#include <cstdlib>

// Реализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
  SimpleVector() : data_(nullptr), size_(0), capacity_(0) {}
  explicit SimpleVector(size_t size) {
	  capacity_ = size_ = size;
	  data_ = new T[size_];
  }

  ~SimpleVector() {
	  if (capacity_ == 1) {
		  delete data_;
	  } else if (capacity_ > 0) {
		  delete[] data_;
	  }
  }

  T& operator[](size_t index) { return data_[index]; }

  T* begin() { return data_; }
  T* end() { return data_ + size_; }
  const T* begin() const { return data_; }
  const T* end() const { return data_ + size_; }

  size_t Size() const { return size_; }
  size_t Capacity() const { return capacity_; }

  void PushBack(const T& value) {
	  if (data_ == nullptr) {
		  data_ = new T;
		  capacity_ = size_ = 1;
		  *data_ = value;
		  return;
	  }

	  if (size_ == capacity_) {
		  T* new_data = new T[2 * capacity_];
		  std::copy(begin(), end(), new_data);
		  new_data[size_] = value;

		  if (capacity_ == 1) {
			  delete data_;
		  } else {
			  delete[] data_;
		  }
		  data_ = new_data;
		  size_++;
		  capacity_ *= 2;

		  return;
	  }

	  data_[size_] = value;
	  size_++;
  }

private:
  // Добавьте поля для хранения данных вектора
  T* data_;
  size_t size_;
  size_t capacity_;
};
