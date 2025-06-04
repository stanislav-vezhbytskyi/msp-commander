#include "attitude_decoder.h"

DecodedTypes AttitudeDecoder::decode(const std::vector<uint8_t> &payload) {
    MSP::ATTITUDE a;

    a.angx = payload[0] | (payload[1] << 8);
    a.angy = payload[2] | (payload[3] << 8);
    a.heading = payload[4] | (payload[5] << 8);

    return a;
}