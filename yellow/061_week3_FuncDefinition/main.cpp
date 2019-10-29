/*
 * main.cpp
 *
 *  Created on: Nov 10, 2018
 *      Author: Anton Dogadaev
 */

#include "sum_reverse_sort.h"
#include "test_runner.h"

void TestSum() {
	AssertEqual(Sum(5, 6), 11, "Sum test");
}

void TestReverse() {
	AssertEqual(Reverse("abcde"), "edcba", "Reverse test");
}

void TestSort() {
	vector<int> testv = {4, 2, 6, 3, 1, 2, 6};
	Sort(testv);
	vector<int> answer = {1, 2, 2, 3, 4, 6, 6};
	AssertEqual(testv, answer, "Sort test");
}

int main() {
	TestRunner runner;
	runner.RunTest(TestSum, "Sum test");
	runner.RunTest(TestReverse, "Reverse test");
	runner.RunTest(TestSort, "Sort test");
	return 0;
}


