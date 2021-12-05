#include <iostream>
#include <thread>
#include "Arduino.h"
#include "RF24.h"

#include "pumpSensor.h"
#include "pumpSensorReceiverUnit.h"

//using namespace sensor;
using namespace receiver;

bool run = true;
RF24 r(1,1);
enum class State {
    ok,
    lowPressure,
    noPumpActivity
};
State state;

void mainThreadFunction() {
    setup();
    while (run) {
        loop();
    }
}

void controlThreadFunction() {
    cout << "Press q to quit.\n";
    while (run) {
        if (GetKeyState('A') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
            state = State::ok;
            r.write(&state, 1);
            delay(300);
        }
        if (GetKeyState('S') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
            state = State::lowPressure;
            r.write(&state, 1);
            delay(300);
        }
        if (GetKeyState('D') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
            state = State::noPumpActivity;
            r.write(&state, 1);
            delay(300);
        }
        if (GetKeyState('Q') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
            run = false;
        }
        if (GetKeyState('2') & 0x8000/*Check if high-order bit is set (1 << 15)*/) {
            digitalWrite(2, HIGH);
        } else {
            digitalWrite(2, LOW);
        }

        Sleep(10);
    }

}

int main() {
    initMemory();
    std::thread controlThread(controlThreadFunction);
    Sleep(1000);
    std::thread mainThread(mainThreadFunction);

    mainThread.join();
    controlThread.join();
    return 0;
}
