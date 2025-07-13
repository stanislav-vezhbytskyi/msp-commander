#include "../../include/msp/msp_payload_router.hpp"

#include "msp/msp_payload_variant.h"
#include "msp/decoder/packet_decoder.h"

namespace msp {
    void MSPPayloadRouter::processPackets(const std::vector<MSPDTO>& packets,
                                         PID& pid, Attitude& attitude, RC& rc, RawIMU& rawIMU) {
        for (const auto& dto : packets) {
            MSPPayloadVariant payload = packet_decoder::decode(dto);
            if (std::holds_alternative<PID>(payload)) {
                pid = std::get<PID>(payload);
            } else if (std::holds_alternative<Attitude>(payload)) {
                attitude = std::get<Attitude>(payload);
            } else if (std::holds_alternative<RC>(payload)) {
                rc = std::get<RC>(payload);
            } else if (std::holds_alternative<RawIMU>(payload)) {
                rawIMU = std::get<RawIMU>(payload);
            }
        }
    }

}
