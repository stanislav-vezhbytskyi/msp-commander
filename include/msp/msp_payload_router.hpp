#pragma once
#include <vector>
#include "msp/msp_dto.h"
#include "msp/msp_protocol.h"

namespace msp {
    class MSPPayloadRouter {
    public:
        static void processPackets(const std::vector<MSPDTO>& packets,
                            PID& pid, Attitude& attitude, RC& rc, RawIMU& rawIMU) ;
    };
}

