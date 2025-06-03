#pragma once
#include <any>
#include <cstdint>
#include <vector>

#include "idecoder.h"

class PIDDecoder : public IDecoder {
public:
    DecodedTypes decode(const std::vector<uint8_t>& payload) override;
};

