#pragma once
#include <variant>
#include <vector>

#include "msp_protocol.h"

using MSPPayloadVariant = std::variant<
    msp::PID,
    msp::Status,
    msp::RawIMU,
    msp::Attitude,
    msp::RC,
    std::monostate
>;
