#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

string classify(double x) {
   if (!isfinite(x) || x < 0 || x > 100)
      return "INVALID_DATA";
   if (x < 20 || x > 80)
      return "ABNORMAL";
   return "NORMAL";
}

struct Test {
   double input;
   string expected;
};

int main() {
   const vector<Test> tests = {
      {50, "NORMAL"}, {20, "NORMAL"}, {80, "NORMAL"},
      {10, "ABNORMAL"}, {90, "ABNORMAL"},
      {-1, "INVALID_DATA"}, {101, "INVALID_DATA"},
      {NAN, "INVALID_DATA"}
   };

  int passed = 0;
  cout << "Software BIST\n";
  for (const auto& test : tests) {
     string actual = classify(test.input);
     bool ok = (actual == test.expected);

      passed += ok;
      cout << "Input=" << test.input
         << " Expected=" << test.expected
         << " Actual=" << actual
         << " Test=" << (ok ? "PASS" : "FAIL") << '\n';
    }
    cout << "BIST result: "
       << (passed == (int)tests.size() ? "PASS" : "FAIL")
       << " (" << passed << "/" << tests.size() << ")\n";
    return passed == (int)tests.size() ? 0 : 1;
}
