#pragma once
#include "idecoder.h"
#include "decoder/docoded_types.h"

class RawIMUDecoder : public IDecoder {
public:
    DecodedTypes decode(const std::vector<uint8_t>& payload) override;
};
