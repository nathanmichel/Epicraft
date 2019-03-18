//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// MojangAPI header
//

#pragma once

#include <cstdlib>

#include "Epicraft.hpp"
#include "Fetcher.hpp"
#include "FormatUUID.hpp"
#include "Base64.hpp"

namespace net {
    class MojangAPI {
    public:
        MojangAPI();

        std::string getUUID(std::string &playerName);
        std::string getUUID(std::string &playerName, std::time_t time);
        std::vector<std::string> getNameHistory(std::string &uuid);
        game::playerSkin_t getProfile(std::string &uuid);

    private:
        std::string parseKey(std::string &str, std::string key);
        std::string makeRequest(const std::string &path, std::string host = "api.mojang.com");

    private:
        boost::asio::ssl::context _context;
    };
}
