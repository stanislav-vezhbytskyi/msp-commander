cmake_minimum_required(VERSION 3.10)
project(MSPCommander)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(msp_parser
        src/main.cpp
        src/msp/decoder/msp_parser.cpp
        "src/msp/decoder/packet_decoder.cpp"
        "include/msp/decoder/packet_decoder.h"
        include/msp/msp_payload_variant.h

        src/msp/encoder/packet_encoder.cpp
        include/msp/encoder/packet_encoder.h
        src/msp/encoder/payload_encoder.cpp
        include/msp/encoder/payload_encoder.h
        src/serial/SerialPort.cpp
        include/serial/SerialPort.h
        src/mspcomm/msp_comm_service.cpp
        include/mspcomm/msp_comm_service.h
        src/telemetry_logging/telemetry_log_writer.cpp
        include/telemetry_logging/telemetry_log_writer.h
        src/telemetry_logging/telemetry_log_formatter.cpp
        include/telemetry_logging/telemetry_log_formatter.h
        include/telemetry/telemetry_frame.h
        include/telemetry/telemetry_data.h
        src/telemetry/raw_to_data.cpp
        include/telemetry/raw_to_data.h
        src/telemetry/data_to_raw.cpp
        include/telemetry/data_to_raw.h
)

include(FetchContent)

FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)

FetchContent_MakeAvailable(spdlog)

target_link_libraries(msp_parser PRIVATE spdlog::spdlog)
