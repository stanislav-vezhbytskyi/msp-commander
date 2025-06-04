#include "../../../include/encoder/payload-encoders/rc_encoder.h"

std::vector<uint8_t> RCEncoder::encode(MSP::RC rc) {
    std::vector<uint8_t> payload;

    payload.push_back(rc.roll & 0xFF);
    payload.push_back((rc.roll >> 8) & 0xFF);
    payload.push_back(rc.pitch & 0xFF);
    payload.push_back((rc.pitch >> 8) & 0xFF);
    payload.push_back(rc.yaw & 0xFF);
    payload.push_back((rc.yaw >> 8) & 0xFF);
    payload.push_back(rc.throttle & 0xFF);
    payload.push_back((rc.throttle >> 8) & 0xFF);
    payload.push_back(rc.aux1 & 0xFF);
    payload.push_back((rc.aux1 >> 8) & 0xFF);
    payload.push_back(rc.aux2 & 0xFF);
    payload.push_back((rc.aux2 >> 8) & 0xFF);
    payload.push_back(rc.aux3 & 0xFF);
    payload.push_back((rc.aux3 >> 8) & 0xFF);
    payload.push_back(rc.aux4 & 0xFF);
    payload.push_back((rc.aux4 >> 8) & 0xFF);

    return payload;
}
