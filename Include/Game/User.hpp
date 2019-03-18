//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// User class
//

#pragma once

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
        unsigned char gamemode;
        game::Dimension dimension;
        std::string _uuid;
        // Metadata; (ça a l'air supper marrant a faire ça)

    };
}
