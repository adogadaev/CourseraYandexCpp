#include <iostream>
#include <stdexcept>
#include <string>

#include "database.h"
#include "date.h"
#include "condition_parser.h"
#include "node.h"
#include "test_runner.h"

using namespace std;

string ParseEvent(istream& is) {
    const string whitespace = " \t";
    const string quotes = "\"";
    string sEvent, sEventWsTrimmed;

    getline(is, sEvent);
    const auto strWsBegin = sEvent.find_first_not_of(whitespace);
    if (strWsBegin == string::npos) {
        return "";
    }
    sEventWsTrimmed = sEvent.substr(strWsBegin);
    const auto strQuotesBegin = sEventWsTrimmed.find_first_of(quotes);
    const auto strQuotesEnd = sEventWsTrimmed.find_last_of(quotes);
    if (strQuotesBegin == string::npos || (strQuotesEnd-strQuotesBegin) <= 1) {
        return sEventWsTrimmed;
    }
    const auto strQuotesRange = strQuotesEnd - strQuotesBegin - 1;

    return sEventWsTrimmed.substr(strQuotesBegin+1, strQuotesRange);
}

void ParseCommand(istream& is, Database& db) {
    string command;
    is >> command;
    if (command == "Add") {
        const auto date = ParseDate(is);
        const auto event = ParseEvent(is);
        db.Add(date, event);
    } else if (command == "Print") {
        db.Print(cout);
    } else if (command == "Del") {
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };
        int count = db.RemoveIf(predicate);
        cout << "Removed " << count << " entries" << endl;
    } else if (command == "Find") {
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date& date, const string& event) {
            return condition->Evaluate(date, event);
        };

        const auto entries = db.FindIf(predicate);
        for (const auto& entry : entries) {
            cout << entry << endl;
        }
        cout << "Found " << entries.size() << " entries" << endl;
    } else if (command == "Last") {
        try {
            cout << db.Last(ParseDate(is)) << endl;
        } catch (invalid_argument&) {
            cout << "No entries" << endl;
        }
    } else if (command.empty()) {
    } else {
        throw logic_error("Unknown command: " + command);
    }
}

void TestAll();

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line); ) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);
        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date& date, const string& event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto& entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument&) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}

void TestParseEvent() {
    {
        istringstream is("\"   sport event \"");
        AssertEqual(ParseEvent(is), "   sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("   \"sport event\" ");
        AssertEqual(ParseEvent(is), "sport event", "Parse event with leading spaces");
    }
    {
        istringstream is("   \"sport event \"");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("     ");
        AssertEqual(ParseEvent(is), "", "Parse spaces");
    }
    {
        istringstream is("");
        AssertEqual(ParseEvent(is), "", "Parse empty event");
    }
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

//void TestDatabase() {
//    {
//        Database db;
//        istringstream is("Add 2017-06-01 1st of June\n"
//                         "Add 2017-07-08 8th of July\n"
//                         "Add 2017-07-08 Someone's birthday\n"
//                         "Del date == 2017-07-08");
//        ParseCommand(is, db);
//        ParseCommand(is, db);
//        ParseCommand(is, db);
//        ParseCommand(is, db);
//
//        ostringstream outs;
//        db.Print(outs);
//        AssertEqual(outs.str(), "2017-06-01 1st of June\n", "Test Command Del");
//    }
//}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
//    tr.RunTest(TestDatabase, "TestDatabase");
}
