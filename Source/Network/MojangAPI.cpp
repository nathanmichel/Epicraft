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

game::uuid_t net::MojangAPI::getUUID(std::string &playerName) {
    std::string path = "/users/profiles/minecraft/" + playerName;
    std::string content = this->makeRequest(path);
    return stringToUUID(content);
}

game::uuid_t net::MojangAPI::getUUID(std::string &playerName, std::time_t time) {
    std::string path = "/users/profiles/minecraft/" + playerName + "?at=" + std::to_string(time);
    std::string content = this->makeRequest(path);
    return stringToUUID(content);
}

game::uuid_t net::MojangAPI::stringToUUID(std::string &str) {
    std::string uuidStr = str.substr(str.find("\"id\":\"") + 6, str.size());
    uuidStr = uuidStr.substr(0, uuidStr.find('\"'));
    std::stringstream stream;
    game::uuid_t uuid;
    stream << uuidStr;
    stream >> std::hex >> uuid;
    return uuid;
}

std::string net::MojangAPI::makeRequest(std::string &path) {
    boost::asio::io_service ioService;
    net::Fetcher fetch(ioService, _context, path);
    ioService.run();
    return fetch.getContent();
}
