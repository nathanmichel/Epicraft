//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// UUID source
//

#include "HexUUID.hpp"

game::uuid_t misc::hexToUUID(std::string &hex) {
    std::stringstream stream;
    game::uuid_t uuid;
    stream << hex;
    stream >> std::hex >> uuid;
    return uuid;
}

std::string misc::UUIDToHex(game::uuid_t &uuid) {
    std::stringstream stream;
    stream << std::hex << uuid;
    return stream.str();
}
