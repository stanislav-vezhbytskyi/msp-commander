#pragma once

#include <memory>
#include <atomic>
#include <chrono>

#include "../msp/msp_payload_router.hpp"
#include "msp/msp_payload_variant.h"
#include "msp/decoder/msp_parser.h"
#include "serial/SerialPort.h"
#include "util/blocking_queue.hpp"
#include "telemetry/telemetry_frame.h"

class TelemetryStreamProcessor {
public:
    TelemetryStreamProcessor(SerialPort &serialPort,
                             std::shared_ptr<BlockingQueue<TelemetryFrame> > telemetryQueue,
                             std::atomic<bool> &runningFlag);

    void run();

private:
    SerialPort &serialProtocol;
    std::shared_ptr<BlockingQueue<TelemetryFrame> > telemetry;
    std::atomic<bool> &running;
    msp::MSPPayloadRouter payloadRouter;
    MSPParser parser;
    std::chrono::time_point<std::chrono::system_clock> startPoint;
};
