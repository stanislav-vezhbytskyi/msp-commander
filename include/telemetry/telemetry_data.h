#pragma once
#include <array>
#include <cstddef>

namespace telemetry::data {

    struct PIDItemData {
        int p;
        int i;
        int d;

        PIDItemData() : p(0), i(0), d(0) {}
        PIDItemData(int p_, int i_, int d_) : p(p_), i(i_), d(d_) {}
    };

    struct PIDData {
        static constexpr size_t PIDITEMS = 5;
        std::array<PIDItemData, PIDITEMS> items;

        PIDItemData &roll() { return items[0]; }
        const PIDItemData &roll() const { return items[0]; }

        PIDItemData &pitch() { return items[1]; }
        const PIDItemData &pitch() const { return items[1]; }

        PIDItemData &yaw() { return items[2]; }
        const PIDItemData &yaw() const { return items[2]; }

        PIDItemData &alt() { return items[3]; }
        const PIDItemData &alt() const { return items[3]; }

        PIDItemData &pos() { return items[4]; }
        const PIDItemData &pos() const { return items[4]; }

    };

    struct StatusData {
        int cycleTime = 0;
        int i2cErrorsCount = 0;
        int sensor = 0;
        int flag = 0;
        int currentSet = 0;
    };

    struct RawIMUData {
        int accX = 0, accY = 0, accZ = 0;
        int gyrX = 0, gyrY = 0, gyrZ = 0;
        int magX = 0, magY = 0, magZ = 0;
    };

    struct AttitudeData {
        int angx = 0;
        int angy = 0;
        int heading = 0;
    };

    // range [1000, 2000]
    struct RCData {
        int roll = 0;
        int pitch = 0;
        int yaw = 0;
        int throttle = 0;
        int aux1 = 0;
        int aux2 = 0;
        int aux3 = 0;
        int aux4 = 0;
    };

}
