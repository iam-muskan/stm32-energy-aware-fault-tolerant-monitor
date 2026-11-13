#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

enum class Status { NORMAL, ABNORMAL, INVALID_DATA };

string label(Status s) {
   if (s == Status::NORMAL) return "NORMAL";
   if (s == Status::ABNORMAL) return "ABNORMAL";
   return "INVALID_DATA";
}

Status validate(double value, double low, double high) {
  if (!isfinite(value) || value < low || value > high)
     return Status::INVALID_DATA;
  return Status::NORMAL;
}

Status evaluateTemperature(double tempC) {
  if (!isfinite(tempC)) return Status::INVALID_DATA;
  if (tempC > 45 || tempC < 15) return Status::ABNORMAL;
  return Status::NORMAL;
}

int main() {
   struct Case { const char* name; double value; Status expected; };
   const vector<Case> cases = {
      {"High temperature", 60, Status::ABNORMAL},
      {"Invalid humidity", -10, Status::INVALID_DATA},
      {"High MQ135 raw", 3000, Status::ABNORMAL},
      {"Missing sensor", NAN, Status::INVALID_DATA},
      {"Out-of-range sensor value", 5000, Status::INVALID_DATA}
   };

    int passed = 0;
    for (const auto& c : cases) {
       Status actual;
       if (string(c.name) == "High temperature")
          actual = evaluateTemperature(c.value);
       else if (string(c.name) == "Invalid humidity" ||
              string(c.name) == "Missing sensor")
          actual = validate(c.value, 0, 100);
       else if (string(c.name) == "High MQ135 raw")
          actual = c.value > 1500 ? Status::ABNORMAL : Status::NORMAL;
       else
          actual = validate(c.value, 0, 4095);

      bool ok = actual == c.expected;
      passed += ok;
      cout << c.name << ": expected=" << label(c.expected)
         << ", actual=" << label(actual)
         << ", " << (ok ? "PASS" : "FAIL") << '\n';
    }
    cout << "Fault-injection tests passed: " << passed
       << "/" << cases.size() << '\n';
    return passed == (int)cases.size() ? 0 : 1;
}
