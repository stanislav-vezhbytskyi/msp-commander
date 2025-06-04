#include "../../../include/encoder/payload-encoders/attitude_encoder.h"

std::vector<uint8_t> AttitudeEncoder::encode(MSP::ATTITUDE a) {
    std::vector<uint8_t> payload;

    payload.push_back(a.angx & 0xFF);
    payload.push_back((a.angx >> 8) & 0xFF);
    payload.push_back(a.angy & 0xFF);
    payload.push_back((a.angy >> 8) & 0xFF);
    payload.push_back(a.angx & 0xFF);
    payload.push_back((a.angx >> 8) & 0xFF);

    return payload;
}
