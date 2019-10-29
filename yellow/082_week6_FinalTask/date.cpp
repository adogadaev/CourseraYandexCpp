/*
 * date.cpp
 *
 *  Created on: Dec 18, 2018
 *      Author: Anton Dogadaev
 */
#include "date.h"

#include <iomanip>

Date::Date() : y_(0), m_(0), d_(0) {}

Date::Date(int year, int month, int day) {
    checkYearFormat(year);
    y_ = year;
    checkMonthFormat(month);
    m_ = month;
    checkDayFormat(day);
    d_ = day;
}

int Date::GetYear() const {
    return y_;
}

int Date::GetMonth() const {
    return m_;
}

int Date::GetDay() const {
    return d_;
}

void Date::checkStrFormat(string str) {
    int nums_registered = 0;
    const char delim = '-';
    bool neg_sign_detected = false;
    bool recording_digits = false;
    for (size_t i = 0; i < str.length(); i++) {
        if (str[i] == delim && neg_sign_detected == false && recording_digits == false) {
            neg_sign_detected = true;
        } else if (isdigit(str[i]) != 0 && recording_digits == false) {
            recording_digits = true;
        } else if (str[i] == delim && recording_digits == true) {
            neg_sign_detected = false;
            recording_digits = false;
            nums_registered++;
        } else if (isdigit(str[i]) == 0) {
            throw invalid_argument("Wrong date format: " + str);
        }

    }
    if (nums_registered != 2 || recording_digits == false) {
        throw invalid_argument("Wrong date format: " + str);
    }
}

void Date::checkYearFormat(int year) {
    if (year < 0 || year > 9999) {
        throw invalid_argument("Year value is invalid: " + to_string(year));
    }
}

void Date::checkMonthFormat(int month) {
    if (month < 1 || month > 12) {
        throw invalid_argument("Month value is invalid: " + to_string(month));
    }
}

void Date::checkDayFormat(int day) {
    if (day < 1 || day > 31) {
        throw invalid_argument("Day value is invalid: " + to_string(day));
    }
}

ostream& operator<<(ostream& out, const Date& d) {
    return out << setw(4) << setfill('0') << d.GetYear() << "-"
               << setw(2) << setfill('0') << d.GetMonth() << "-"
               << setw(2) << setfill('0') << d.GetDay();
}

Date ParseDate(istream& is) {
    string sDate;

    if (is >> sDate) {
        int nums_registered = 0;
        const char delim = '-';
        bool neg_sign_detected = false;
        bool recording_digits = false;
        for (size_t i = 0; i < sDate.length(); i++) {
            if (sDate[i] == delim && neg_sign_detected == false && recording_digits == false) {
                neg_sign_detected = true;
            } else if (isdigit(sDate[i]) != 0 && recording_digits == false) {
                recording_digits = true;
            } else if (sDate[i] == delim && recording_digits == true) {
                neg_sign_detected = false;
                recording_digits = false;
                nums_registered++;
            } else if (isdigit(sDate[i]) == 0) {
                throw invalid_argument("Wrong date format: " + sDate);
            }
        }
        if (nums_registered != 2 || recording_digits == false) {
            throw invalid_argument("Wrong date format: " + sDate);
        }

        int year, month, day;
        char c;
        stringstream ss(sDate);
        if (ss >> year && (ss >> c && c == delim) &&
                ss >> month && (ss >> c && c == delim) &&
                ss >> day) {
            return Date(year, month, day);
        } else {
            throw invalid_argument("Wrong date format: " + sDate);
        }
    }
    throw invalid_argument("Cannot read date from input stream");
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() < rhs.GetYear()) {
        return true;
    } else if (lhs.GetYear() == rhs.GetYear() &&
            lhs.GetMonth() < rhs.GetMonth()) {
        return true;
    } else if (lhs.GetYear() == rhs.GetYear() &&
            lhs.GetMonth() == rhs.GetMonth() &&
            lhs.GetDay() < rhs.GetDay()) {
        return true;
    }
    return false;
}

bool operator<=(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() < rhs.GetYear()) {
        return true;
    } else if (lhs.GetYear() == rhs.GetYear() &&
            lhs.GetMonth() < rhs.GetMonth()) {
        return true;
    } else if (lhs.GetYear() == rhs.GetYear() &&
            lhs.GetMonth() == rhs.GetMonth() &&
            lhs.GetDay() <= rhs.GetDay()) {
        return true;
    }
    return false;
}

bool operator==(const Date& lhs, const Date& rhs) {
    return (lhs.GetYear() == rhs.GetYear() &&
            lhs.GetMonth() == rhs.GetMonth() &&
            lhs.GetDay() == rhs.GetDay());
}

bool operator!=(const Date& lhs, const Date& rhs) {
    return !(lhs == rhs);
}

bool operator>=(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs);
}

bool operator>(const Date& lhs, const Date& rhs) {
    return !(lhs < rhs || lhs == rhs);
}




