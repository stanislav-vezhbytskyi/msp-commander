#include "../../include/telemetry/raw_to_data.h"

namespace telemetry::converters::raw_to_data {
    data::PIDData convert(const msp::PID &pid) {
        data::PIDData result;

        for (size_t i = 0; i < data::PIDData::PIDITEMS; ++i) {
            const auto &rawItem = pid.items[i];
            auto &dataItem = result.items[i];

            dataItem.p = static_cast<int>(rawItem.p);
            dataItem.i = static_cast<int>(rawItem.i);
            dataItem.d = static_cast<int>(rawItem.d);
        }

        return result;
    }
    data::StatusData convert(const msp::Status &status) {
        telemetry::data::StatusData result;
        result.cycleTime = static_cast<int>(status.cycleTime);
        result.i2cErrorsCount = static_cast<int>(status.i2cErrorsCount);
        result.sensor = static_cast<int>(status.sensor);
        result.flag = status.flag; // 32-bit
        result.currentSet = static_cast<int>(status.currentSet);
        return result;
    }

    data::RawIMUData convert(const msp::RawIMU &rawIMU) {
        telemetry::data::RawIMUData result;
        result.accX = static_cast<int>(rawIMU.accX);
        result.accY = static_cast<int>(rawIMU.accY);
        result.accZ = static_cast<int>(rawIMU.accZ);

        result.gyrX = static_cast<int>(rawIMU.gyrX);
        result.gyrY = static_cast<int>(rawIMU.gyrY);
        result.gyrZ = static_cast<int>(rawIMU.gyrZ);

        result.magX = static_cast<int>(rawIMU.magX);
        result.magY = static_cast<int>(rawIMU.magY);
        result.magZ = static_cast<int>(rawIMU.magZ);

        return result;
    }

    data::AttitudeData convert(const msp::Attitude &attitude) {
        telemetry::data::AttitudeData result;
        result.angx = static_cast<int>(attitude.angx);
        result.angy = static_cast<int>(attitude.angy);
        result.heading = static_cast<int>(attitude.heading);
        return result;
    }

    data::RCData convert(const msp::RC &rc) {
        telemetry::data::RCData result;
        result.roll = static_cast<int>(rc.roll);
        result.pitch = static_cast<int>(rc.pitch);
        result.yaw = static_cast<int>(rc.yaw);
        result.throttle = static_cast<int>(rc.throttle);
        result.aux1 = static_cast<int>(rc.aux1);
        result.aux2 = static_cast<int>(rc.aux2);
        result.aux3 = static_cast<int>(rc.aux3);
        result.aux4 = static_cast<int>(rc.aux4);
        return result;
    }
}
