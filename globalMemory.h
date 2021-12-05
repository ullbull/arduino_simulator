//
// Created by UlrikKarlsson on 2021-11-18.
//

#ifndef TEST_GLOBALMEMORY_H
#define TEST_GLOBALMEMORY_H

#include "Arduino.h"

extern byte memory[20];
extern int memSize;
extern int iWrite;
extern int iRead;

void initMemory();

#endif //TEST_GLOBALMEMORY_H
