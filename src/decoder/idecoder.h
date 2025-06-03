#pragma once

#include <any>
#include <cstdint>
#include <vector>

#include "docoded_types.h"

class IDecoder {
public:
    virtual DecodedTypes decode(const std::vector<uint8_t>& payload) = 0;
    virtual ~IDecoder() = default;
};



