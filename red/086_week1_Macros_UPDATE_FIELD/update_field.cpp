#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;

std::ostream& operator<<(std::ostream& out, const Date& d) {
	return out << d.year << "-" << d.month << "-" << d.day;
}

std::istream& operator>>(std::istream& in, Date& d) {
	in >> d.year;
	in.ignore(1, '-');
	in >> d.month;
	in.ignore(1, '-');
	in >> d.day;
	return in;
}

bool operator==(const Date& l, const Date& r) {
  return std::tie(l.year, l.month, l.day) == std::tie(r.year, r.month, r.day);
}

std::ostream& operator<<(std::ostream& out, const Time& t) {
	return out << t.hours << ":" << t.minutes;
}

std::istream& operator>>(std::istream& in, Time& t) {
	in >> t.hours;
	in.ignore(1, ':');
	in >> t.minutes;
	return in;
}

bool operator==(const Time& l, const Time& r) {
  return std::tie(l.hours, l.minutes) == std::tie(r.hours, r.minutes);
}

#define UPDATE_FIELD(ticket, field, values) { \
	map<string, string>::const_iterator it;   \
	it = (values).find((#field));             \
	if (it != (values).end()) {               \
		istringstream is(it->second);         \
		is >> (ticket).field;                 \
	}                                         \
}

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
