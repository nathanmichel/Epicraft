//
// EPITECH PROJECT, 2019
// Epitain
// File description:
// Protocol
//

#include "Protocol.hpp"

prot::Protocol::Protocol()
{

}

void	prot::Protocol::parseProtocol(char *data, int size, Status &status)
{
	if (status == prot::handshaking)
		_handshaking.parseProtocol(data, size);
	else if (status == prot::status)
		std::cout << "Status\n";
	else if (status == prot::login)
		std::cout << "Login\n";
	else if (status == prot::play)
		std::cout << "Play\n";
	else
		std::cerr << "Invalid status\n";
}
