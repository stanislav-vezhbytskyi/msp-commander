#pragma once

#include <vector>
#include <cstdint>


namespace PayloadEncoder {
   std::vector<uint8_t> encodePayload(const MSPPayloadVariant& data) ;
}

