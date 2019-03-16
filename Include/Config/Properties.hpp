//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Properties class
//

#pragma once

#include <boost/filesystem.hpp>
#include <ctime>

#include "Epicraft.hpp"

namespace config {
    class Properties {
    public:
        Properties();

        bool refresh();
        std::string &operator[](std::string &key);

    private:
        void update(bool refreshed);

    private:
        const std::string _file = "server.properties";
        std::time_t _lastUpdated;
        std::map<std::string, std::string> _properties = {};
        const std::vector<std::string> _nonRefresh = {
                "server-ip", "server-port", "ressource-pack",
                "level-name", "white-list", "difficulty"
        };
    };
};
