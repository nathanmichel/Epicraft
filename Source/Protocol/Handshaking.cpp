//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Handshaking
//

#include "Handshaking.hpp"
#include "Manager.hpp"
#include "Protocol.hpp"

prot::Handshaking::Handshaking(mgr::Manager &manager) : _manager(manager)
{

}

void	prot::Handshaking::parseHandshake(const buffer_t &data, const int size, prot::StateStatus &status)
{
	std::size_t offset = 1; // To skip Packet ID

	try {
		int version = misc::readVarInt(data, offset, size);
		int addressLength = misc::readVarInt(data, offset, size);
		std::string address(data.begin() + offset, data.begin() + offset + addressLength);
		offset += addressLength;
		unsigned short port = ((unsigned char) data[offset] << 8) | ((unsigned char) data[offset + 1]);
		offset += 2;
		if (data[offset] == prot::status || data[offset] == prot::login) {
			status = (prot::StateStatus) data[offset];
		}
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return;
	}
}

void	prot::Handshaking::parseProtocol(const net::request_t *request)
{
	if (request->data[0] != 0x00) {
		std::cerr << "Invalid Handshake" << std::endl;
		return;
	}
	parseHandshake(request->data, request->size, request->status);
}
