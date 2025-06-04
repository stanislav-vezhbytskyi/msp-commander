#include <vector>

#include "msp_protocol.h"


class RCEncoder {
    std::vector<std::uint8_t> encode(MSP::RC rc);
    ~RCEncoder();
};

