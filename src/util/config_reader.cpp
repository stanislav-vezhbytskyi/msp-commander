#include "../../include/util/config_reader.h"

#include <unordered_map>

#include "fstream"
#include "spdlog/fmt/bundled/ranges.h"
#include "util/config_dto.h"

static ConfigDTO mapResult(std::unordered_map<std::string, std::string> &conf) {
    ConfigDTO dto;
    dto.logFilePath = conf["logFilePath"];
    dto.serialDevice = conf["serialDevice"];
    dto.baudRate = std::stoi(conf["baudRate"]);
    return std::move(dto);
}

ConfigDTO ConfigReader::readConfig(std::string path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        throw std::runtime_error("Config file not found: " + path);
    }

    std::unordered_map<std::string, std::string> conf;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        int pos = line.find('=');

        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1);
        conf[key] = value;
    }
    file.close();
    return mapResult(conf);
}
