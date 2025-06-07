#pragma once
#include <memory>

#include "msp_payload_variant.h"
#include "../msp_dto.h"


class PacketDecoder {
public:
    static MSPPayloadVariant decode(const MSPDTO& dto);
};
