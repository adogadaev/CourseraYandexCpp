/*
 * main.cpp
 *
 *  Created on: Dec 9, 2018
 *      Author: Anton Dogadaev
 */
#include <iostream>
#include <vector>
#include <memory>
#include <string>
#include <iomanip>
#include <cmath>

using namespace std;

class Figure {
public:
	virtual string Name() const = 0;
	virtual double Perimeter() const = 0;
	virtual double Area() const = 0;
};

class Triangle : public Figure {
public:
	Triangle(int a, int b, int c) : _name("TRIANGLE") {
		_perimeter = a + b + c;
		_area = sqrt(_perimeter/2 * (_perimeter/2 - a) * (_perimeter/2 - b) *
					 (_perimeter/2 - c));
	}

	string Name() const override {
		return _name;
	}

	double Perimeter() const override {
		return _perimeter;
	}

	double Area() const override {
		return _area;
	}
private:
	string _name;
	double _perimeter;
	double _area;
};

class Rect : public Figure {
public:
	Rect(int width, int height) : _name("RECT") {
		_perimeter = 2 * (width + height);
		_area = width * height;
	}

	string Name() const override {
		return _name;
	}

	double Perimeter() const override {
		return _perimeter;
	}

	double Area() const override {
		return _area;
	}
private:
	string _name;
	double _perimeter;
	double _area;
};

class Circle : public Figure {
public:
	Circle(int r) : _name("CIRCLE") {
		_perimeter = 2 * 3.14 * r;
		_area = 3.14 * r * r;
	}

	string Name() const override {
		return _name;
	}

	double Perimeter() const override {
		return _perimeter;
	}

	double Area() const override {
		return _area;
	}
private:
	string _name;
	double _perimeter;
	double _area;
};

shared_ptr<Figure> CreateFigure(istream& is) {
	string fig_name;

	is >> fig_name;
	if (fig_name == "RECT") {
		int w, h;
		is >> w >> h;
		return make_shared<Rect>(w, h);
	} else if (fig_name == "TRIANGLE") {
		int a, b, c;
		is >> a >> b >> c;
		return make_shared<Triangle>(a, b, c);
	}

	int r;
	is >> r;
	return make_shared<Circle>(r);
}

int main() {
	vector<shared_ptr<Figure>> figures;
	for (string line; getline(cin, line); ) {
		istringstream is(line);

		string command;
		is >> command;
		if (command == "ADD") {
			figures.push_back(CreateFigure(is));
		} else if (command == "PRINT") {
			for (const auto& current_figure : figures) {
				cout << fixed << setprecision(3)
            				 << current_figure->Name() << " "
							 << current_figure->Perimeter() << " "
							 << current_figure->Area() << endl;
			}
		}
	}
	return 0;
}



