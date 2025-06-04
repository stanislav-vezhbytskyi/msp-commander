#pragma once
#include "idecoder.h"

class AttitudeDecoder : public IDecoder {
public:
    DecodedTypes decode(const std::vector<uint8_t>& payload) override;
};


