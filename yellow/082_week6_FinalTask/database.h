/*
 * database.h
 *
 *  Created on: Dec 18, 2018
 *      Author: Anton Dogadaev
 */

#pragma once

#include <string>
#include <ostream>
#include <functional>
#include <map>
#include <utility>
#include <set>
#include <deque>
#include <vector>

#include "date.h"

using namespace std;

using PredicateFn = std::function<bool(const Date&, const string&)>;

class Database {
public:
    void Add(Date d, string ev);
    ostream& Print(ostream& out) const;
    int RemoveIf(PredicateFn predicate);
    vector<pair<Date, string>> FindIf(PredicateFn predicate) const;
    pair<Date, string> Last(Date d) const;
private:
    bool DeleteEvent(const Date& date, const string& event);
//    int  DeleteDate(const Date& date);

    map<Date, set<string>> db_uniqueness;
    map<Date, deque<string>> db_order;
};

ostream& operator<<(ostream& out, const pair<Date, string>& p);
ostream& operator<<(ostream& out, const pair<Date, deque<string>>& p);
