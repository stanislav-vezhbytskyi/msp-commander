#include "decoder_factory.h"

#include <memory>

#include "decoder_pid.h"

std::unique_ptr<IDecoder> create_decoder(uint8_t command) {
    switch (command) {

        case 1: return std::make_unique<DecoderPID>();

        default: return nullptr;
    }
}

