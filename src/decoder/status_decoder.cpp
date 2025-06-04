#include "status_decoder.h"

DecodedTypes StatusDecoder::decode(const std::vector<uint8_t> &payload) {
    MSP::STATUS s;

    s.cycleTime = payload[0] | (payload[1] << 8);
    s.i2cErrorsCount = payload[2] | (payload[3]<< 8);
    s.sensor = payload[4] | (payload[5]<< 8);
    s.flag = payload[6] | (payload[7]<< 8) | (payload[8]<< 16) | (payload[9]<< 24);
    s.currentSet = payload[10];

    return s;
}
