#pragma once

#include <vector>
#include <cstdint>


namespace payload_encoder {
   std::vector<uint8_t> encodePayload(const MSPPayloadVariant& data) ;
}

