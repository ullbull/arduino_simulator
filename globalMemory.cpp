//
// Created by UlrikKarlsson on 2021-11-18.
//

#include "globalMemory.h"

byte memory[20] = {'<'};
int memSize = 20;
int iWrite = 0;
int iRead = 0;

void initMemory() {
    for (int i = 0; i < memSize; ++i) {
        memory[i] = '<';
    }
}
