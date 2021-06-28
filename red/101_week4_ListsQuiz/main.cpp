#include <iostream>
#include <list>

using namespace std;

int main() {
	list<int> mylist;

	// set some initial values:
	for (int i=1; i<=10; ++i)
		mylist.push_back(i);

	for (const auto& el : mylist)
		cout << el << " ";
	cout << "\n";

	auto it1 = next(mylist.begin(), 2);
	auto it2 = next(mylist.begin(), 7);
	cout << *it1 << " " << *it2 << "\n";

	auto tmp_it = next(it2);
	mylist.splice(it1, mylist, it2);
	mylist.splice(tmp_it, mylist, it1);

	for (const auto& el : mylist)
		cout << el << " ";
	cout << "\n";
	cout << *it1 << " " << *it2 << "\n";
}
