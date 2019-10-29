/*
 * main.cpp
 *
 *  Created on: Nov 26, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

int main() {
	int num;

	cin >> num;

	vector<int> v(num);
//	for (int i = num; i >= 1; i--) {
//		v[num - i] = i;
//	}
	iota(v.begin(), v.end(), 1);
	reverse(v.begin(), v.end());
	do {
		for (size_t i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
		cout << endl;
//	} while (next_permutation(v.begin(), v.end(),
//			[](const int a, const int b){
//				return (a >= b);
//			}));
	} while (prev_permutation(v.begin(), v.end()));

	return 0;
}



