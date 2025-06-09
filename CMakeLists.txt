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
)
