#pragma once
#include "msp/msp_protocol.h"
#include "telemetry/telemetry_data.h"

namespace telemetry::converters::data_to_raw {

    msp::PID convert(const data::PIDData& pidData) ;

    msp::Status convert(const data::StatusData& statusData) ;

    msp::RawIMU convert(const data::RawIMUData& imuData) ;

    msp::Attitude convert(const data::AttitudeData& attitudeData) ;

    msp::RC convert(const data::RCData& rcData) ;

}

