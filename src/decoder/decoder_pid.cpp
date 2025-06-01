#include "decoder_pid.h"
#include <cstdint>
#include "msp_protocol.h"

std::any DecoderPID::decode(const std::vector<uint8_t>& payload){
    std::vector<MSP::PID> pids;

    for (int i = 0; i < payload.size(); i+=3) {
        uint8_t p = payload[i];
        uint8_t ii = payload[i+1];
        uint8_t d = payload[i+2];

        pids.push_back(MSP::PID{p,ii,d});
    }

    return pids;
}
