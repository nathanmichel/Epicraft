//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// VarInt
//

#pragma once

#include "Epicraft.hpp"

namespace misc {
	int	readVarInt(const buffer_t &data, std::size_t &offset, const int size);
	void	writeVarInt(unsigned int value, buffer_t &data);

	int	getVarIntSize(unsigned int value);
}
