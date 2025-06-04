#pragma once


#include <vector>

#include "msp_protocol.h"
class StatusEncoder {
    std::vector<std::uint8_t> encode(MSP::STATUS s);
    ~StatusEncoder();
};

