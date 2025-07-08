#pragma once
#include <cstdint>
#include <vector>

#include "msp/msp_payload_variant.h"


class PacketEncoder {
    static std::vector<uint8_t> encode(uint8_t cmdId, const MSPPayloadVariant& v);
};


