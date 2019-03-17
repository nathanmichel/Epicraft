//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// MojangAPI header
//

#pragma once

#include <sstream>
#include <iomanip>

#include "Epicraft.hpp"
#include "Fetcher.hpp"

namespace net {
    class MojangAPI {
    public:
        MojangAPI();

        game::uuid_t getUUID(std::string &playerName);
        game::uuid_t getUUID(std::string &playerName, std::time_t time);

    private:
        game::uuid_t stringToUUID(std::string &str);
        std::string makeRequest(std::string &path);

    private:
        boost::asio::ssl::context _context;
    };
}
