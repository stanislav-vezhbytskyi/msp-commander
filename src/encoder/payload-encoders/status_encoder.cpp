#include "../../../include/encoder/payload-encoders/status_encoder.h"


std::vector<uint8_t> StatusEncoder::encode(MSP::STATUS s) {
    std::vector<uint8_t> payload;

    payload.push_back(s.cycleTime & 0xFF);
    payload.push_back((s.cycleTime >> 8) & 0xFF);
    payload.push_back(s.i2cErrorsCount  & 0xFF);
    payload.push_back((s.i2cErrorsCount >> 8) & 0xFF);
    payload.push_back(s.sensor  & 0xFF);
    payload.push_back((s.sensor  >> 8) & 0xFF);
    payload.push_back(s.flag   & 0xFF);
    payload.push_back((s.flag   >> 8) & 0xFF);
    payload.push_back((s.flag   >> 16) & 0xFF);
    payload.push_back((s.flag   >> 24) & 0xFF);
    payload.push_back(s.currentSet & 0xFF);

    return payload;
}
