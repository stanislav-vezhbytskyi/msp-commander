#include "pid_forwarder.h"

#include <any>
#include <iostream>

void PIDForwarder::forward(const std::any& data) {
    try {
        std::cout << "Forwarded data: " << std::any_cast<std::string>(data) << std::endl;
    } catch (const std::bad_any_cast& e) {
        std::cerr << "Failed to cast forwarded data." << std::endl;
    }
}
