#include <variant>

#include "../../../include/msp/msp_payload_variant.h"

namespace payload_encoder {
    namespace {
        inline void encodeInt16(std::vector<uint8_t>& payload, int16_t val) {
            payload.push_back(val & 0xFF);
            payload.push_back((val >> 8) & 0xFF);
        }

        std::vector<uint8_t> encode(const msp::Attitude& att) {
            std::vector<uint8_t> payload;
            encodeInt16(payload, att.angx);
            encodeInt16(payload, att.angy);
            encodeInt16(payload, att.heading);
            return payload;
        }

        std::vector<uint8_t> encode(const msp::PID& pid) {
            std::vector<uint8_t> payload;
            payload.reserve(msp::PID::PIDITEMS*3);

            for (const auto& i: pid.items) {
                payload.push_back(i.p);
                payload.push_back(i.i);
                payload.push_back(i.d);
            }

            return payload;
        }


        std::vector<uint8_t> encode(const msp::RawIMU& r) {
            std::vector<uint8_t> payload;

            encodeInt16(payload, r.accX);
            encodeInt16(payload, r.accY);
            encodeInt16(payload, r.accZ);
            encodeInt16(payload, r.gyrX);
            encodeInt16(payload, r.gyrY);
            encodeInt16(payload, r.gyrZ);
            encodeInt16(payload, r.magX);
            encodeInt16(payload, r.magY);
            encodeInt16(payload, r.magZ);
            return payload;
        }

        std::vector<uint8_t> encode(const msp::Status& s) {
            std::vector<uint8_t> payload;

            encodeInt16(payload, s.cycleTime);
            encodeInt16(payload, s.i2cErrorsCount);
            encodeInt16(payload,s.sensor);

            payload.push_back(s.flag   & 0xFF);
            payload.push_back((s.flag   >> 8) & 0xFF);
            payload.push_back((s.flag   >> 16) & 0xFF);
            payload.push_back((s.flag   >> 24) & 0xFF);
            payload.push_back(s.currentSet & 0xFF);

            return payload;
        }

        std::vector<uint8_t> encode(const msp::RC& rc) {
            std::vector<uint8_t> payload;

            encodeInt16(payload, rc.roll);
            encodeInt16(payload, rc.pitch);
            encodeInt16(payload, rc.yaw);
            encodeInt16(payload, rc.throttle);
            encodeInt16(payload, rc.aux1);
            encodeInt16(payload, rc.aux2);
            encodeInt16(payload, rc.aux3);
            encodeInt16(payload, rc.aux4);

            return payload;
        }
        std::vector<uint8_t> encode(const std::monostate& m) {
            return {};
        }
    }
    std::vector<uint8_t> encodePayload(const MSPPayloadVariant& data) {
        return std::visit([](const auto& payload) -> std::vector<uint8_t> {
            return encode(payload);
        }, data);
    }
}
