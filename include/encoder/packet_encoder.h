#pragma once
#include <cstdint>
#include <vector>

#include "msp_payload_variant.h"

class PacketEncoder {
    static std::vector<uint8_t> encode(uint8_t command, const MSPPayloadVariant& v);
};


