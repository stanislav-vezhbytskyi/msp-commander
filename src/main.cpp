#include "../include/msp-dto.h"
#include "../include/parsing_state.h"
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include "../include/msp-parser.h"

int main() {
    int fd = open("../test/resources/mock_msp.bin", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    //for configuration msp
    // termios tty;
    // tcgetattr(fd, &tty);
    // cfsetispeed(&tty, B115200);
    // cfsetospeed(&tty, B115200);
    // // ...налаштування tty...
    // tcsetattr(fd, TCSANOW, &tty);

    std::vector<uint8_t> buffer(64);
    std::vector<MSPDTO> packets;
    ParsingState parsingState = ParsingState::WaitingForHeader;
    MSPParser mspParser;


    while(true){
        ssize_t bytesRead = read(fd, buffer.data(), buffer.size());
        mspParser.parse(bytesRead,buffer,packets);
        
    }
    

    std::cout << packets.back().checksum << std::endl;
    std::cout << "end program" << std::endl;
    close(fd);
    return 0;
}


