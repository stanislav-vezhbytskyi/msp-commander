#include "../../../include/encoder/payload-encoders/pid_encoder.h"

std::vector<uint8_t> PIDEncoder::encode(MSP::PID pid) {
    std::vector<uint8_t> payload;

    payload.push_back(pid.roll);
    payload.push_back(pid.pitch);
    payload.push_back(pid.yaw);
    payload.push_back(pid.alt);
    payload.push_back(pid.pos);
    payload.push_back(pid.posr);
    payload.push_back(pid.navr);
    payload.push_back(pid.level);
    payload.push_back(pid.mag);
    payload.push_back(pid.vel);

    return payload;
}


