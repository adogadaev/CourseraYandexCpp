/*
 * database.cpp
 *
 *  Created on: Dec 18, 2018
 *      Author: Anton Dogadaev
 */
#include "database.h"

#include "condition_parser.h"

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <algorithm>

void Database::Add(Date d, string ev) {
    if (db_uniqueness.count(d) > 0 && db_uniqueness.at(d).count(ev) > 0) {
        return;
    }
    db_uniqueness[d].insert(ev);
    db_order[d].push_back(ev);
    if (db_uniqueness[d].size() != db_order[d].size()) {
        throw logic_error("Database::Add: DB sizes do not match.");
    }
}

ostream& Database::Print(ostream& out) const {
    if (db_order.size() != 0) {
        for (const auto& EventsInDay : db_order) {
            if (db_uniqueness.at(EventsInDay.first).size() !=
                    db_order.at(EventsInDay.first).size()) {
                throw logic_error("Database::Print: DB sizes do not match.");
            }
            for (const auto& event : EventsInDay.second) {
                out << setw(4) << setfill('0') << EventsInDay.first.GetYear() << '-';
                out << setw(2) << setfill('0') << EventsInDay.first.GetMonth() << '-';
                out << setw(2) << setfill('0') << EventsInDay.first.GetDay() << ' ';
                out << event << endl;
            }
        }
    } else {
        out << endl;
    }

    return out;
}

int Database::RemoveIf(PredicateFn predicate) {
    vector<pair<Date, string>> db_del = FindIf(predicate);
    int events = 0;
    for (const auto& DayEventPair : db_del) {
        if (DeleteEvent(DayEventPair.first, DayEventPair.second) == false) {
            throw logic_error("No entry to delete");
        }
        events++;
    }
    return events;
}

bool Database::DeleteEvent(const Date& date, const string& event) {
    if (db_uniqueness.count(date) > 0 && db_uniqueness.at(date).count(event) > 0) {
        db_uniqueness.at(date).erase(event);
        db_order.at(date).erase(std::remove(db_order.at(date).begin(),
                                            db_order.at(date).end(), event),
                                db_order.at(date).end());
        if (db_uniqueness.at(date).size() == 0) {
            db_uniqueness.erase(date);
            db_order.erase(date);
        }
        return true;
    }
    return false;
}

//int Database::DeleteDate(const Date& date) {
//    int events = 0;
//    if (db_uniqueness.count(date) > 0) {
//        events = db_uniqueness.at(date).size();
//    }
//    db_uniqueness.erase(date);
//    db_order.erase(date);
//    return events;
//}

vector<pair<Date, string>> Database::FindIf(PredicateFn predicate) const {
    vector<pair<Date, string>> result;
    for (const auto& EventsInDay : db_order) {
        for (const auto& event : EventsInDay.second) {
            if (predicate(EventsInDay.first, event)) {
                result.push_back(make_pair(EventsInDay.first, event));
            }
        }
    }
    return result;
}

pair<Date, string> Database::Last(Date d) const {
//    string line = "date <= " + to_string(d.GetYear()) + "-" +
//                  to_string(d.GetMonth()) + "-" + to_string(d.GetDay());
//    istringstream is(line);
//    auto condition = ParseCondition(is);
//    auto predicate = [condition](const Date& date, const string& event) {
//        return condition->Evaluate(date, event);
//    };
//    const auto entries = FindIf(predicate);
//    const size_t entries_size = entries.size();
//    if (entries_size == 0) {
//        throw invalid_argument("Database::Last: No entries");
//    }
//    return entries[entries_size - 1];
    const auto iter_gr = db_order.upper_bound(d);
    if (iter_gr == db_order.begin()) {
        throw invalid_argument("Database::Last: No entries");
    }
    const auto iter_last = prev(iter_gr);
    return {iter_last->first, iter_last->second.back()};
}

ostream& operator<<(ostream& out, const pair<Date, string>& p) {
    return out << p.first << " " << p.second;
}

ostream& operator<<(ostream& out, const pair<Date, deque<string>>& p) {
    bool multiline = false;
    for (const auto& event : p.second) {
        if (multiline) {
            out << endl;
        }
        out << p.first << " " << event;
        multiline = true;
    }
    return out;
}

