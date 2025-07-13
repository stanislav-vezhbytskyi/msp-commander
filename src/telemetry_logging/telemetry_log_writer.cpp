#include "../../include/telemetry_logging/telemetry_log_writer.h"

#include <atomic>
#include <filesystem>
#include <fstream>
#include <iosfwd>
#include <iostream>
#include <string>

#include "plog/Log.h"


void TelemetryLogWriter::write(std::shared_ptr<
                                   BlockingQueue<TelemetryFrame> > telemetry, std::atomic<bool> &running) {
    while (running) {
        const auto &t = telemetry->pop();

        int rollErr = t.rc.roll - t.attitude.angx;
        int pitchErr = t.rc.pitch - t.attitude.angy;
        int yawErr = t.rc.yaw - t.attitude.heading;

        fout << t.timestamp << ", "
                << t.rc.roll << ", " << t.rc.pitch << ", " << t.rc.yaw << ", "
                << t.attitude.angx << ", " << t.attitude.angy << ", " << t.attitude.heading << ", "
                << rollErr << ", " << pitchErr << ", " << yawErr << ", "
                << t.imuData.gyrX << ", " << t.imuData.gyrY << ", " << t.imuData.gyrZ << ", "
                << t.imuData.accX << ", " << t.imuData.accY << ", " << t.imuData.accZ << ", "
                << t.pid.roll().p << ", " << t.pid.roll().i << ", " << t.pid.roll().d << ", "
                << "\n";
    }
}


void TelemetryLogWriter::open(const std::string &fileName) {
    bool fileExists = std::filesystem::exists(fileName);
    fout.open(fileName, std::ios::out | std::ios::app);

    if (!fileExists) {
        fout << "timestamp" << ", "
                << "rc.roll" << ", " << "rc.pitch" << ", " << "rc.yaw" << ", "
                << "attitude.angx" << ", " << "attitude.angy" << ", " << "attitude.heading" << ", "
                << "rollErr" << ", " << "pitchErr" << ", " << "yawErr" << ", "
                << "gyro.rollRate" << ", " << "gyro.pitchRate" << ", " << "gyro.yawRate" << ", "
                << "accel.x" << ", " << "accel.y" << ", " << "accel.z" << ", "
                << "pid.roll().p" << ", " << "pid.roll().i" << ", " << "pid.roll().d" << ", "
                << "\n";
    }
}

bool TelemetryLogWriter::isOpen() const {
    return fout.is_open();
}
