cmake_minimum_required(VERSION 3.10)
project(MSPCommander)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Додай інклуди
include_directories(include)

# Підключення зовнішніх бібліотек
include(FetchContent)

# Якщо ти хочеш використовувати spdlog — він уже підключений (не обов’язково, якщо Plog тобі достатньо)
FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        GIT_TAG v1.12.0
)
FetchContent_MakeAvailable(spdlog)

# Створення екзешника
add_executable(msp_parser
        src/main.cpp
        src/msp/decoder/msp_parser.cpp
        src/msp/decoder/packet_decoder.cpp


        src/msp/encoder/packet_encoder.cpp

        src/msp/encoder/payload_encoder.cpp

        src/serial/SerialPort.cpp

        src/mspcomm/msp_comm_service.cpp

        src/telemetry_logging/telemetry_log_writer.cpp


        src/telemetry/raw_to_data.cpp

        src/telemetry/data_to_raw.cpp

        src/util/config_reader.cpp
)

# External libraries
target_include_directories(msp_parser PRIVATE ${CMAKE_SOURCE_DIR}/external/plog/include)
target_link_libraries(msp_parser PRIVATE spdlog::spdlog)
