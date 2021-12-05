//
// Created by UlrikKarlsson on 2021-10-27.
//

#include "Arduino.h"
#include <chrono>
//#include <sys/time.h>
#include <ctime>
//#include <windows.h>
#include <iostream>

using namespace std::chrono;

uint8_t gpio[13] = {LOW};

unsigned long millis(){
    // static int millis = 0;
    // return millis ++;

    // time_t now = time(nullptr);
    // return now * 1000;

    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    auto sec_since_epoch = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();

    // cout << "seconds since epoch: " << sec_since_epoch << endl;
    // cout << "milliseconds since epoch: " << millisec_since_epoch << endl;

    return millisec_since_epoch;
}

void delay(int millis) {
    Sleep(millis);
}

void pinMode(uint8_t pin, uint8_t mode){

}


int digitalRead(uint8_t pin) {
    return gpio[pin];
}

void digitalWrite(uint8_t pin, uint8_t val) {
    gpio[pin] = val;
}

Serial::Serial() {
    ;
}

void Serial::begin(unsigned long baudrate) {
    std::cout << "Serial begin " << baudrate << endl;
}

void Serial::print(const char *message){
    std::cout << message;
}
void Serial::print(boolean message){
    std::cout << (bool)message;
}
void Serial::print(int message) {
    std::cout << message;
}

void Serial::println(const char *message){
    print(message); std::cout << std::endl;
}
void Serial::println(boolean message){
    print(message); std::cout << std::endl;
}
void Serial::println(int message) {
    print(message); std::cout << std::endl;
}
