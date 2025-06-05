#include "../../include/encoder/msp-request-builder.h"

#include <vector>

#include "encoder/payload_encoders.h"


std::vector<uint8_t> MSPRequestBuilder::buildRequest(const uint8_t command, const MSPPayloadVariant& v) {
    std::vector<uint8_t> request;
    request.push_back('$');
    request.push_back('M');
    request.push_back('>');

    std::vector<uint8_t> payload = PayloadEncoders::encodePayload(v);

    request.push_back(payload.size());

    request.push_back(command);

    request.insert(request.end(), payload.begin(), payload.end());

    return request;
}
