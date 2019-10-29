/*
 * main.cpp
 *
 *  Created on: Oct 18, 2018
 *      Author: Anton Dogadaev
 */
#include <string>

using namespace std;

struct Specialization {
	string val;
	explicit Specialization(string v) : val(v) {}
};

struct Course {
	string val;
	explicit Course(string v) : val(v) {}
};

struct Week {
	string val;
	explicit Week(string v) : val(v) {}
};

struct LectureTitle {
	string specialization;
	string course;
	string week;

	LectureTitle(Specialization s, Course c, Week w) :
		specialization(s.val), course(c.val), week(w.val) {}
};

//int main() {
//	LectureTitle title(
//			Specialization("C++"),
//			Course("White belt"),
//			Week("4th")
//	);
//
//	return 0;
//}


