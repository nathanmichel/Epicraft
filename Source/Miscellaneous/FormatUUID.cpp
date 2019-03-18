//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// FormatUUID source
//

#include "FormatUUID.hpp"

std::string misc::formatUUID(std::string &uuid) {
    std::string newString(uuid);
    newString.insert(8, 1, '-');
    newString.insert(13, 1, '-');
    newString.insert(18, 1, '-');
    newString.insert(23, 1, '-');
    return newString;
}

std::string misc::basicUUID(std::string &uuid) {
    std::string newString(uuid);
    newString.erase(std::remove(newString.begin(), newString.end(), '-'), newString.end());
    return newString;
}
