/*
 * test_runner.cpp
 *
 *  Created on: Dec 25, 2018
 *      Author: Anton Dogadaev
 */
#include "test_runner.h"

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}



