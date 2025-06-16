#pragma once
#include "serial/SerialPort.h"

class MspCommService {
public:
    void requestAllSensorData( SerialPort& s);
};


