//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// User class
//

#pragma once

#include <boost/multiprecision/cpp_int.hpp>

#include "Epicraft.hpp"

namespace game {
    class User {
    public:
        User() = default;

    private:
        int _entityId;
        double _x;
        double _y;
        double _z;
        float _yaw;
        float _pitch;
        std::byte gamemode;
        game::Dimension dimension;
        boost::multiprecision::uint128_t _uid;
        // Metadata; (ça a l'air supper marrant a faire ça)

    };
}