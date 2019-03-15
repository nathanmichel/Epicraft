//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// VarInt
//

#include "VarInt.hpp"

int     misc::readVarInt(const buffer_t &data, const std::size_t offset, const int size, int &resSize)
{
	int result = 0;
	int value;

	resSize = 0;
	if (size <= 0 || resSize + offset >= size)
		throw std::runtime_error("The string is empty");
	do {
		value = (data[resSize + offset] & 0b01111111);
		result = result | (value << (7 * resSize));
		resSize++;
		if (resSize > 5)
			throw std::runtime_error("The number is too big");
	} while ((data[resSize + offset - 1] & 0b10000000) != 0 && resSize + offset < size); //-1 cause of incr b4
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
