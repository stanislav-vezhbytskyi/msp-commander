#include <iostream>
#include <variant>
#include <vector>

#include "../../../include/decoder/forwarder/data_forwarder.h"
#include "msp_protocol.h"

void DataForwarder::forward(const MSPPayloadVariant& data) {
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::vector<MSP::PID>>) {
            std::cout << "Forwarded PID data:\n";
        } else if constexpr (std::is_same_v<T, MSP::STATUS>) {
            std::cout << "Forwarded STATUS data:\n";
            std::cout << "cycleTime: " << arg.cycleTime << " us\n";
            std::cout << "i2cErrorsCount: " << arg.i2cErrorsCount << "\n";
            std::cout << "sensor (raw): " << arg.sensor << "\n";

            std::cout << "BARO: " << ((arg.sensor & (1 << 1)) ? "ON" : "OFF") << ", ";
            std::cout << "MAG: "  << ((arg.sensor & (1 << 2)) ? "ON" : "OFF") << ", ";
            std::cout << "GPS: "  << ((arg.sensor & (1 << 3)) ? "ON" : "OFF") << ", ";
            std::cout << "SONAR: "<< ((arg.sensor & (1 << 4)) ? "ON" : "OFF") << "\n";

            std::cout << "flag (bitfield): " << arg.flag << "\n";
            std::cout << "currentSet: " << static_cast<int>(arg.currentSet) << "\n";

        } else if constexpr(std::is_same_v<T, MSP::RawIMU>) {
            std::cout<<"raw imu type here!";
        }else if constexpr(std::is_same_v<T, MSP::ATTITUDE>) {
            std::cout<<"attitude type here!";
        }else if constexpr(std::is_same_v<T, MSP::RC>) {
            std::cout<<"rc type here!";
        }
        else if constexpr (std::is_same_v<T, std::monostate>) {
            std::cout << "No decoded data\n";

        } else {
            std::cout << "Unhandled type in forwarder\n";
        }
    }, data);
}
