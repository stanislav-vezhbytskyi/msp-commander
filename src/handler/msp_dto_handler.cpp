#include "msp_dto_handler.h"

#include <iostream>

#include "../decoder/attitude_decoder.h"
#include "../decoder/decoder_factory.h"
#include "../decoder/pid_decoder.h"
#include "../decoder/raw_imu_decoder.h"
#include "../decoder/rc_decoder.h"
#include "../decoder/status_decoder.h"
#include "../forwarder/idata_forwarder.h"

void MspDtoHandler::handle(const MSPDTO& dto) {
    auto decoder = create_decoder(dto.command);
    if (!decoder) {
        std::cout<<"invalid decoder ):"<<std::endl;
        return;
    }

    const DecodedTypes data = decoder->decode(dto.payload);

    DataForwarder forwarder;
    forwarder.forward(data);
}

std::unique_ptr<IDecoder> MspDtoHandler::create_decoder(uint8_t command) {
    switch (command) {
        case MSP::MessageID::PID:
            return std::make_unique<PIDDecoder>();
        case MSP::MessageID::STATUS:
            return std::make_unique<StatusDecoder>();
        case MSP::MessageID::RAW_IMU:
            return std::make_unique<RawIMUDecoder>();
        case MSP::MessageID::ATTITUDE:
            return std::make_unique<AttitudeDecoder>();
        case MSP::MessageID::RC:
            return std::make_unique<RCDecoder>();
        default:
            return nullptr;
    }
}