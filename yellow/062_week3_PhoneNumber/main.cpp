/*
 * main.cpp
 *
 *  Created on: Nov 10, 2018
 *      Author: Anton Dogadaev
 */
#include "phone_number.h"
#include "test_runner.h"

void TestOk() {
	{
		PhoneNumber pn("+7-495-111-22-33");
		AssertEqual(pn.GetInternationalNumber(), "+7-495-111-22-33", "GetInternationalNumber");
		AssertEqual(pn.GetCountryCode(), "7", "GetCountryCode");
		AssertEqual(pn.GetCityCode(), "495", "GetCityCode");
		AssertEqual(pn.GetLocalNumber(), "111-22-33", "GetLocalNumber");
	}

	{
		PhoneNumber pn("+7-495-1112233");
		AssertEqual(pn.GetInternationalNumber(), "+7-495-1112233", "GetInternationalNumber");
		AssertEqual(pn.GetCountryCode(), "7", "GetCountryCode");
		AssertEqual(pn.GetCityCode(), "495", "GetCityCode");
		AssertEqual(pn.GetLocalNumber(), "1112233", "GetLocalNumber");
	}

	{
		PhoneNumber pn("+323-22-460002");
		AssertEqual(pn.GetInternationalNumber(), "+323-22-460002", "GetInternationalNumber");
		AssertEqual(pn.GetCountryCode(), "323", "GetCountryCode");
		AssertEqual(pn.GetCityCode(), "22", "GetCityCode");
		AssertEqual(pn.GetLocalNumber(), "460002", "GetLocalNumber");
	}

	{
		PhoneNumber pn("+1-2-coursera-cpp");
		AssertEqual(pn.GetInternationalNumber(), "+1-2-coursera-cpp", "GetInternationalNumber");
		AssertEqual(pn.GetCountryCode(), "1", "GetCountryCode");
		AssertEqual(pn.GetCityCode(), "2", "GetCityCode");
		AssertEqual(pn.GetLocalNumber(), "coursera-cpp", "GetLocalNumber");
	}
}

void TestWrongFormat() {
	{
		try {
			PhoneNumber pn("1-2-333");
			AssertEqual(pn.GetInternationalNumber(), "1-2-333", "GetInternationalNumber");
			AssertEqual(pn.GetCountryCode(), "1", "GetCountryCode");
			AssertEqual(pn.GetCityCode(), "2", "GetCityCode");
			AssertEqual(pn.GetLocalNumber(), "333", "GetLocalNumber");
			Assert(false, "no exception");
		} catch (invalid_argument& e) {
			cerr << e.what() << endl;
		}

		try {
			PhoneNumber pn("+7-1233");
			AssertEqual(pn.GetInternationalNumber(), "+7-1233", "GetInternationalNumber");
			AssertEqual(pn.GetCountryCode(), "7", "GetCountryCode");
			AssertEqual(pn.GetCityCode(), "1233", "GetCityCode");
			AssertEqual(pn.GetLocalNumber(), "", "GetLocalNumber");
			Assert(false, "no exception");
		} catch (invalid_argument& e) {
			cerr << e.what() << endl;
		}
	}
}

int main() {
	TestRunner tr;
	tr.RunTest(TestOk, "TestOk");
	tr.RunTest(TestWrongFormat, "TestWrongFormat");
	return 0;
}



