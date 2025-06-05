#pragma once
#include <cstdint>
#include <vector>

#include "msp_payload_variant.h"

class MSPRequestBuilder {
    std::vector<uint8_t> buildRequest(uint8_t command,const MSPPayloadVariant& v);
    ~MSPRequestBuilder();
};


