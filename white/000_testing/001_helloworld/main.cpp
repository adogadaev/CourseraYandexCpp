#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <limits>

using namespace std;

struct Person {
	string name;
	string last_name;
	unsigned int age;
};

int main() {
	vector<int> nums = {1, 2, 3, 5};
	map<string, int> name_to_value;
	vector<Person> staff;
	string s = "abcdefgh";
	vector<int> nums2 = {1, 3, 4, 5, 7, 8, 9, 5};
	unsigned int quantity;
	unsigned int quantity_alg;

	cout << "Hello world!" << endl;
	cout << "Vector's size is " << nums.size() << endl;

	name_to_value["one"] = 1;
	name_to_value["two"] = 2;
	cout << "one is " << name_to_value["one"] << endl;

	staff.push_back({"Ivan", "Ivanov", 25});
	staff.push_back({"Petr", "Petrov", 30});
	cout << staff[0].last_name << endl;

	for (char c : s) {
		cout << c << ",";
	}
	cout << endl;

	for (auto c : s) {
		cout << c << ",";
	}
	cout << endl;

	quantity = 0;
	for (auto i : nums2) {
		if (i == 5) {
			quantity++;
		}
	}
	quantity_alg = count(begin(nums2), end(nums2), 5);
	cout << "There are " << quantity << " fives in nums2" << endl;
	cout << "There are " << quantity_alg << " fives in nums2" << endl;

	sort(begin(nums2), end(nums2));
	for (auto i : nums2) {
		cout << i << " ";
	}
	cout << endl;

	map<string, int> mStrInt = {{"a", 1}, {"b", 2}, {"c", 3}};
	string concat = "";
	int sum = 0;
	for (auto i : mStrInt) {
		concat += i.first;
		sum += i.second;
	}
	cout << concat << " " << sum << endl;

	map<string, int> m1 = {{"one", 1}, {"two", 2}};
	for (const auto& [key, value] : m1) {
		cout << key << " " << value << endl;
	}
	cout << endl;

	map<int, string> m2 = {{1, "odd"}, {2, "even"}, {1, "one"}};
	for (const auto& [key, value] : m2) {
		cout << key << " " << value << endl;
	}

	cout << sizeof(int) << " " << sizeof(size_t) << " "
		 << sizeof(long int) << endl;
	cout << numeric_limits<int>::min() << " " <<
			numeric_limits<int>::max() << endl;
	cout << numeric_limits<long int>::min() << " " <<
				numeric_limits<long int>::max() << endl;

	int x = 2'000'000'000;
	cout << x << endl;

	return 0;
}
