//
// Created by UlrikKarlsson on 2021-11-04.
//

#include "pumpSensor.h"

#include "Arduino.h"
#include <string>

#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "tools.h"

namespace sensor {
    RF24 radio(9, 10);
    const byte address[6] = "00001";    //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
    int pumpSwitchPin = 2;
    int ledRedPin = 5;

    bool pumpIsOn = false;

    unsigned long timeAtPumpOn;
    unsigned long timeAtPumpOff;
    unsigned long timeAtLastTransmit;

//                                    sec   m h d
    unsigned int pumpToggleMinInterval = 1000 * 5;

//                                    sec   m h d
    unsigned int pumpMaxOffTime = 1000 * 20;

    int transmitInterval = 1000 * 2;
    boolean pumpIsToggled = false;
    int newPumpState = 0;

    std::string message = "State unknown";

    enum class State {
        ok,
        lowPressure,
        noPumpActivity,
        blinkLedOn,
        blinkLedOff
    };

    State state = State::noPumpActivity;
    State extra;


    void setup() {
        pinMode(pumpSwitchPin, INPUT);
        Serial.begin(9600);
        radio.begin();
        radio.openWritingPipe(address);
        radio.setPALevel(RF24_PA_MIN);
        radio.stopListening();

        timeAtPumpOn = millis();
        timeAtPumpOff = millis();
        timeAtLastTransmit = millis();
        pumpIsOn = digitalRead(pumpSwitchPin);
    }

    unsigned long currentTime;
    unsigned int timeSinceLastPumpOn = 0;
    unsigned int timeSinceLastPumpOff = 0;
    unsigned int timeSinceLastTransmit = 0;
    boolean readyToAlert = true;
    unsigned int errorToggles = 0;

    void loop() {
        currentTime = millis();
        newPumpState = digitalRead(pumpSwitchPin);

        if (pumpIsOn) {
            if (newPumpState == 0) {
                // The pump was toggled off now
                pumpIsOn = false;
                timeAtPumpOff = currentTime;
                Serial.println("Pump is off!");
                blinkLedPumpOff(ledRedPin);
                extra = State::blinkLedOff;
                radio.write(&extra, 1);
            }
        } else {    // Pump is off
            if (newPumpState == 1) {
                // The pump was toggled on now
                pumpIsOn = true;
                timeAtPumpOn = currentTime;
                Serial.println("Pump is on!");
                blinkLedPumpOn(ledRedPin);
                extra = State::blinkLedOn;
                radio.write(&extra, 1);

                if (timeSinceLastPumpOn < pumpToggleMinInterval) {
                    // Pump toggles too often.
                    errorToggles++;
                    if (errorToggles >= 2) {
                        message = "Low pressure";
                        state = State::lowPressure;

                    }
                } else {
                    message = "ok";
                    state = State::ok;
                    errorToggles = 0;
                }

                Serial.print("errorToggles = ");
                Serial.println((int) errorToggles);
                delay(500);

            }
        }

        timeSinceLastPumpOn = currentTime - timeAtPumpOn;
        timeSinceLastPumpOff = currentTime - timeAtPumpOff;
        timeSinceLastTransmit = currentTime - timeAtLastTransmit;

        if (timeSinceLastPumpOn > pumpMaxOffTime) {
            if (readyToAlert) {
                readyToAlert = false;
                message = "No pump activity!";
                state = State::noPumpActivity;
                Serial.println(message.c_str());
            }
        } else {
            readyToAlert = true;
        }

        // Send status at a fixed interval
        if (timeSinceLastTransmit >= transmitInterval) {
            timeAtLastTransmit = currentTime;
            radio.write(message.c_str(), message.size());
            radio.write(&state, 1);
        }

        if (radio.available()) {
            char text[32] = "";
            radio.read(&text, sizeof(text));
            Serial.print("Read: ");
            Serial.println(text);
        }

        delay(10);
    }
}