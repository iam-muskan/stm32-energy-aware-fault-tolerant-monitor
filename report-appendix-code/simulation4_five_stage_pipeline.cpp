#include <iostream>
#include <string>
using namespace std;
int main() {

    // Inputs represent one illustrative sensor snapshot.
    const int temperatureC = 40;
    const int mq135Raw = 900;
    int R1 = temperatureC;
    int R2 = mq135Raw;
    int R3 = 0, R4 = 0, R5 = 0;
    const char* stages[] = {"IF", "ID", "EX", "MEM", "WB"};
    const char* instructions[] = {
        "I1: LOAD R1, temperature",
        "I2: LOAD R2, MQ135",
        "I3: GT R3, R1, 35",
        "I4: GT R4, R2, 1500",
        "I5: OR R5, R3, R4"
    };
    // Simplified sequential trace; not cycle-accurate or overlapped.
    for (const char* stage : stages) {
        cout << "Stage " << stage << ":\n";
        for (const char* instruction : instructions)
           cout << " " << instruction << '\n';
    }
    // Execute the modeled operations in dependency order.
    R3 = (R1 > 35) ? 1 : 0;
    R4 = (R2 > 1500) ? 1 : 0;
    R5 = R3 | R4;
    cout << "\nFinal modeled registers:\n";
    cout << "R1 (temperature) = " << R1 << '\n';
    cout << "R2 (MQ135 raw) = " << R2 << '\n';
    cout << "R3 (temperature flag) = " << R3 << '\n';
    cout << "R4 (gas flag) = " << R4 << '\n';
    cout << "R5 (alarm flag) = " << R5 << '\n';
    cout << "Alarm: " << (R5 ? "ON" : "OFF") << '\n';
    return 0;
}
