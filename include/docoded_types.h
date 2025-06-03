#pragma once
#include <variant>
#include <vector>

#include "msp_protocol.h"

using DecodedTypes = std::variant<
    std::vector<MSP::PID>,
    MSP::GyroData,
    std::monostate
//, todo: add new types
>;
