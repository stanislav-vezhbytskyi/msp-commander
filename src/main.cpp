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

#include "../include/util/blocking_queue.hpp"

#include "plog/Init.h"
#include "telemetry/telemetry_stream_processor.hpp"

const std::string CONFIG_FILE_NAME = "config.cfg";

static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender;
static plog::RollingFileAppender<plog::TxtFormatter> fileAppender("app.log");

void initLogging() {
    plog::init(plog::debug, &consoleAppender).addAppender(&fileAppender);
    PLOGI << "App started.";
}

ConfigDTO loadConfig(const std::string &configFile) {
    PLOGI << "Reading configs from file " << configFile;
    ConfigReader confReader;
    ConfigDTO config = confReader.readConfig(configFile);
    PLOGI << "Config loaded: device=" << config.serialDevice
          << ", baudRate=" << config.baudRate
          << ", logFile=" << config.logFilePath;
    return config;
}

bool openSerialPort(SerialPort &serial, const ConfigDTO &config) {
    PLOGI << "Trying to start serial port on " << config.serialDevice
          << " with baud rate " << config.baudRate;
    if (!serial.open(config.serialDevice, config.baudRate)) {
        PLOGF << "Failed to open serial port";
        return false;
    }
    PLOGI << "Serial port opened successfully.";
    return true;
}

bool openTelemetryLog(TelemetryLogWriter &logWriter, const std::string &logFilePath) {
    logWriter.open(logFilePath);
    PLOGI << "Opening telemetry log file: " << logFilePath;
    if (!logWriter.isOpen()) {
        PLOGF << "Failed to open telemetry log file: " << logFilePath;
        return false;
    }
    PLOGI << "Telemetry logging started.";
    return true;
}

int main() {
    initLogging();
    ConfigDTO conf = loadConfig(CONFIG_FILE_NAME);
    auto startPoint = std::chrono::high_resolution_clock::now();

    SerialPort serial;
    if (!openSerialPort(serial, conf)) return -1;

    auto telemetryQueue = std::make_shared<BlockingQueue<TelemetryFrame>>();

    TelemetryLogWriter logWriter;
    if (!openTelemetryLog(logWriter, conf.logFilePath)) return -1;

    std::atomic<bool> running{true};

    TelemetryStreamProcessor reader(serial, telemetryQueue, running);

    std::thread readerThread(&TelemetryStreamProcessor::run, &reader);
    std::thread logWriterThread(&TelemetryLogWriter::write, &logWriter, telemetryQueue, std::ref(running));

    std::this_thread::sleep_for(std::chrono::seconds(2));
    running = false;

    readerThread.join();
    logWriterThread.join();

    return 0;
}
