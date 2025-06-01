#pragma once
#include "idecoder.h"
#include <memory>

std::unique_ptr<IDecoder> create_decoder(uint8_t command);