#pragma once

#include "../msp_dto.h"

#include "msp/msp_payload_variant.h"

namespace packet_decoder {
    MSPPayloadVariant decode(const MSPDTO& dto);
}