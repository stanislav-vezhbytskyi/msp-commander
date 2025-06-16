#pragma once
#include <fstream>
#include <iosfwd>
#include <vector>

#include "../telemetry/telemetry_frame.h"

class TelemetryLogWriter {
public:
    void open(const std::string &fileName);
    bool isOpen();
    void write(const std::vector<TelemetryFrame> &f);
    private:
    std::fstream fout;
};
