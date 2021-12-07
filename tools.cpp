//
// Created by UlrikKarlsson on 2021-12-07.
//

#include "tools.h"
#include "Arduino.h"

void customBlinkLed(int pin, int numberOfBlinks, int onTime, int offTime) {
    int initialState = digitalRead(pin);
    for (int i = 0; i < numberOfBlinks; ++i) {
        digitalWrite(pin, 0);
        delay(offTime);
        digitalWrite(pin, 1);
        delay(onTime);
    }
    digitalWrite(pin, initialState);
}

void blinkLedPumpOn(int pin) {
    customBlinkLed(pin, 2, 250, 100);
}

void blinkLedPumpOff(int pin) {
    customBlinkLed(pin, 1, 500, 1);
}