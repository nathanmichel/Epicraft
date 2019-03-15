//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Protocol
//

#include "Protocol.hpp"
#include "Manager.hpp"

prot::Protocol::Protocol(mgr::Manager &manager) : _manager(manager), _handshaking(manager), _status(manager)
{

}

void	prot::Protocol::addRequest(const net::request_t *request)
{
	_requests.push_back(request);
}

void	prot::Protocol::parseProtocol()
{
	for (auto request : _requests) {
		if (request->status == prot::handshaking)
			_handshaking.parseProtocol(request);
		else if (request->status == prot::status)
			_status.parseProtocol(request);
		else if (request->status == prot::login)
			std::cout << "Login\n";
		else if (request->status == prot::play)
			std::cout << "Play\n";
		else
			std::cerr << "Invalid status\n";
	}
	std::cout << "ca clear\n";
	_requests.clear();
}

int	prot::Protocol::readVarInt(const buffer_t &data, const std::size_t offset, const int size, int &resSize)
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

void	prot::Protocol::writeVarInt(unsigned int value, buffer_t &data)
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

int	prot::Protocol::getVarIntSize(unsigned int value)
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
