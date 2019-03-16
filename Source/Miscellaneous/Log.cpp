//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Log sources
//

#include "Log.hpp"

void    misc::toLog(std::string context, std::string msg) {
    std::time_t t = std::time(0);
    std::tm *now = std::localtime(&t);
    std::cout << "[" << std::setw(2) << std::setfill('0') << now->tm_hour << ":";
    std::cout << std::setw(2) << std::setfill('0') << now->tm_min << ":";
    std::cout << std::setw(2) << std::setfill('0') << now->tm_sec << "] ";
    std::cout << "[" << context << "]: " << msg << std::endl;
}
