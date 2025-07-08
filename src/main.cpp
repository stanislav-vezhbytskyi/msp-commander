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
#include "util/config_reader.h"

#include <plog/Log.h>
#include <plog/Appenders/ConsoleAppender.h>
#include <plog/Appenders/RollingFileAppender.h>
#include <plog/Formatters/TxtFormatter.h>

#include "plog/Init.h"

const std::string CONFIG_FILE_NAME = "config.cfg";

static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
static plog::RollingFileAppender<plog::TxtFormatter> fileAppender("app.log");

// void printDTO(const MSPDTO &dto) {
//     std::cout << "MSPDTO { "
//             << "direction: " << +dto.direction << ", "
//             << "length: " << +dto.length << ", "
//             << "command: " << +dto.command << ", "
//             << "payload: [";
//
//     for (size_t i = 0; i < dto.payload.size(); ++i) {
//         std::cout << "0x" << std::hex << +dto.payload[i] << std::dec;
//         if (i + 1 < dto.payload.size()) std::cout << ", ";
//     }
//     std::cout << "], checksum: 0x" << std::hex << +dto.checksum << std::dec << " }\n";
// }

void initLogging() {
    plog::init(plog::debug, &consoleAppender).addAppender(&fileAppender);
    PLOGI << "App started.";
}
ConfigDTO loadConfig(const std::string& configFile) {
    PLOGI << "Reading configs from file " << configFile;
    ConfigReader confReader;
    ConfigDTO config = confReader.readConfig(configFile);
    PLOGI << "Config loaded: device=" << config.serialDevice
          << ", baudRate=" << config.baudRate
          << ", logFile=" << config.logFilePath;
    return config;
}
bool openSerialPort(SerialPort& serial, const ConfigDTO& config) {
    PLOGI << "Trying to start serial port on " << config.serialDevice
          << " with baud rate " << config.baudRate;
    if (!serial.open(config.serialDevice, config.baudRate)) {
        PLOGF << "Failed to open serial port";
        return false;
    }
    PLOGI << "Serial port opened successfully.";
    return true;
}

bool openTelemetryLog(TelemetryLogWriter& logWriter, const std::string& logFilePath) {
    logWriter.open(logFilePath);
    PLOGI << "Opening telemetry log file: " << logFilePath;
    if (!logWriter.isOpen()) {
        PLOGF << "Failed to open telemetry log file: " << logFilePath;
        return false;
    }
    PLOGI << "Telemetry logging started.";
    return true;
}

void processPackets(const std::vector<MSPDTO>& packets,
                    msp::PID& pid, msp::Attitude& attitude, msp::RC& rc, msp::RawIMU& rawIMU) {
    for (const auto& dto : packets) {
        MSPPayloadVariant payload = packet_decoder::decode(dto);
        if (std::holds_alternative<msp::PID>(payload)) {
            pid = std::get<msp::PID>(payload);
        } else if (std::holds_alternative<msp::Attitude>(payload)) {
            attitude = std::get<msp::Attitude>(payload);
        } else if (std::holds_alternative<msp::RC>(payload)) {
            rc = std::get<msp::RC>(payload);
        } else if (std::holds_alternative<msp::RawIMU>(payload)) {
            rawIMU = std::get<msp::RawIMU>(payload);
        }
    }
}

void runLoop(SerialPort& serialProtocol, MspCommService& commService,
             MSPParser& parser, TelemetryLogWriter& logWriter) {

    std::vector<MSPDTO> packets;
    std::vector<TelemetryFrame> telemetry;
    auto startPoint = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < 1000; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        commService.requestAllSensorData(serialProtocol);

        std::vector<uint8_t> buffer(128);
        ssize_t bytesRead = serialProtocol.read(buffer.data(), buffer.size());

        msp::PID pid{};
        msp::Attitude attitude{};
        msp::RC rc{};
        msp::RawIMU rawIMU{};

        packets.clear();
        parser.parse(bytesRead, buffer, packets);
        processPackets(packets, pid, attitude, rc, rawIMU);

        telemetry::data::PIDData pidData = telemetry::converters::raw_to_data::convert(pid);
        telemetry::data::AttitudeData attitudeData = telemetry::converters::raw_to_data::convert(attitude);
        telemetry::data::RCData rcData = telemetry::converters::raw_to_data::convert(rc);
        telemetry::data::RawIMUData rawIMUData = telemetry::converters::raw_to_data::convert(rawIMU);

        auto endPoint = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endPoint - startPoint);

        telemetry.push_back({duration.count(), rcData, attitudeData, pidData, rawIMUData});
        logWriter.write(telemetry);
        telemetry.clear();
    }
}

int main() {
    initLogging();
    ConfigDTO conf = loadConfig(CONFIG_FILE_NAME);

    SerialPort serial;
    if (!openSerialPort(serial, conf)) {
        return -1;
    }

    TelemetryLogWriter logWriter;
    if (!openTelemetryLog(logWriter, conf.logFilePath)) {
        return -1;
    }


    MspCommService commService;
    MSPParser parser;

    runLoop(serial, commService, parser,logWriter);

}