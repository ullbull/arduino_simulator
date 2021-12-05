//
// Created by UlrikKarlsson on 2021-10-27.
//

#include "Transiver.h"
#include "Arduino.h"
#include <iostream>

using namespace std;

Transiver::Transiver(int CE, int CSN) {
//    std::cout << "Transiver constructor\n";
    this->time = millis();

    this->CE = CE;
    this->CSN = CSN;
}

Transiver::~Transiver() {
//    std::cout << "Transiver destructor\n";
}

void Transiver::setAddress() {

}

void Transiver::setPALevel() {

}

void Transiver::setAsTransmitter() {

}

void Transiver::setAsReceiver() {

}

void Transiver::send(int message) {
    cout << "int" << endl;
    cout << "sending: " << message << endl;
}

void Transiver::send(bool state) {
    cout << "bool" << endl;
    cout << "sending: " << state << endl;
}

bool Transiver::receive(int timeout) {
    unsigned long startTime = millis();
    while (true) {
        if (millis() - this->time > 3000) {
            this->time = millis();
            return true;
        } else if (millis() - startTime > timeout) {
            cout << "timeout" << endl;
            return false;
        }
    }
}
