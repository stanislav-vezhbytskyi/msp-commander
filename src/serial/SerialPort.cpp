#include "../../include/serial/SerialPort.h"


#include <fcntl.h>
#include <termio.h>
#include <unistd.h>


bool SerialPort::open(const std::string &device, int baudrate) {
    fd = ::open(device.c_str(), O_RDWR | O_NOCTTY | O_SYNC);

    if (fd == -1) {
        perror("open");
        return false;
    }

    if (tcgetattr(fd, &tty) != 0) {
        perror("tcgetattr");
        return false;
    }

    setUp();

    return true;
}
void SerialPort::close() {
    if (fd != -1) {
        ::close(fd);
        fd = -1;
    }

}
bool SerialPort::isOpen() const {
    return fd != -1;
}
bool SerialPort::write(const void *data, size_t size) {
    ssize_t written = ::write(fd, data, size);
    return written == static_cast<ssize_t>(size);
}

ssize_t SerialPort::read(uint8_t* buffer, size_t maxSize) {
    return ::read(fd, buffer, maxSize);
}


void SerialPort::setUp() {
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
    tty.c_cflag &= ~CRTSCTS;
    tcsetattr(fd, TCSANOW, &tty);
}