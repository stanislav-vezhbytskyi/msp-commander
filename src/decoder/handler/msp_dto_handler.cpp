#include "decoder/handler/msp_dto_handler.h"

#include <iostream>

#include "../../../include/msp_payload_variant.h"
#include "decoder/forwarder/data_forwarder.h"
#include "decoder/payload-decoders/decoder_factory.h"
#include "dto/msp_dto.h"


void MspDtoHandler::handle(const MSPDTO& dto) {
    DecoderFactory decoderFactory;
    auto decoder = decoderFactory.create_decoder(dto.command);
    if (!decoder) {
        std::cout<<"invalid decoder ):"<<std::endl;
        return;
    }

    const MSPPayloadVariant data = decoder->decode(dto.payload);

    DataForwarder forwarder;
    forwarder.forward(data);
}

