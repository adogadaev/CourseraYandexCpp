#include "test_runner.h"

#include <ostream>
#include <iostream>
using namespace std;

#define PRINT_VALUES(out, x, y) (out) << (x) << endl << (y) << endl

int main() {
  TestRunner tr;
  tr.RunTest([] {
    ostringstream output;
    PRINT_VALUES(output, 5, "red belt");
    ASSERT_EQUAL(output.str(), "5\nred belt\n");
  }, "PRINT_VALUES usage example");

  tr.RunTest([] {
      ostringstream output;
      PRINT_VALUES(output, 0-5, "red belt\n\\n");
      ASSERT_EQUAL(output.str(), "-5\nred belt\n\\n\n");
    }, "PRINT_VALUES usage example 2");

  PRINT_VALUES(std::cout, 0-5, "red belt\n\\n");

  return 0;
}
