#include "decoder/payload-decoders/pid_decoder.h"

#include <cstdint>

#include "msp_protocol.h"
#include "decoder/docoded_types.h"

DecodedTypes PIDDecoder::decode(const std::vector<uint8_t> &payload) {
    MSP::PID pid;

    pid.roll = payload[0];
    pid.pitch = payload[1];
    pid.yaw = payload[2];
    pid.alt = payload[3];
    pid.pos = payload[4];
    pid.posr = payload[5];
    pid.navr = payload[6];
    pid.level = payload[7];
    pid.mag = payload[8];
    pid.vel = payload[9];

    return pid;
}
