#pragma once
#include <vector>

#include "msp_protocol.h"


class PIDEncoder {
    std::vector<uint8_t> encode(MSP::PID pid);
    ~PIDEncoder();
};



