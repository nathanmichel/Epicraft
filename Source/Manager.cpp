//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Manager
//

#include "Manager.hpp"

mgr::Manager::Manager() : _server(25565, *this), _protocol(*this)
{

}

void	mgr::Manager::run()
{
	std::thread server(&net::TcpServer::run, &_server);

	server.detach();
	while (1)
		sleep(1);
}

void	mgr::Manager::callback(const net::request_t *request)
{
	_protocol.addRequest(request);
	if (!_protocol.getIsRunning()) {
		_thread = std::thread(&prot::Protocol::parseProtocol, &_protocol);
		_thread.detach();
	}
}

void	mgr::Manager::callback(const net::response_t *response)
{
	_server.putResponse(response);
}
