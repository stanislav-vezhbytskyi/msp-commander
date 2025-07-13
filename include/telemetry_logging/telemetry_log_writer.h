#pragma once
#include <atomic>
#include <fstream>
#include <iosfwd>
#include <vector>

#include "../telemetry/telemetry_frame.h"
#include "util/blocking_queue.hpp"

class TelemetryLogWriter {
public:
    void open(const std::string &fileName);
    bool isOpen() const;
    void write(std::shared_ptr<
                     BlockingQueue<TelemetryFrame>> telemetry, std::atomic<bool>& running);
    private:
    std::fstream fout;
};
