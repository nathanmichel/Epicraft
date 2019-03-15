//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// VarInt
//

#pragma once

#include "Epicraft.hpp"

namespace misc {
	int	readVarInt(const buffer_t &data, const std::size_t offset, const int size, int &resSize);
	void	writeVarInt(unsigned int value, buffer_t &data);

	int	getVarIntSize(unsigned int value);
}
