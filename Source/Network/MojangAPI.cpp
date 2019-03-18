//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// MojangAPI source
//

#include "MojangAPI.hpp"

net::MojangAPI::MojangAPI() : _context(boost::asio::ssl::context::sslv23) {
    _context.set_default_verify_paths();
}

std::string net::MojangAPI::getUUID(std::string &playerName) {
    std::string path = "/users/profiles/minecraft/" + playerName;
    std::string content = this->makeRequest(path);
    std::string uuid = parseKey(content, "id");
    return misc::formatUUID(uuid);
}

std::string net::MojangAPI::getUUID(std::string &playerName, std::time_t time) {
    std::string path = "/users/profiles/minecraft/" + playerName + "?at=" + std::to_string(time);
    std::string content = this->makeRequest(path);
    std::string uuid = parseKey(content, "id");
    return misc::formatUUID(uuid);
}

std::vector<std::string> net::MojangAPI::getNameHistory(std::string &uuid) {
    std::vector<std::string> names = {};
    std::string path = "/user/profiles/" + misc::basicUUID(uuid) + "/names";
    std::string content = this->makeRequest(path);
    while (content.find("\"name\":\"") != std::string::npos) {
        content = content.substr(content.find("\"name\":\"") + 8, content.size());
        std::string name = content.substr(0, content.find('\"'));
        names.push_back(name);
    }
    return names;
}

game::playerSkin_t net::MojangAPI::getProfile(std::string &uuid) {
    std::string path = "/session/minecraft/profile/" + misc::basicUUID(uuid);
    std::string content = this->makeRequest(path, "sessionserver.mojang.com");
    std::string base64Str = parseKey(content, "value");
    std::string textures = misc::base64Decode(base64Str);
    game::playerSkin_t skin;
    skin.timestamp = std::strtol(parseKey(textures, "timestamp").c_str(), nullptr, 10);
    skin.uuid = uuid;
    skin.name = parseKey(textures, "profileName");
    skin.skinUrl = parseKey(textures, "url");
    if (textures.find("\"model\":\"") != std::string::npos)
        skin.modelType = game::slim;
    if (textures.find("\"CAPE\":\"") != std::string::npos) {
        textures = textures.substr(textures.find("\"CAPE\":\"") + 8, textures.size());
        skin.capeUrl = parseKey(textures, "url");
    }
    return skin;
}

std::string net::MojangAPI::parseKey(std::string &str, std::string key) {
    std::string value = str.substr(str.find("\"" + key + "\":") + 3 + key.size(), str.size());
    if (value.front() == '\"')
        value = value.substr(1, value.size());
    value = value.substr(0, value.find('\"'));
    return value;
}

std::string net::MojangAPI::makeRequest(const std::string &path, const std::string host) {
    boost::asio::io_service ioService;
    net::Fetcher fetch(ioService, _context, path, host);
    ioService.run();
    return fetch.getContent();
}
