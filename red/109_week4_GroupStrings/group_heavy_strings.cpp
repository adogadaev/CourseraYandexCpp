#include "test_runner.h"

#include <algorithm>
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

using namespace std;

// Объявляем Group<String> для произвольного типа String
// синонимом vector<String>.
// Благодаря этому в качестве возвращаемого значения
// функции можно указать не малопонятный вектор векторов,
// а вектор групп — vector<Group<String>>.
template <typename String>
using Group = vector<String>;

// Ещё один шаблонный синоним типа
// позволяет вместо громоздкого typename String::value_type
// использовать Char<String>
template <typename String>
using Char = typename String::value_type;

template <typename String>
vector<Group<String>> GroupHeavyStrings(vector<String> strings) {
	// Напишите реализацию функции,
	// использовав не более 1 копирования каждого символа
	map<set<Char<String>>, list<String>> groups;
	for (auto& str : strings) {
		set<Char<String>> key;
		for (auto& ch : str) {
			key.insert(move(ch));
		}
		groups[move(key)].push_back(move(str));
	}

	vector<Group<String>> res;
	res.reserve((groups.size()));
	size_t i = 0;
	for (auto& group : groups) {
		res.push_back(Group<String>());
		res[i].reserve(group.second.size());
		for (auto& group_el : group.second) {
			res[i].push_back(move(group_el));
		}
		++i;
	}

	return move(res);

//	map<set<Char<String>>, Group<String>> data;
//	vector<String> keys(strings.size());
//	for (const auto& str : strings) {
//		String key = str;
//		key.erase(unique(key.begin(), key.end()), key.end());
//	}
//
//	vector<Group<String>> res;
//	res.reserve(data.size() + 1);
//	for (auto it = data.begin(); it != data.end(); ++it) {
//		res.push_back(move(it->second));
//	}
//
//	return res;
}


void TestGroupingABC() {
	vector<string> strings = {"caab", "abc", "cccc", "bacc", "c"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 2);
	sort(begin(groups), end(groups));  // Порядок групп не имеет значения
	ASSERT_EQUAL(groups[0], vector<string>({"caab", "abc", "bacc"}));
	ASSERT_EQUAL(groups[1], vector<string>({"cccc", "c"}));
}

void TestGroupingReal() {
	vector<string> strings = {"law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl"};
	auto groups = GroupHeavyStrings(strings);
	ASSERT_EQUAL(groups.size(), 4);
	sort(begin(groups), end(groups));  // Порядок групп не имеет значения
	ASSERT_EQUAL(groups[0], vector<string>({"laptop", "paloalto"}));
	ASSERT_EQUAL(groups[1], vector<string>({"law", "wall", "awl"}));
	ASSERT_EQUAL(groups[2], vector<string>({"port"}));
	ASSERT_EQUAL(groups[3], vector<string>({"top", "pot"}));
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestGroupingABC);
	RUN_TEST(tr, TestGroupingReal);
	return 0;
}
