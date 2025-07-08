#pragma once
#include <unordered_map>

#include "config_dto.h"


class ConfigReader {
public:
    ConfigDTO readConfig(std::string path);
};
