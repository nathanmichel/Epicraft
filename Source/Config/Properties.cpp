//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Properties class
//

#include "Properties.hpp"

config::Properties::Properties() {
    this->update();
}

bool config::Properties::refresh() {
    auto newTime = boost::filesystem::last_write_time(_file);
    if (std::difftime(_lastUpdated, newTime)) {
        this->update();
        return true;
    }
    return false;
}

void config::Properties::update() {
    _lastUpdated = boost::filesystem::last_write_time(_file);
    std::ifstream file(_file);
    std::string line;
    while (std::getline(file, line)) {
        if (line.front() == '#')
            continue;
        auto pos = line.find('=');
        if (pos == std::string::npos)
            continue;
        // TODO: Catch non refreshable proprieties
        _properties[line.substr(0, pos)] = line.substr(pos + 1, line.size());
    }
    file.close();
}

std::string &config::Properties::operator[](std::string &key) {
    return _properties.at(key);
}


// catch (boost::filesystem::filesystem_error const &e)
