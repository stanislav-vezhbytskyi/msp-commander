#pragma once
#include "idecoder.h"
#include "../../msp_payload_variant.h"

class AttitudeDecoder : public IDecoder {
public:
    MSPPayloadVariant decode(const std::vector<uint8_t>& payload) override;
};


