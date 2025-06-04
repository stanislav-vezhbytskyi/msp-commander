#pragma once
#include <vector>

#include "msp_protocol.h"

class RawIMUEncoder {
    std::vector<uint8_t> encode(MSP::RawIMU r);
    ~RawIMUEncoder();
};

