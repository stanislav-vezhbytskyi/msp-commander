#pragma once
#include "idecoder.h"
#include <memory>

class DecoderFactory {
public:
  virtual ~DecoderFactory() = default;
  virtual  std::unique_ptr<IDecoder> create_decoder(uint8_t command);
};