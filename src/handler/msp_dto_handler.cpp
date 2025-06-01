#include "msp_dto_handler.h"
#include "../decoder/decoder_factory.h"
#include "../forwarder/pid_forwarder.h"

void MspDtoHandler::handle(const MSPDTO& dto) {
    auto decoder = create_decoder(dto.command);
    if (!decoder) {
        // лог або виняток
        return;
    }

    auto data = decoder->decode(dto.payload);

    PIDForwarder forwarder;
    forwarder.forward(data);
}
