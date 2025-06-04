#pragma once
#include <variant>
#include <vector>

#include "msp_protocol.h"

using DecodedTypes = std::variant<
    MSP::PID,
    MSP::STATUS,
    MSP::RawIMU,
    MSP::ATTITUDE,
    MSP::RC,
    std::monostate
//, todo: add new types
>;
