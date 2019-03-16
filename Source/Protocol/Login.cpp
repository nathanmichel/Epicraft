//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Login
//

#include "Login.hpp"
#include "Manager.hpp"

prot::Login::Login(mgr::Manager &manager) : _manager(manager)
{

}

void	prot::Login::loginSuccess(const std::string uuid, const std::string name)
{
	std::cout << "UUID : " << uuid << " pseudo :  " << name << std::endl;
	std::cout << "WTF\n";
}

void	prot::Login::parseLogin(const buffer_t &data, const int size)
{
	std::size_t offset = 1;
	int varIntSize = 0;

	try {
		int nameLength = misc::readVarInt(data, offset, size, varIntSize);
		if (nameLength > 16) {
			std::cerr << "Invalid request (the username is too long)" << std::endl;
			return;
		}
		offset += varIntSize;
		std::cout << nameLength << std::endl;
		std::string name(data.begin() + offset, data.begin() + offset + nameLength);
		loginSuccess("6f02141b-c5fa-40b2-b24d-5687562e37db", name);
	} catch (const std::exception &e) {
		std::cerr << e.what() << std::endl;
		return;
	}
}

void	prot::Login::parseProtocol(const net::request_t *request)
{
	if (request->data[0] != 0x00) {
		std::cerr << "Invalid Login" << std::endl;
		return;
	}
	parseLogin(request->data, request->size);
}
