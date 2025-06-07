#include "../../include/encoder/packet_encoder.h"

#include <vector>

#include "encoder/payload_encoder.h"


std::vector<uint8_t> PacketEncoder::encode(const uint8_t command, const MSPPayloadVariant& v) {
    std::vector<uint8_t> request;
    request.push_back('$');
    request.push_back('M');
    request.push_back('>');

    std::vector<uint8_t> payload = PayloadEncoder::encodePayload(v);

    request.push_back(payload.size());

    request.push_back(command);

    request.insert(request.end(), payload.begin(), payload.end());

    return request;
}
