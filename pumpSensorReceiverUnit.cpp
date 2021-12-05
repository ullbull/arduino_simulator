//
// Created by UlrikKarlsson on 2021-11-12.
//

#include "pumpSensorReceiverUnit.h"

#include "Arduino.h"
#include <string>
#include "RF24.h"

namespace receiver {

    RF24 radio(9, 10);
    const byte address[6] = "00001";    //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
    int ledPinGreen = 3;
    int ledPinRed = 4;
    int ledPinYellow = 5;

    int ledPins[] = {
            ledPinGreen,
            ledPinRed,
            ledPinYellow
    };

    // Warn if no radio is received for this duration (milliseconds)
    unsigned long maxRadioReceiveInterval = 1000 * 5;

    enum class State {
        ok,
        lowPressure,
        noPumpActivity,
        noRadio,
    };
    State state;
    State lastState;

    void allLedsOff() {
        int length = sizeof(ledPins) / sizeof(ledPins[0]);
        for (int i = 0; i < length; ++i) {
            digitalWrite(ledPins[i], LOW);
        }
    }

    void setup() {
        pinMode(6, OUTPUT);
        Serial.begin(9600);
        radio.begin();

        //Setting the address at which we will receive the data
        radio.openReadingPipe(0, address);

        //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
        radio.setPALevel(RF24_PA_MIN);

        //S the module as receiver
        radio.startListening();
    }

    unsigned long currentTime = millis();
    unsigned long lastRadioReceiveTime = currentTime;
    unsigned long timeSinceLastRadioReceive;
    int ledPin = ledPinRed;

    void loop() {
        currentTime = millis();
        if (radio.available()) {
            lastRadioReceiveTime = millis();
            radio.read(&state, 1);
        }

        timeSinceLastRadioReceive = currentTime - lastRadioReceiveTime;
        if (timeSinceLastRadioReceive > maxRadioReceiveInterval) {
            state = State::noRadio;
        }

        if (state != lastState) {
            // State has changed!
            lastState = state;

            switch (state) {
                case State::ok: {
                    ledPin = ledPinGreen;
                    break;
                }
                case State::noRadio: {
                    ledPin = ledPinYellow;
                    break;
                }
                case State::lowPressure:
                case State::noPumpActivity: {
                    ledPin = ledPinRed;
                    break;
                }
            }

            allLedsOff();
            digitalWrite(ledPin, HIGH);

            Serial.print("ledPin: ");
            Serial.println(ledPin);
        }

        delay(5);
    }
}
