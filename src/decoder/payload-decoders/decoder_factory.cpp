#include "decoder/payload-decoders/decoder_factory.h"

#include <memory>

#include "msp_protocol.h"
#include "decoder/payload-decoders/attitude_decoder.h"
#include "decoder/payload-decoders/pid_decoder.h"
#include "decoder/payload-decoders/raw_imu_decoder.h"
#include "decoder/payload-decoders/rc_decoder.h"
#include "decoder/payload-decoders/status_decoder.h"


class IDecoder;

std::unique_ptr<IDecoder> DecoderFactory::create_decoder(uint8_t command) {
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

