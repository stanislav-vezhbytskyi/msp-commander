#include <iostream>


#include "msp/msp_payload_variant.h"
#include "msp/decoder/packet_decoder.h"


namespace packet_decoder {
    namespace {
        MSPPayloadVariant decodeAttitude(const std::vector<uint8_t> &payload) {
            msp::Attitude a;

            a.angx = payload[0] | (payload[1] << 8);
            a.angy = payload[2] | (payload[3] << 8);
            a.heading = payload[4] | (payload[5] << 8);

            return a;
        }

        MSPPayloadVariant decodePID(const std::vector<uint8_t>& payload) {
            msp::PID pid;

            int count = payload.size() / 3;
            for (int i = 0; i < count && i < msp::PID::PIDITEMS; ++i) {
                pid.items[i].p = payload[i * 3];
                pid.items[i].i = payload[i * 3 + 1];
                pid.items[i].d = payload[i * 3 + 2];
            }

            return pid;
        }

        MSPPayloadVariant decodeRawIMU(const std::vector<uint8_t> &payload) {
            msp::RawIMU r;

            r.accX = payload[0] | (payload[1] << 8);
            r.accY = payload[2] | (payload[3] << 8);
            r.accZ = payload[4] | (payload[5] << 8);
            r.gyrX = payload[6] | (payload[7] << 8);
            r.gyrY = payload[8] | (payload[9] << 8);
            r.gyrZ = payload[10] | (payload[11] << 8);
            r.magX = payload[12] | (payload[13] << 8);
            r.magY = payload[14] | (payload[15] << 8);
            r.magZ = payload[16] | (payload[17] << 8);

            return r;
        }

        MSPPayloadVariant decodeRC(const std::vector<uint8_t> &payload) {
            msp::RC rc;

            rc.roll = payload[0] | (payload[1] << 8);
            rc.pitch = payload[2] | (payload[3] << 8);
            rc.yaw = payload[4] | (payload[5] << 8);
            rc.throttle = payload[6] | (payload[7] << 8);
            rc.aux1 = payload[8] | (payload[9] << 8);
            rc.aux2 = payload[10] | (payload[11] << 8);
            rc.aux3 = payload[12] | (payload[13] << 8);
            rc.aux4 = payload[14] | (payload[15] << 8);

            return rc;
        }

        MSPPayloadVariant decodeStatus(const std::vector<uint8_t> &payload) {
            msp::Status s;

            s.cycleTime = payload[0] | (payload[1] << 8);
            s.i2cErrorsCount = payload[2] | (payload[3] << 8);
            s.sensor = payload[4] | (payload[5] << 8);
            s.flag = payload[6] | (payload[7] << 8) | (payload[8] << 16) | (payload[9] << 24);
            s.currentSet = payload[10];

            return s;
        }
    }

    MSPPayloadVariant decode(const MSPDTO &dto) {
        switch (dto.command) {
            case msp::codeid::PID:
                return decodePID(dto.payload);
            case msp::codeid::STATUS:
                return decodeStatus(dto.payload);
            case msp::codeid::RAW_IMU:
                return decodeRawIMU(dto.payload);
            case msp::codeid::ATTITUDE:
                return decodeAttitude(dto.payload);
            case msp::codeid::RC:
                return decodeRC(dto.payload);
            default:
                return {};
        }
    }
}
