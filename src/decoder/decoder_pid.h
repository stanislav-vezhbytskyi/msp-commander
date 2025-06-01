#pragma once
#include <any>
#include <cstdint>
#include <vector>

#include "idecoder.h"

class DecoderPID : public IDecoder {
public:
    std::any decode(const std::vector<uint8_t>& payload) override;
};

