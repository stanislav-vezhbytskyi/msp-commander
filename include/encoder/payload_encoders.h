#pragma once

#include <vector>
#include <cstdint>

#include "msp_payload_variant.h"
#include "msp_protocol.h"

namespace PayloadEncoders {
    std::vector<uint8_t> encodePayload(const MSPPayloadVariant& data);
}

