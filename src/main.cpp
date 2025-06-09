#include "../include/msp/msp_dto.h"

#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <cstdint>
#include <termio.h>

#include "msp/decoder/msp_parser.h"
#include "msp/decoder/packet_decoder.h"


int main() {
    int fd = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_SYNC);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    termios tty{};
    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        return 1;
    }
    tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
    tty.c_iflag &= ~IGNBRK;                         // disable break processing
    tty.c_lflag = 0;                                // no signaling chars, no echo
    tty.c_oflag = 0;                                // no remapping, no delays
    tty.c_cc[VMIN]  = 1;                            // read doesn't block
    tty.c_cc[VTIME] = 1;                            // 0.1 seconds read timeout

    tty.c_iflag &= ~(IXON | IXOFF | IXANY);         // shut off xon/xoff ctrl
    tty.c_cflag |= (CLOCAL | CREAD);                // ignore modem controls, enable reading
    tty.c_cflag &= ~(PARENB | PARODD);              // no parity
    tty.c_cflag &= ~CSTOPB;                         // 1 stop bit
    tty.c_cflag &= ~CRTSCTS;                        // no hardware flow control

    if (tcsetattr(fd, TCSANOW, &tty) != 0) {
        perror("tcsetattr");
        return 1;
    }

    std::vector<uint8_t> msp_ident = {
        '$', 'M', '<', 0, 108, 108  // code 1, checksum = 0 ^ 1 = 1
    };

    ssize_t written = write(fd, msp_ident.data(), msp_ident.size());
    if (written == -1) {
        perror("write");
        return 1;
    }

    std::cout << "Sent: " << msp_ident.size() << " bytes\n";

    usleep(100 * 1000);

    std::vector<uint8_t> buffer(64);
    std::vector<MSPDTO> packets;
    MSPParser mspParser;


    std::cout << "start parsing" << std::endl;

    ssize_t bytesRead = read(fd, buffer.data(), buffer.size());

    if (sizeof(buffer) > 4) {

        std::cout << "something there"<< std::endl;

    }

    for (int i = 0; i < bytesRead; ++i)
        printf("0x%02X ", buffer[i]);
    printf("\n");

    mspParser.parse(bytesRead, buffer, packets);


    MSPDTO dto = packets.back();

    std::cout << "MSPDTO { "
              << "direction: " << +dto.direction << ", "
              << "length: " << +dto.length << ", "
              << "command: " << +dto.command << ", "
              << "payload: [";

    for (size_t i = 0; i < dto.payload.size(); ++i) {
        std::cout << "0x" << std::hex << +dto.payload[i] << std::dec;
        if (i + 1 < dto.payload.size()) std::cout << ", ";
    }

    std::cout << "], checksum: 0x" << std::hex << +dto.checksum << std::dec << " }" << std::endl;







    std::cout << "end program" << std::endl;
    close(fd);
    return 0;
}