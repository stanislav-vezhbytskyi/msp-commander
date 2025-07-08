#include "../../include/mspcomm/msp_comm_service.h"

#include <iostream>

#include "msp/msp_protocol.h"
#include "plog/Log.h"

void MspCommService::requestAllSensorData( SerialPort& s) {

    send(s,msp::GET_ATTITUDE, sizeof(msp::GET_RC));
    send(s,msp::GET_PID, sizeof(msp::GET_RC));
    send(s,msp::GET_RC, sizeof(msp::GET_RC));
}

bool MspCommService::send(SerialPort& s, const uint8_t* cmd, size_t size) {
    if (!s.write(cmd, size)) {
        PLOGF << "Failed to write command " << static_cast<int>(cmd[0]) << "\n";
        return false;
    }
    return true;
}
