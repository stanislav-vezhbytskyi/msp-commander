#pragma once
#include "../../msp_payload_variant.h"


class DataForwarder {
public:
     ~DataForwarder() = default;
     void forward(const MSPPayloadVariant& data);
};
