#include "pid_decoder.h"
#include <cstdint>
#include <variant>

#include "msp_protocol.h"

DecodedTypes PIDDecoder::decode(const std::vector<uint8_t>& payload){
    std::vector<MSP::PID> pids;
    if (payload.size() % 3 != 0) return std::monostate{};

    for (size_t i = 0; i < payload.size(); i += 3) {
        MSP::PID pid {
            .p = payload[i],
            .i = payload[i + 1],
            .d = payload[i + 2]
        };
        pids.push_back(pid);
    }
    return pids;
}
