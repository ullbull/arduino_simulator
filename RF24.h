//
// Created by UlrikKarlsson on 2021-10-27.
//

#ifndef TEST_RF24_H
#define TEST_RF24_H
#include "Arduino.h"
#include "globalMemory.h"

const int RF24_PA_MIN = 1;
const char Null = '<';

class RF24 {
private:
    int CE {};
    int CSN {};
    byte address[6];
//    byte memory[500] = {'\0'};
//    int memSize = 500;
//    int iWrite = 0;
//    int iRead = 0;

public:
    RF24(int CE, int CSN);
    ~RF24();

    void begin();
    void openWritingPipe(const uint8_t* address);
    void openReadingPipe(uint8_t child, const uint8_t* address);
    void setPALevel(int level);
    void startListening();
    void stopListening();
    bool write(const void* buf, uint8_t len);
    bool available();
    void read(void* buf, uint8_t len);
};


#endif //TEST_RF24_H
