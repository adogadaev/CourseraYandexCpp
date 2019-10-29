/*
 * main.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

enum class Gender {
	FEMALE,
	MALE
};

struct Person {
	int age;  // возраст
	Gender gender;  // пол
	bool is_employed;  // имеет ли работу
};

void PrintStats(vector<Person> persons);

template <typename InputIt>
int ComputeMedianAge(InputIt range_begin, InputIt range_end) {
	if (range_begin == range_end) {
		return 0;
	}
	vector<typename InputIt::value_type> range_copy(range_begin, range_end);
	auto middle = begin(range_copy) + range_copy.size() / 2;
	nth_element(
			begin(range_copy), middle, end(range_copy),
			[](const Person& lhs, const Person& rhs) {
		return lhs.age < rhs.age;
	}
	);
	return middle->age;
}

int main() {
	vector<Person> persons = {
			{31, Gender::MALE, false},
			{40, Gender::FEMALE, true},
			{24, Gender::MALE, true},
			{20, Gender::FEMALE, true},
			{80, Gender::FEMALE, false},
			{78, Gender::MALE, false},
			{10, Gender::FEMALE, false},
			{55, Gender::MALE, true},
	};
	PrintStats(persons);
	return 0;
}

void PrintStats(vector<Person> persons) {
	cout << "Median age = "
		<< ComputeMedianAge(begin(persons), end(persons)) << endl;

	auto it_fem_end = partition(begin(persons), end(persons),
		[](const Person& p) {
			return (p.gender == Gender::FEMALE);
	});
	cout << "Median age for females = "
		<< ComputeMedianAge(begin(persons), it_fem_end) << endl;
	cout << "Median age for males = "
		<< ComputeMedianAge(it_fem_end, end(persons)) << endl;

	auto it_fem_empl_end = partition(begin(persons), it_fem_end,
			[](const Person& p) {
				return (p.is_employed == true);
	});
	cout << "Median age for employed females = "
		<< ComputeMedianAge(begin(persons), it_fem_empl_end) << endl;
	cout << "Median age for unemployed females = "
		<< ComputeMedianAge(it_fem_empl_end, it_fem_end) << endl;

	auto it_male_empl_end = partition(it_fem_end, end(persons),
		[](const Person& p) {
			return (p.is_employed == true);
	});
	cout << "Median age for employed males = "
		<< ComputeMedianAge(it_fem_end, it_male_empl_end) << endl;
	cout << "Median age for unemployed males = "
		<< ComputeMedianAge(it_male_empl_end, end(persons)) << endl;
}

