#pragma once
#include "idecoder.h"
#include "decoder/docoded_types.h"

class StatusDecoder : public IDecoder {
    DecodedTypes decode(const std::vector<uint8_t>& payload) override;
};



