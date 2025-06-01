#ifndef MSP_PARSER_H
#define MSP_PARSER_H

#include <vector>
#include "dto/msp_dto.h"
#include "parsing_state.h"
#include <iostream>

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
