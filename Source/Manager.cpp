//
// EPITECH PROJECT, 2019
// Epitain
// File description:
// Manager
//

#include "Manager.hpp"

mgr::Manager::Manager() : _server(25565, *this)
{

}

void	mgr::Manager::run()
{
	std::thread server(&net::TcpServer::run, &_server);

	server.detach();
	while (1)
		sleep(1);
}

void	mgr::Manager::callback(char *data, int size, prot::Status &status)
{
	_protocol.parseProtocol(data, size, status);
}
