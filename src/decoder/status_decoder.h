
#pragma once
#include "idecoder.h"

class StatusDecoder : public IDecoder {
    DecodedTypes decode(const std::vector<uint8_t>& payload) override;
};



