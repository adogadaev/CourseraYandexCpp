/*
 * main.cpp
 *
 *  Created on: Oct 17, 2018
 *      Author: Anton Dogadaev
 */
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class SortedStrings {
public:
  void AddString(const string& s) {
	  // добавить строку s в набор
	  vSortedStrings.push_back(s);
	  sort(vSortedStrings.begin(), vSortedStrings.end());
  }
  vector<string> GetSortedStrings() {
	  // получить набор из всех добавленных строк в отсортированном порядке
	  return vSortedStrings;
  }
private:
  // приватные поля
  vector<string> vSortedStrings;
};

//void PrintSortedStrings(SortedStrings& strings) {
//  for (const string& s : strings.GetSortedStrings()) {
//    cout << s << " ";
//  }
//  cout << endl;
//}
//
//int main() {
//  SortedStrings strings;
//
//  strings.AddString("first");
//  strings.AddString("third");
//  strings.AddString("second");
//  PrintSortedStrings(strings);
//
//  strings.AddString("second");
//  PrintSortedStrings(strings);
//
//  return 0;
//}
//
