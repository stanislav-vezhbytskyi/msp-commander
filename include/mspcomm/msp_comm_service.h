#pragma once
#include "serial/SerialPort.h"

class MspCommService {
public:
    static void requestAllSensorData( SerialPort& s);
    static bool send(SerialPort& s, const uint8_t* cmd, size_t size);
};


