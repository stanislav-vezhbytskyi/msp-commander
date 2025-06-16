#pragma once

#include <cstdint>
#include <string>
#include <termios.h>

class SerialPort {
public:
    bool open(const std::string& device, int baudrate);
    void close();
    //bool write(const uint8_t* data, size_t size);
    bool write(const void *data, size_t size);
    ssize_t read(uint8_t* buffer, size_t maxSize);
    bool isOpen() const;
private:
    void setUp();
    int fd = -1;
    termios tty{};
};
