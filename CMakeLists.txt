cmake_minimum_required(VERSION 3.10)
project(MSPCommander)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(msp_parser
    src/main.cpp
        src/decoder/msp_parser.cpp
        include/decoder/payload-decoders/idecoder.h
        src/decoder/decode/pid_decoder.cpp
        include/decoder/payload-decoders/pid_decoder.h
        "src/decoder/packet_decoder.cpp"
        "include/decoder/packet_decoder.h"
        src/decoder/decode/decoder_factory.cpp
        include/decoder/payload-decoders/decoder_factory.h
        include/msp_payload_variant.h
        src/decoder/decode/status_decoder.cpp
        include/decoder/payload-decoders/status_decoder.h
        src/decoder/decode/raw_imu_decoder.cpp
        include/decoder/payload-decoders/raw_imu_decoder.h
        src/decoder/decode/attitude_decoder.cpp
        include/decoder/payload-decoders/attitude_decoder.h
        src/decoder/decode/rc_decoder.cpp
        include/decoder/payload-decoders/rc_decoder.h

        src/encoder/packet_encoder.cpp
        include/encoder/packet_encoder.h
        src/encoder/payload_encoder.cpp
        include/encoder/payload_encoder.h
)
