//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// VarInt
//

#include "VarInt.hpp"

int     misc::readVarInt(const buffer_t &data, std::size_t &offset, const int size)
{
	int result = 0;
	int nbrSize = 0;
	int value;

	if (size <= 0 || offset >= size)
		throw std::runtime_error("The string is empty");
	do {
		value = (data[offset] & 0b01111111);
		result = result | (value << (7 * nbrSize));
		offset++;
		nbrSize++;
		if (nbrSize > 5)
			throw std::runtime_error("The number is too big");
	} while ((data[offset - 1] & 0b10000000) != 0 && offset < size); //-1 cause of incr b4
	return result;
}

void    misc::writeVarInt(unsigned int value, buffer_t &data)
{
	std::size_t resSize = 0;

	do {
		char temp = (char) (value & 0b01111111);

		value >>= 7;
		if (value != 0) {
			temp |= 0b10000000;
		}
		data.push_back(temp);
		resSize++;
	} while (value != 0);
}

int     misc::getVarIntSize(unsigned int value)
{
	std::size_t i = 0;

	do {
		char temp = (char) (value & 0b01111111);

		value >>= 7;
		if (value != 0) {
			temp |= 0b10000000;
		}
		i++;
	} while (value != 0);
	return i;
}
