#include "../../include/telemetry/telemetry_stream_processor.hpp"
#include "telemetry/data_to_raw.h"
#include "telemetry/raw_to_data.h"
#include <thread>
#include <chrono>

#include "msp/msp_dto.h"
#include "mspcomm/msp_comm_service.h"

TelemetryStreamProcessor::TelemetryStreamProcessor(SerialPort& serialPort,
                                             std::shared_ptr<BlockingQueue<TelemetryFrame>> telemetryQueue,
                                             std::atomic<bool>& runningFlag)
    : serialProtocol(serialPort), telemetry(std::move(telemetryQueue)), running(runningFlag),
      startPoint(std::chrono::high_resolution_clock::now()) {}

void TelemetryStreamProcessor::run() {
    while (running) {
        std::vector<MSPDTO> packets;
        MspCommService::requestAllSensorData(serialProtocol);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        std::vector<uint8_t> buffer(128);
        ssize_t bytesRead = serialProtocol.read(buffer.data(), buffer.size());

        msp::PID pid{};
        msp::Attitude attitude{};
        msp::RC rc{};
        msp::RawIMU rawIMU{};

        parser.parse(bytesRead, buffer, packets);
        payloadRouter.processPackets(packets, pid, attitude, rc, rawIMU);

        telemetry::data::PIDData pidData = telemetry::converters::raw_to_data::convert(pid);
        telemetry::data::AttitudeData attitudeData = telemetry::converters::raw_to_data::convert(attitude);
        telemetry::data::RCData rcData = telemetry::converters::raw_to_data::convert(rc);
        telemetry::data::RawIMUData rawIMUData = telemetry::converters::raw_to_data::convert(rawIMU);

        auto endPoint = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endPoint - startPoint);

        telemetry->push({duration.count(), rcData, attitudeData, pidData, rawIMUData});
    }
}
