#include "../../../include/encoder/payload-encoders/raw_imu_encoder.h"


std::vector<uint8_t> RawIMUEncoder::encode(MSP::RawIMU r) {
    std::vector<uint8_t> payload;

    payload.push_back(r.accX & 0xFF);
    payload.push_back((r.accX >> 8) & 0xFF);
    payload.push_back(r.accY & 0xFF);
    payload.push_back((r.accY >> 8) & 0xFF);
    payload.push_back(r.accZ & 0xFF);
    payload.push_back((r.accZ >> 8) & 0xFF);
    payload.push_back(r.gyrX & 0xFF);
    payload.push_back((r.gyrX >> 8) & 0xFF);
    payload.push_back(r.gyrY & 0xFF);
    payload.push_back((r.gyrY >> 8) & 0xFF);
    payload.push_back(r.gyrZ & 0xFF);
    payload.push_back((r.gyrZ >> 8) & 0xFF);
    payload.push_back(r.magX & 0xFF);
    payload.push_back((r.magX >> 8) & 0xFF);
    payload.push_back(r.magY & 0xFF);
    payload.push_back((r.magY >> 8) & 0xFF);
    payload.push_back(r.magZ & 0xFF);
    payload.push_back((r.magZ >> 8) & 0xFF);

    return payload;
}
