#include "test_runner.h"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>

using namespace std;

template<typename T>
class Entry {
public:
	T data;
	size_t id;
	size_t priority;

private:
	static size_t next_id;

public:
	Entry() = delete;
	Entry(T data) : data(move(data)), id(next_id++), priority(0) {}
	Entry(Entry&& other) : data(move(other.data)), id(other.id), priority(other.priority) {}
	Entry(const Entry&) = delete;
	Entry& operator=(const Entry&) = delete;
	Entry& operator=(Entry&& other) {
		data = move(other.data);
		id = other.id;
		priority = other.priority;
	}

	friend bool operator<(const Entry& lhs, const Entry& rhs) {
		return tie(lhs.priority, lhs.id) < tie(rhs.priority, rhs.id);
	}
};

template<typename T> size_t Entry<T>::next_id = 0;

template <typename T>
class PriorityCollection {
public:
	using Id = size_t;

	// Добавить объект с нулевым приоритетом
	// с помощью перемещения и вернуть его идентификатор
	Id Add(T object) {
		auto it = data_.insert(move(object)).first;
		Id id = it->id;
		idToIt_[id] = it;

		return id;
	}

	// Добавить все элементы диапазона [range_begin, range_end)
	// с помощью перемещения, записав выданные им идентификаторы
	// в диапазон [ids_begin, ...)
	template <typename ObjInputIt, typename IdOutputIt>
	void Add(ObjInputIt range_begin, ObjInputIt range_end,
			IdOutputIt ids_begin) {
		for (auto it = range_begin; it != range_end; ++it, ++ids_begin) {
			auto it_inserted = data_.insert(move(*it)).first;
			Id id = it_inserted->id;
			idToIt_[id] = it_inserted;
			*ids_begin = id;
		}
	}

	// Определить, принадлежит ли идентификатор какому-либо
	// хранящемуся в контейнере объекту
	bool IsValid(Id id) const {
		return (idToIt_.find(id) != idToIt_.end());
	}

	// Получить объект по идентификатору
	const T& Get(Id id) const {
		return idToIt_.at(id)->data;
	}

	// Увеличить приоритет объекта на 1
	void Promote(Id id) {
		auto node = data_.extract(idToIt_.at(id));
		auto entry = move(node.value());
		entry.priority++;

		idToIt_[id] = data_.insert(move(entry)).first;
	}

	// Получить объект с максимальным приоритетом и его приоритет
	pair<const T&, int> GetMax() const {
		return {data_.rbegin()->data, data_.rbegin()->priority};
	}

	// Аналогично GetMax, но удаляет элемент из контейнера
	pair<T, int> PopMax() {
		auto node = data_.extract(prev(data_.end()));
		auto max_entry = move(node.value());
		idToIt_.erase(max_entry.id);

		return {move(max_entry.data), max_entry.priority};
	}

private:
	// Приватные поля и методы
	set<Entry<T>> data_;
	map<Id, typename set<Entry<T>>::iterator> idToIt_;
};


class StringNonCopyable : public string {
public:
	using string::string;  // Позволяет использовать конструкторы строки
	StringNonCopyable(const StringNonCopyable&) = delete;
	StringNonCopyable(StringNonCopyable&&) = default;
	StringNonCopyable& operator=(const StringNonCopyable&) = delete;
	StringNonCopyable& operator=(StringNonCopyable&&) = default;
};

void TestNoCopy() {
	PriorityCollection<StringNonCopyable> strings;
	const auto white_id = strings.Add("white");
	const auto yellow_id = strings.Add("yellow");
	const auto red_id = strings.Add("red");

	strings.Promote(yellow_id);
	for (int i = 0; i < 2; ++i) {
		strings.Promote(red_id);
	}
	strings.Promote(yellow_id);
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "red");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "yellow");
		ASSERT_EQUAL(item.second, 2);
	}
	{
		const auto item = strings.PopMax();
		ASSERT_EQUAL(item.first, "white");
		ASSERT_EQUAL(item.second, 0);
	}
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestNoCopy);
	return 0;
}
