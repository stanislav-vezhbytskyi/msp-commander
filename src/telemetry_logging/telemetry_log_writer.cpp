#include "../../include/telemetry_logging/telemetry_log_writer.h"

#include <filesystem>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <string>

void TelemetryLogWriter::write(const std::vector<TelemetryFrame> &telemetry) {

    if (!fout.is_open()) {
        std::cerr << "Log file is not open!\n";
        return;
    }
    for (const auto &t: telemetry) {
        int rollErr = t.rc.roll - t.attitude.angx;
        int pitchErr = t.rc.pitch - t.attitude.angy;
        int yawErr = t.rc.yaw - t.attitude.heading;

        fout << t.timestamp << ", "
                << t.rc.roll << ", "
                << t.attitude.angx << ", "
                << rollErr << ", "
                << t.rc.pitch << ", "
                << t.attitude.angy << ", "
                << pitchErr << ", "
                << t.rc.yaw << ", "
                << t.attitude.heading << ", "
                << yawErr << ", "
                << t.pid.roll().p << ", "
                << t.pid.roll().i << ", "
                << t.pid.roll().d << ", "
                << "\n";
    }
}

void TelemetryLogWriter::open(const std::string &fileName) {
    bool fileExists = std::filesystem::exists(fileName);
    fout.open(fileName, std::ios::out | std::ios::app);

    if (!fileExists) {
        fout << "timestamp" << ", "
                 << "rc.roll" << ", "
                 << "attitude.angx" << ", "
                 << "rollErr" << ", "
                 << "rc.pitch" << ", "
                 << "attitude.angy" << ", "
                 << "pitchErr" << ", "
                 << "rc.yaw" << ", "
                 << "attitude.heading" << ", "
                 << "yawErr" << ", "
                 << "pid.roll().p" << ", "
                 << "pid.roll().i" << ", "
                 << "pid.roll().d" << ", "
                 << "\n";
    }
}

bool TelemetryLogWriter::isOpen() {
    return fout.is_open();
}

