#pragma once
#include <cstdint>
#include <vector>

#include "idecoder.h"
#include "../../msp_payload_variant.h"

class PIDDecoder : public IDecoder {
public:
    MSPPayloadVariant decode(const std::vector<uint8_t>& payload) override;
};

