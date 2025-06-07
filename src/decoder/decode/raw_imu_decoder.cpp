
#include "decoder/payload-decoders/raw_imu_decoder.h"

#include "../../../include/msp_payload_variant.h"

MSPPayloadVariant RawIMUDecoder::decode(const std::vector<uint8_t> &payload) {
    MSP::RawIMU r;

    r.accX = payload[0] | (payload[1] << 8);
    r.accY = payload[2] | (payload[3] << 8);
    r.accZ = payload[4] | (payload[5] << 8);
    r.gyrX = payload[6] | (payload[7] << 8);
    r.gyrY = payload[8] | (payload[9] << 8);
    r.gyrZ = payload[10] | (payload[11] << 8);
    r.magX = payload[12] | (payload[13] << 8);
    r.magY = payload[14] | (payload[15] << 8);
    r.magZ = payload[16] | (payload[17] << 8);

    return r;
}
