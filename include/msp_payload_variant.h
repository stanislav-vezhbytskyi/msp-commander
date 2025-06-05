#pragma once
#include <variant>
#include <vector>

#include "msp_protocol.h"

using MSPPayloadVariant = std::variant<
    MSP::PID,
    MSP::STATUS,
    MSP::RawIMU,
    MSP::ATTITUDE,
    MSP::RC,
    std::monostate
>;
