/*
 * main.cpp
 *
 *  Created on: Dec 2, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>

using namespace std;

class Animal {
public:
	Animal(const string& name) : Name(name) {}

	const string Name;
};


class Dog : public Animal {
public:
	Dog(const string& name) : Animal(name) {}

	void Bark() {
		cout << Name << " barks: woof!" << endl;
	}
};

int main() {
	Dog d("dog");
	d.Bark();
	return 0;
}



