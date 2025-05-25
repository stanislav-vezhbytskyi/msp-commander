#ifndef MSP_DTO_H
#define MSP_DTO_H

#include <vector>
#include <cstdint>

struct MSPDTO {
    uint8_t direction;
    uint8_t length;
    uint8_t command;
    std::vector<uint8_t> payload;
    uint8_t checksum;
};

#endif 
