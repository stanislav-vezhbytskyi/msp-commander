#include "pid_forwarder.h"

#include <any>
#include <iostream>
#include <variant>
#include <vector>

#include "msp_protocol.h"

void PIDForwarder::forward(const DecodedTypes& data) {
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::vector<MSP::PID>>) {
            std::cout << "Forwarded PID data:\n";
            for (const auto& pid : arg) {
                std::cout << "P: " << pid.p << ", I: " << pid.i << ", D: " << pid.d << '\n';
            }
        } else if constexpr (std::is_same_v<T, MSP::GyroData>) {
            std::cout << "Gyro: " << arg.x << ", " << arg.y << ", " << arg.z << '\n';
        } else if constexpr (std::is_same_v<T, std::monostate>) {
            std::cout << "No decoded data\n";
        } else {
            std::cout << "Unhandled type in forwarder\n";
        }
    }, data);
}

