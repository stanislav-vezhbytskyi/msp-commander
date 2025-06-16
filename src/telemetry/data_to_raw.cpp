#include "../../include/telemetry/data_to_raw.h"
#include <algorithm> //

namespace telemetry::converters::data_to_raw {

    constexpr uint8_t clamp_u8(int value) {
        return static_cast<uint8_t>(std::clamp(value, 0, 255));
    }

    constexpr uint16_t clamp_u16(int value) {
        return static_cast<uint16_t>(std::clamp(value, 0, 65535));
    }

    msp::PID convert(const data::PIDData& pidData) {
        msp::PID result;
        for (size_t i = 0; i < msp::PID::PIDITEMS; ++i) {
            const auto& dataItem = pidData.items[i];
            auto& rawItem = result.items[i];
            rawItem.p = clamp_u8(dataItem.p);
            rawItem.i = clamp_u8(dataItem.i);
            rawItem.d = clamp_u8(dataItem.d);
        }
        return result;
    }

    msp::Status convert(const data::StatusData& statusData) {
        msp::Status result;
        result.cycleTime = clamp_u16(statusData.cycleTime);
        result.i2cErrorsCount = clamp_u16(statusData.i2cErrorsCount);
        result.sensor = clamp_u16(statusData.sensor);
        result.flag = static_cast<uint32_t>(statusData.flag); // припускаємо, що input ок
        result.currentSet = clamp_u8(statusData.currentSet);
        return result;
    }

    msp::RawIMU convert(const data::RawIMUData& imuData) {
        msp::RawIMU result;
        result.accX = clamp_u16(imuData.accX);
        result.accY = clamp_u16(imuData.accY);
        result.accZ = clamp_u16(imuData.accZ);

        result.gyrX = clamp_u16(imuData.gyrX);
        result.gyrY = clamp_u16(imuData.gyrY);
        result.gyrZ = clamp_u16(imuData.gyrZ);

        result.magX = clamp_u16(imuData.magX);
        result.magY = clamp_u16(imuData.magY);
        result.magZ = clamp_u16(imuData.magZ);

        return result;
    }

    msp::Attitude convert(const data::AttitudeData& attitudeData) {
        msp::Attitude result;
        result.angx = clamp_u16(attitudeData.angx);
        result.angy = clamp_u16(attitudeData.angy);
        result.heading = clamp_u16(attitudeData.heading);
        return result;
    }

    msp::RC convert(const data::RCData& rcData) {
        msp::RC result;
        result.roll = clamp_u16(rcData.roll);
        result.pitch = clamp_u16(rcData.pitch);
        result.yaw = clamp_u16(rcData.yaw);
        result.throttle = clamp_u16(rcData.throttle);
        result.aux1 = clamp_u16(rcData.aux1);
        result.aux2 = clamp_u16(rcData.aux2);
        result.aux3 = clamp_u16(rcData.aux3);
        result.aux4 = clamp_u16(rcData.aux4);
        return result;
    }

}
