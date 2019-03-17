//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Base64 header
//

#pragma once

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "Epicraft.hpp"

namespace misc {
    game::uuid_t hexToUUID(std::string &hex);
    std::string	UUIDToHex(game::uuid_t &uuid);
};
