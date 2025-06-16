#pragma once
#include "telemetry_data.h"
#include "msp/msp_protocol.h"

namespace telemetry::converters::raw_to_data {
    data::PIDData convert(const msp::PID &pid) ;
    data::StatusData convert(const msp::Status &status) ;

    data::RawIMUData convert(const msp::RawIMU &rawIMU) ;

    data::AttitudeData convert(const msp::Attitude &attitude) ;

    data::RCData convert(const msp::RC &rc) ;
}
