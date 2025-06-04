#pragma once
#include <cstdint>
#include <vector>

#include "idecoder.h"
#include "decoder/docoded_types.h"

class PIDDecoder : public IDecoder {
public:
    DecodedTypes decode(const std::vector<uint8_t>& payload) override;
};

