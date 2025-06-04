#pragma once
#include "idecoder.h"
#include "decoder/docoded_types.h"

class AttitudeDecoder : public IDecoder {
public:
    DecodedTypes decode(const std::vector<uint8_t>& payload) override;
};


