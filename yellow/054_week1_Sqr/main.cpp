/*
 * main.cpp
 *
 *  Created on: Oct 31, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <vector>
#include <map>
#include <utility>
#include <cmath>

using namespace std;

template <typename T>
T Sqr(const T& n);
template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p);
template <typename T>
vector<T> Sqr(const vector<T>& v);
template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m);

int main() {
	// Пример вызова функции
	vector<int> v = {1, 2, 3};
	cout << "vector:";
	for (int x : Sqr(v)) {
		cout << ' ' << x;
	}
	cout << endl;

	map<int, pair<int, int>> map_of_pairs = {
			{4, {2, 2}},
			{7, {4, 3}}
	};
	cout << "map of pairs:" << endl;
	for (const auto& x : Sqr(map_of_pairs)) {
		cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
	}

	return 0;
}

template <typename T>
T Sqr(const T& n) {
	return (n*n);
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p) {
	return pair<First, Second>(Sqr(p.first), Sqr(p.second));
}

template <typename T>
vector<T> Sqr(const vector<T>& v) {
	vector<T> copy = v;
	for (auto& el : copy) {
		el = Sqr(el);
	}
	return copy;
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& m) {
	map<Key, Value> copy = m;
	for (auto& el : copy) {
		el.second = Sqr(el.second);
	}
	return copy;
}

