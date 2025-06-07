
#include "decoder/payload-decoders/rc_decoder.h"

#include "../../../include/msp_payload_variant.h"

MSPPayloadVariant RCDecoder::decode(const std::vector<uint8_t> &payload) {
    MSP::RC rc;

    rc.roll = payload[0] | (payload[1]<<8);
    rc.pitch = payload[2] | (payload[3]<<8);
    rc.yaw = payload[4] | (payload[5]<<8);
    rc.throttle = payload[6] | (payload[7]<<8);
    rc.aux1 = payload[8] | (payload[9]<<8);
    rc.aux2 = payload[10] | (payload[11]<<8);
    rc.aux3 = payload[12] | (payload[13]<<8);
    rc.aux4 = payload[14] | (payload[15]<<8);

    return rc;
}
