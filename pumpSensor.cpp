//
// Created by UlrikKarlsson on 2021-11-04.
//

#include "pumpSensor.h"

#include "Arduino.h"
#include <string>

#include "SPI.h"
#include "nRF24L01.h"
#include "RF24.h"

namespace sensor {
    RF24 radio(9, 10);
    const byte address[6] = "00001";    //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
    int sensor_pin = 2;

    unsigned long lastPumpToggleTime;
    unsigned long lastTransmitTime;

//                                    sec   m h d
    unsigned int pumpToggleMinInterval = 1000 * 5;

//                                    sec   m h d
    unsigned int pumpToggleMaxInterval = 1000 * 20;

    int transmitInterval = 1000 * 2;
    boolean pumpIsToggled = false;

    std::string message = "State unknown";

    enum class State {
        ok,
        lowPressure,
        noPumpActivity
    };

    State state = State::noPumpActivity;

    void setup() {
        pinMode(sensor_pin, INPUT);
        Serial.begin(9600);
        radio.begin();
        radio.openWritingPipe(address);
        radio.setPALevel(RF24_PA_MIN);
        radio.stopListening();

        lastPumpToggleTime = millis();
        lastTransmitTime = millis();
    }

    unsigned long currentTime;
    unsigned int timeSinceLastPumpToggle;
    unsigned int timeSinceLastTransmit;
    boolean alert = true;
    unsigned int errorToggles = 0;

    void loop() {

        currentTime = millis();
        timeSinceLastPumpToggle = currentTime - lastPumpToggleTime;
        timeSinceLastTransmit = currentTime - lastTransmitTime;
        pumpIsToggled = digitalRead(sensor_pin);

        if (timeSinceLastPumpToggle > pumpToggleMaxInterval) {
            if (alert) {
                alert = false;
                message = "No pump activity!";
                state = State::noPumpActivity;
                Serial.println(message.c_str());
            }
        } else {
            alert = true;
        }

        if (pumpIsToggled) {
            lastPumpToggleTime = currentTime;
            Serial.println("Pump is toggled!");

            if (timeSinceLastPumpToggle < pumpToggleMinInterval) {
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

        // Send status at a fixed interval
        if (timeSinceLastTransmit >= transmitInterval) {
            lastTransmitTime = currentTime;
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