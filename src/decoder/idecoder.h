#pragma once

#include <any>
#include <cstdint>
#include <vector>

class IDecoder {
public:
    virtual std::any decode(const std::vector<uint8_t>& payload) = 0;
    virtual ~IDecoder() = default;
};



