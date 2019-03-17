//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Base64 source
// Program found at: https://renenyffenegger.ch/notes/development/Base64/Encoding-and-decoding-base-64-with-cpp
//

#include "Base64.hpp"

const std::string base64Chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

static inline bool isBase64(unsigned char c) {
    return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string	misc::base64Encode(std::string path) {
    std::ifstream file(path);
    std::string str((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());
    file.close();
    return base64Encode(str.c_str(), str.size());
}

std::string	misc::base64Encode(char const *bytesToEncode, int len) {
    std::string ret;
    int i = 0;
    int j = 0;
    char charArray3[3];
    char charArray4[4];

    while (len--) {
        charArray3[i++] = *(bytesToEncode++);
        if (i == 3) {
            charArray4[0] = (charArray3[0] & 0xfc) >> 2;
            charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4);
            charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6);
            charArray4[3] = charArray3[2] & 0x3f;
            for (i = 0; (i < 4); i++)
                ret += base64Chars[charArray4[i]];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            charArray3[j] = '\0';
        charArray4[0] = ( charArray3[0] & 0xfc) >> 2;
        charArray4[1] = ((charArray3[0] & 0x03) << 4) + ((charArray3[1] & 0xf0) >> 4);
        charArray4[2] = ((charArray3[1] & 0x0f) << 2) + ((charArray3[2] & 0xc0) >> 6);
        for (j = 0; (j < i + 1); j++)
            ret += base64Chars[charArray4[j]];
        while ((i++ < 3))
            ret += '=';
    }
    return ret;
}

std::string misc::base64Decode(std::string const &encodedStr) {
    int len = encodedStr.size();
    int i = 0;
    int j = 0;
    int in = 0;
    unsigned char charArray4[4];
    unsigned char charArray3[3];
    std::string ret;

    while (len-- && (encodedStr[in] != '=') && isBase64(encodedStr[in])) {
        charArray4[i++] = encodedStr[in];
        in++;
        if (i == 4) {
            for (i = 0; i < 4; i++)
                charArray4[i] = base64Chars.find(charArray4[i]);
            charArray3[0] = ( charArray4[0] << 2       ) + ((charArray4[1] & 0x30) >> 4);
            charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
            charArray3[2] = ((charArray4[2] & 0x3) << 6) +   charArray4[3];
            for (i = 0; (i < 3); i++)
                ret += charArray3[i];
            i = 0;
        }
    }

    if (i) {
        for (j = 0; j < i; j++)
            charArray4[j] = base64Chars.find(charArray4[j]);
        charArray3[0] = (charArray4[0] << 2) + ((charArray4[1] & 0x30) >> 4);
        charArray3[1] = ((charArray4[1] & 0xf) << 4) + ((charArray4[2] & 0x3c) >> 2);
        for (j = 0; (j < i - 1); j++) ret += charArray3[j];
    }
    return ret;
}
