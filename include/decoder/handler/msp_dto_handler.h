#pragma once
#include <memory>
#include "dto/msp_dto.h"

class IDecoder;

class MspDtoHandler {
public:
    void handle(const MSPDTO& dto);
private:
    std::unique_ptr<IDecoder> create_decoder(uint8_t command);
};
