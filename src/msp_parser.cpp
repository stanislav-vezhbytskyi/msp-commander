#include "msp_parser.h"

#include <cstdint>

const uint8_t MSPParser::MSP_HEADER_START = '$';  // 0x24
const uint8_t MSPParser::MSP_HEADER_MAGIC = 'M';  // 0x4D 

MSPParser::MSPParser() : parsingState(ParsingState::WaitingForHeader) {}

uint8_t MSPParser::calculateChecksum(const MSPDTO& dto) {
    uint8_t checksum = dto.length ^ dto.command;

    for (uint8_t temp : dto.payload) {
        checksum ^= temp;
    }

    return checksum;
}


void MSPParser::parse(ssize_t bytesRead, std::vector<uint8_t> &buffer, std::vector<MSPDTO> &packets) {
    if (bytesRead > 0) {
        int i = 0;
        while (i < bytesRead) {
            switch (parsingState) {
                case ParsingState::WaitingForHeader:
                    if (buffer[i] == MSP_HEADER_START) {
                        parsingState = ParsingState::ReadingProtocolType;
                    }
                    i++;
                    break;

                case ParsingState::ReadingProtocolType:
                    if (buffer[i] == MSP_HEADER_MAGIC) {
                        packets.push_back(MSPDTO{});
                        parsingState = ParsingState::ReadingDirection;
                    } else {
                        parsingState = ParsingState::WaitingForHeader;
                    }
                    i++;
                    break;

                case ParsingState::ReadingDirection:
                    if (packets.empty()) {
                        parsingState = ParsingState::WaitingForHeader;
                        break;
                    }
                    packets.back().direction = buffer[i];
                    parsingState = ParsingState::ReadingPayloadSize;
                    i++;
                    break;

                case ParsingState::ReadingPayloadSize:
                    if (packets.empty()) {
                        parsingState = ParsingState::WaitingForHeader;
                        break;
                    }
                    packets.back().length = buffer[i];
                    packets.back().payload.clear();
                    parsingState = (packets.back().length == 0) ? ParsingState::ValidatingData : ParsingState::ReadingCommand;
                    i++;
                    break;

                case ParsingState::ReadingCommand:
                    if (packets.empty()) {
                        parsingState = ParsingState::WaitingForHeader;
                        break;
                    }
                    packets.back().command = buffer[i];
                    parsingState = ParsingState::ReadingPayload;
                    i++;
                    break;

                case ParsingState::ReadingPayload:
                    if (packets.empty()) {
                        parsingState = ParsingState::WaitingForHeader;
                        break;
                    }
                    packets.back().payload.push_back(buffer[i]);

                    std::cout << "length " << packets.back().length << std::endl;
                    if (packets.back().payload.size() == packets.back().length) {
                        parsingState = ParsingState::ValidatingData;
                    }
                    i++;
                    break;

                case ParsingState::ValidatingData:
                    if (packets.empty()) {
                        parsingState = ParsingState::WaitingForHeader;
                        break;
                    }
                    if (buffer[i] == calculateChecksum(packets.back())) {
                        std::cout << "packet successfully read" << std::endl;
                        parsingState = ParsingState::WaitingForHeader;
                    } else {
                        std::cout << "checksum error" << std::endl;
                        packets.pop_back();  // discard invalid packet
                        parsingState = ParsingState::WaitingForHeader;
                    }
                    i++;
                    break;

                case ParsingState::Error:
                    if (!packets.empty()) packets.pop_back();
                    std::cout << "error" << std::endl;
                    parsingState = ParsingState::WaitingForHeader;
                    i++;
                    break;
            }
        }
    }
}
