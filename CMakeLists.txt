cmake_minimum_required(VERSION 3.10)
project(MSPCommander)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

add_executable(msp_parser
    src/main.cpp
        src/decoder/msp_parser.cpp
        include/decoder/payload-decoders/idecoder.h
        src/decoder/payload-decoders/pid_decoder.cpp
        include/decoder/payload-decoders/pid_decoder.h
        "src/decoder/handler/msp_dto_handler.cpp"
        "include/decoder/handler/msp_dto_handler.h"
        include/decoder/forwarder/data_forwarder.h
        src/decoder/payload-decoders/decoder_factory.cpp
        include/decoder/payload-decoders/decoder_factory.h
        include/decoder/docoded_types.h
        src/decoder/payload-decoders/status_decoder.cpp
        include/decoder/payload-decoders/status_decoder.h
        src/decoder/forwarder/data_forwarder.cpp
        src/decoder/payload-decoders/raw_imu_decoder.cpp
        include/decoder/payload-decoders/raw_imu_decoder.h
        src/decoder/payload-decoders/attitude_decoder.cpp
        include/decoder/payload-decoders/attitude_decoder.h
        src/decoder/payload-decoders/rc_decoder.cpp
        include/decoder/payload-decoders/rc_decoder.h
        src/encoder/payload-encoders/pid_encoder.cpp
        include/encoder/payload-encoders/pid_encoder.h
        src/encoder/payload-encoders/raw_imu_encoder.cpp
        include/encoder/payload-encoders/raw_imu_encoder.h
        src/encoder/payload-encoders/attitude_encoder.cpp
        include/encoder/payload-encoders/attitude_encoder.h
        src/encoder/payload-encoders/rc_encoder.cpp
        include/encoder/payload-encoders/rc_encoder.h
        src/encoder/payload-encoders/status_encoder.cpp
        include/encoder/payload-encoders/status_encoder.h
)
