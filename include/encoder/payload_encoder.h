#pragma once

#include <vector>
#include <cstdint>

#include "msp_payload_variant.h"

namespace PayloadEncoder {
   std::vector<uint8_t> encodePayload(const MSPPayloadVariant& data) ;
}

