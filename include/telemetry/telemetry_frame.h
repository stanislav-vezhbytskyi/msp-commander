#pragma once
#include "telemetry/telemetry_data.h"

struct TelemetryFrame {
    long long timestamp;
    telemetry::data::RCData rc;
    telemetry::data::AttitudeData attitude;
    telemetry::data::PIDData pid;
};
