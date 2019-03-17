//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Base64 header
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>

namespace misc {
    std::string	base64Encode(std::string path);
    std::string	base64Encode(char const *bytesToEncode, int len);
    std::string base64Decode(std::string const &encodedStr);
};
