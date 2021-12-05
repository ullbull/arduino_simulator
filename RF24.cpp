//
// Created by UlrikKarlsson on 2021-10-27.
//

#include <iostream>
#include "RF24.h"

RF24::RF24(int CE, int CSN) {
    this->CE = CE;
    this->CSN = CSN;
}

void RF24::begin() {
    std::cout << "RF24 begin.\n";
}

void RF24::openWritingPipe(const uint8_t* address) {
    std::cout << "Address: [";
    int length = 6;
    for (int i = 0; i < length; ++i) {
        std::cout << address[i];
        if (i < length -1) std::cout << ",";
    }
    std::cout << "]\n";
}

void RF24::openReadingPipe(uint8_t child, const uint8_t *address) {

}

void RF24::setPALevel(int level) {
    std::cout << "Setting PALevel to: " << level << std::endl;
}

void RF24::startListening() {
    std::cout << "RF24 start listening.\n";
}

void RF24::stopListening() {
    std::cout << "RF24 stop listening.\n";
}

bool RF24::available() {
    bool available = false;

    for (int i = 0; i < memSize; ++i) {
        available = (memory[iRead] != Null);
        if (available) break;
        iRead++;
        if (iRead >= memSize) iRead = 0;
    }

    return available;
}

bool RF24::write(const void* buf, uint8_t len){
    char *current = (char *) buf;

    cout << "Writing to RF24: ";
    for (int i = 0; i < len; ++i) {
        cout << current[i];
        memory[iWrite] = current[i];
        if (++iWrite >= memSize) iWrite = 0;
    }
//    memory[++iWrite] = '\n';
    cout << endl;

    return true;
}

void RF24::read(void *buf, uint8_t len) {
    auto* current = reinterpret_cast<uint8_t*>(buf);

    int i = 0;
    for (; i < len; ++i) {
        if (iRead >= memSize) iRead = 0;
        if (memory[iRead] == Null) break;
        current[i] = memory[iRead];
        memory[iRead] = Null;
        iRead++;
    }
    current[i] = '\0';
}

RF24::~RF24() = default;

