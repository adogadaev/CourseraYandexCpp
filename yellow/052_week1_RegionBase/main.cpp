/*
 * main.cpp
 *
 *  Created on: Oct 30, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <map>
#include <tuple>

using namespace std;

enum class Lang {
	DE, FR, IT
};

struct Region {
	string std_name;
	string parent_std_name;
	map<Lang, string> names;
	int64_t population;
};

bool operator<(const Region& lhs, const Region& rhs) {
	return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
			tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions) {
	map<Region, uint32_t> repetitions;
	uint32_t max_reps = 0;
	for (const auto& region: regions) {
		if (repetitions.count(region) == 0) {
			repetitions[region] = 1;
		} else {
			repetitions[region]++;
		}
		if (repetitions[region] > max_reps) {
			max_reps = repetitions[region];
		}
	}
	return max_reps;
}

int main() {
	cout << FindMaxRepetitionCount({
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
				"Russia",
				"Eurasia",
				{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
				89
		}, {
				"Moscow",
				"Russia",
				{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
				89
		}, {
				"Moscow",
				"Russia",
				{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
				89
		}, {
				"Russia",
				"Eurasia",
				{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
				89
		},
	}) << endl;

	cout << FindMaxRepetitionCount({
		{
			"Moscow",
			"Russia",
			{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
			89
		}, {
				"Russia",
				"Eurasia",
				{{Lang::DE, "Russland"}, {Lang::FR, "Russie"}, {Lang::IT, "Russia"}},
				89
		}, {
				"Moscow",
				"Russia",
				{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou deux"}, {Lang::IT, "Mosca"}},
				89
		}, {
				"Moscow",
				"Toulouse",
				{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
				89
		}, {
				"Moscow",
				"Russia",
				{{Lang::DE, "Moskau"}, {Lang::FR, "Moscou"}, {Lang::IT, "Mosca"}},
				31
		},
	}) << endl;

	return 0;
}

