//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Properties class
//

#include "Properties.hpp"

config::Properties::Properties() {
    this->update(false);
}

bool config::Properties::refresh() {
    try {
        auto newTime = boost::filesystem::last_write_time(_file);
        if (std::difftime(_lastUpdated, newTime)) {
            this->update(true);
            return true;
        }
    } catch (boost::filesystem::filesystem_error const &e) {
        std::cerr << "Can't find " + _file << std::endl;
    }
    return false;
}

void config::Properties::update(bool refreshed) {
    _lastUpdated = boost::filesystem::last_write_time(_file);
    std::ifstream file(_file);
    std::string line;
    while (std::getline(file, line)) {
        if (line.front() == '#')
            continue;
        auto pos = line.find('=');
        if (pos == std::string::npos)
            continue;
        std::string key = line.substr(0, pos);
        std::string value = line.substr(pos + 1, line.size());
        if (refreshed && _properties[key] != value
            && std::find(_nonRefresh.begin(), _nonRefresh.end(), key) != _nonRefresh.end())
            misc::toLog("Config", "To use the new value of " + key + ", you need to restart the server.");
        else
            _properties[key] = value;
    }
    file.close();
}

std::string &config::Properties::operator[](std::string &key) {
    return _properties.at(key);
}
