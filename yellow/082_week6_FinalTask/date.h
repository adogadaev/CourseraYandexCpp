/*
 * date.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Anton Dogadaev
 */

#pragma once

#include <string>
#include <stdexcept>

using namespace std;

class Date {
public:
    Date();
    Date(int year, int month, int day);

    int GetYear() const;
    int GetMonth() const;
    int GetDay() const;
private:
    int y_;
    int m_;
    int d_;

    void checkStrFormat(string str);
    void checkYearFormat(int year);
    void checkMonthFormat(int month);
    void checkDayFormat(int day);
};

ostream& operator<<(ostream& out, const Date& d);
bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);
Date ParseDate(istream& is);

