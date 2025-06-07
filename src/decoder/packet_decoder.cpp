#include "../../include/decoder/packet_decoder.h"

#include <iostream>

#include "../../include/msp_payload_variant.h"
#include "decoder/payload-decoders/decoder_factory.h"
#include "../../include/msp_dto.h"


MSPPayloadVariant PacketDecoder::decode(const MSPDTO& dto) {
    DecoderFactory decoderFactory;
    auto decoder = decoderFactory.create_decoder(dto.command);

    if (!decoder) {
        throw std::invalid_argument("invalid decoder");
    }

    return decoder->decode(dto.payload);
}

