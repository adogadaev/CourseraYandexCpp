#include <algorithm>
#include <iostream>

using namespace std;

template <typename T>
class SimpleVector {
public:
	SimpleVector() = default;
	explicit SimpleVector(size_t size)
		: data(new T[size]),
		  size(size),
		  capacity(size) {}
	SimpleVector(const SimpleVector& other)
		: data(new T[other.capacity]),
		  size(other.size),
		  capacity(other.capacity) {
		copy(other.begin(), other.end(), begin());
	}
	~SimpleVector() { delete[] data; }

	SimpleVector& operator=(const SimpleVector& other) {
//		size = other.size;
//		capacity = other.capacity;
//		delete[] data;
//		data = new T[capacity];
//		copy(other.begin(), other.end(), begin());
		SimpleVector tmp(other);
		swap(tmp.data, data);
		swap(tmp.size, size);
		swap(tmp.capacity, capacity);

		return *this;
	}

	T& operator[](size_t index) { return data[index];	}

	T* begin() { return data; }
	T* end() { return data + size; }
	const T* begin() const { return data; }
	const T* end() const { return data + size; }

	size_t Size() const { return size; }
	size_t Capacity() const { return capacity; }

	void PushBack(const T& value) {
		if (size >= capacity) {
			auto new_cap = (capacity == 0) ? 1 : 2 * capacity;
			auto new_data = new T[new_cap];
			copy(begin(), end(), new_data);
			delete[] data;
			data = new_data;
			capacity = new_cap;
		}
		data[size++] = value;
	}

private:
	T* data = nullptr;
	size_t size = 0;
	size_t capacity = 0;
};
