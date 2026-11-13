#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

struct Sample {
   const char* id;
   double tempC, humidity, mq135;
};

string classify(const Sample& s) {
   if (!isfinite(s.tempC) || !isfinite(s.humidity) ||
      !isfinite(s.mq135) || s.humidity < 0 || s.humidity > 100 ||
      s.mq135 < 0) {
      return "INVALID_DATA";
   }
   if (s.tempC < 15 || s.tempC > 45 ||
      s.humidity < 30 || s.humidity > 70 ||
      s.mq135 > 1500) {
      return "ABNORMAL";
   }
   return "NORMAL";
}

int main() {
   const vector<Sample> tests = {
      {"S1", 25, 50, 900},
      {"S2", 39, 50, 900},
      {"S3", 25, 80, 900},
      {"S4", 25, 50, 2200},
      {"S5", 40, 85, 2800},
      {"S6", 46, 55, 1000}
   };

  cout << "Environmental Monitoring Simulation\n";
  for (const auto& s : tests) {
     cout << s.id << ": T=" << s.tempC

         << " C, RH=" << s.humidity
         << " %, MQ135=" << s.mq135
         << " -> " << classify(s) << '\n';
  }
  return 0;}
