cmake_minimum_required(VERSION 3.10)
project(MSPCommander)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(msp_parser
    src/main.cpp
    src/msp_parser.cpp
        src/decoder/idecoder.h
        src/decoder/pid_decoder.cpp
        src/decoder/pid_decoder.h
        "src/handler/msp_dto_handler.cpp"
        "src/handler/msp_dto_handler.h"
        src/forwarder/idata_forwarder.h
        src/decoder/decoder_factory.cpp
        src/decoder/decoder_factory.h
        include/docoded_types.h
        src/decoder/status_decoder.cpp
        src/decoder/status_decoder.h
        src/forwarder/data_forwarder.cpp
        src/decoder/raw_imu_decoder.cpp
        src/decoder/raw_imu_decoder.h
        src/decoder/attitude_decoder.cpp
        src/decoder/attitude_decoder.h
        src/decoder/rc_decoder.cpp
        src/decoder/rc_decoder.h
)
