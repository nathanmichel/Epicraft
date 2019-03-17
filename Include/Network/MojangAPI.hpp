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
#include "HexUUID.hpp"
#include "Base64.hpp"

namespace net {
    class MojangAPI {
    public:
        MojangAPI();

        game::uuid_t getUUID(std::string &playerName);
        game::uuid_t getUUID(std::string &playerName, std::time_t time);
        std::vector<std::string> getNameHistory(game::uuid_t &uuid);
        game::playerSkin_t getProfile(game::uuid_t &uuid);

    private:
        std::string parseKey(std::string &str, std::string key);
        std::string makeRequest(const std::string &path, std::string host = "api.mojang.com");

    private:
        boost::asio::ssl::context _context;
    };
}
