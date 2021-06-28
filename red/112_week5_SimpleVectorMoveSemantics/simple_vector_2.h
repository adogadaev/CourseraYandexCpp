#include <algorithm>
#include <cstdint>

using namespace std;

// Реализуйте SimpleVector в этом файле
// и отправьте его на проверку

template <typename T>
class SimpleVector {
public:
	SimpleVector() = default;
	explicit SimpleVector(size_t size)
	: capacity_(size),
	  size_(size),
	  data_(new T[size]) {}
	~SimpleVector() { delete[] data_; }

	T& operator[](size_t index) { return data_[index]; }

	T* begin() { return data_; }
	T* end() { return data_ + size_; }
	const T* begin() const { return data_; }
	const T* end() const { return data_ + size_; }

	size_t Size() const { return size_; }
	size_t Capacity() const { return capacity_; }

	void PushBack(const T& value) {
		if (size_ == capacity_) {
			size_t new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
			T* new_data = new T[new_capacity];
			std::copy(begin(), end(), new_data);
			new_data[size_] = value;

			delete[] data_;
			data_ = new_data;
			size_++;
			capacity_ = new_capacity;

			return;
		}

		data_[size_++] = value;
	}
	void PushBack(T&& value) {
		if (size_ == capacity_) {
			size_t new_capacity = capacity_ == 0 ? 1 : 2 * capacity_;
			T* new_data = new T[new_capacity];
			std::move(begin(), end(), new_data);
			new_data[size_] = move(value);

			delete[] data_;
			data_ = new_data;
			size_++;
			capacity_ = new_capacity;

			return;
		}

		data_[size_++] = move(value);
	}

	// При необходимости перегрузите
	// существующие публичные методы

private:
	// Добавьте сюда поля
	size_t capacity_ = 0;
	size_t size_ = 0;
	T* data_ = nullptr;
};
