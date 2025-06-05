#pragma once

#include <vector>
#include "../../msp_payload_variant.h"

class IDecoder {
public:
    virtual MSPPayloadVariant decode(const std::vector<uint8_t>& payload) = 0;
    virtual ~IDecoder() = default;
};



