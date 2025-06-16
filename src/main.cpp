#include "../include/msp/msp_dto.h"

#include <unistd.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include <fstream>
#include <thread>
#include <variant>

#include "msp/decoder/msp_parser.h"
#include "../include/serial/SerialPort.h"
#include "../include/mspcomm/msp_comm_service.h"
#include "msp/msp_payload_variant.h"
#include "msp/msp_protocol.h"
#include "msp/decoder/packet_decoder.h"
#include "telemetry_logging/telemetry_log_writer.h"
#include "chrono"
#include "telemetry/raw_to_data.h"


void printDTO(const MSPDTO& dto){
    std::cout << "MSPDTO { "
             << "direction: " << +dto.direction << ", "
             << "length: " << +dto.length << ", "
             << "command: " << +dto.command << ", "
             << "payload: [";

    for (size_t i = 0; i < dto.payload.size(); ++i) {
        std::cout << "0x" << std::hex << +dto.payload[i] << std::dec;
        if (i + 1 < dto.payload.size()) std::cout << ", ";
    }
    std::cout << "], checksum: 0x" << std::hex << +dto.checksum << std::dec << " }\n";
}

int main() {
    SerialPort serialProtocol;

    if (!serialProtocol.open("/dev/ttyACM0", 115200)) {
        std::cerr << "Failed to open serial port\n";
        return 1;
    }

    std::vector<MSPDTO> packets;
    MSPParser parser;

    MspCommService commService;

    TelemetryLogWriter logWriter;
    logWriter.open("TTTTTTTTtelemetry-logs.csv");
    if (!logWriter.isOpen()) {
        std::cerr << "Failed to open telemetry log file\n";
        return 1;
    }

    std::vector<TelemetryFrame> telemetry;
    auto startPoint = std::chrono::high_resolution_clock::now();


    for (int i = 0; i < 100; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));


        commService.requestAllSensorData(serialProtocol);

        std::vector<uint8_t> buffer(128);
        ssize_t bytesRead = serialProtocol.read(buffer.data(), buffer.size());

        msp::PID pid{};
        msp::Attitude attitude{};
        msp::RC rc{};

        packets.clear();
        parser.parse(bytesRead, buffer, packets);
        for (const auto& dto: packets) {
            printDTO(dto);

            MSPPayloadVariant payload = packet_decoder::decode(dto);
            if (std::holds_alternative<msp::PID>(payload)) {
                pid = std::get<msp::PID>(payload);
            } else if (std::holds_alternative<msp::Attitude>(payload)) {
                attitude = std::get<msp::Attitude>(payload);
            } else if (std::holds_alternative<msp::RC>(payload)) {
                rc = std::get<msp::RC>(payload);
            }
        }

        telemetry::data::PIDData pidData{};
        telemetry::data::AttitudeData attitudeData{};
        telemetry::data::RCData rcData{};
        pidData = telemetry::converters::raw_to_data::convert(pid);
        attitudeData = telemetry::converters::raw_to_data::convert(attitude);
        rcData = telemetry::converters::raw_to_data::convert(rc);

        auto endPoint = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endPoint- startPoint);
        telemetry.push_back({duration.count(), rcData, attitudeData, pidData});
        logWriter.write(telemetry);
        telemetry.clear();
    }

    serialProtocol.close();
}
