#include "../../include/mspcomm/msp_comm_service.h"

#include <iostream>

#include "msp/msp_protocol.h"

void MspCommService::requestAllSensorData( SerialPort& s) {

    if (!s.write(msp::GET_ATTITUDE, sizeof(msp::GET_ATTITUDE))) {
        std::cerr << "Failed to write to serial port\n";
        return;
    }
    if (! s.write(msp::GET_PID, sizeof(msp::GET_PID))){
        std::cerr << "Failed to write to serial port\n";
        return;
    }
    if (! s.write(msp::GET_RC, sizeof(msp::GET_RC))){
        std::cerr << "Failed to write to serial port\n";
        return;
    }
}
