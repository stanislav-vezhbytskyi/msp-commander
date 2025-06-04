#pragma once
#include <vector>

#include "msp_protocol.h"


class AttitudeEncoder {
    std::vector<uint8_t> encode(MSP::ATTITUDE a);
    ~AttitudeEncoder();
};
