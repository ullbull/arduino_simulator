cmake_minimum_required(VERSION 3.20)
project(test)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")

add_executable(test main.cpp Transiver.cpp Transiver.h RF24.cpp RF24.h Arduino.cpp Arduino.h pumpSensor.cpp pumpSensor.h pumpSensorReceiverUnit.cpp pumpSensorReceiverUnit.h SPI.h nRF24L01.h globalMemory.cpp globalMemory.h)
