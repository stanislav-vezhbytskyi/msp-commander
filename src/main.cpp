#include "../include/dto/msp_dto.h"
#include "../include/decoder/msp_parser.h"

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cstdint>

#include "decoder/handler/msp_dto_handler.h"


int main() {

    std::cout<<"start parsing"<<std::endl;
    int fd = open("mock_msp_raw_imu.bin", O_RDONLY);
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
    MSPParser mspParser;


    std::cout<<"start parsing"<<std::endl;
   // while(true){
        ssize_t bytesRead = read(fd, buffer.data(), buffer.size());
        std::cout<<"start parsing"<<std::endl;
        mspParser.parse(bytesRead,buffer,packets);
        
    //}

    MspDtoHandler handler;
    handler.handle(packets.back());




    std::cout << packets.back().checksum << std::endl;
    std::cout << "end program" << std::endl;
    close(fd);
    return 0;
}


