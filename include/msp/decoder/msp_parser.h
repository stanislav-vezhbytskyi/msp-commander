#ifndef MSP_PARSER_H
#define MSP_PARSER_H

#include <cstdint>
#include <vector>
#include <iostream>
#include "parsing_state.h"
#include "msp/msp_dto.h"

enum class ParsingState;

class MSPParser {
private:
    ParsingState parsingState;

    static const uint8_t MSP_HEADER_START;  
    static const uint8_t MSP_HEADER_MAGIC;

    uint8_t calculateChecksum(const MSPDTO& dto) ;
public:
    MSPParser();  
    void parse(ssize_t bytesRead, std::vector<uint8_t> &buffer, std::vector<MSPDTO> &packets);
};

#endif
