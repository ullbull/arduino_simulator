//
// Created by UlrikKarlsson on 2021-10-27.
//

#ifndef TEST_ARDUINO_H
#define TEST_ARDUINO_H

#include<windows.h>     //using boolean = bool;
#include <cstdint>

using namespace std;
using byte = unsigned char;

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1

unsigned long millis();
void delay(int);

void pinMode(uint8_t pin, uint8_t mode);

int digitalRead(uint8_t pin);
void digitalWrite(uint8_t pin, uint8_t val);


class Serial
{
private:
public:
    Serial();
    static void begin(unsigned long);
    void end(void);

    static void print(const char *message);

    static void print(boolean message);

    static void print(int message);

    static void println(boolean message);

    static void println(const char *message);

    static void println(int message);


};
extern Serial Serial;


#endif //TEST_ARDUINO_H
