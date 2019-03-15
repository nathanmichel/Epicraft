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
	_isRunning = false;
}

void	prot::Protocol::addRequest(const net::request_t *request)
{
	_requests.push_back(request);
}

void	prot::Protocol::parseProtocol()
{
	_isRunning = true;
	for (std::size_t i = 0 ; i < _requests.size() ; i++) {
		if (_requests[i]->status == prot::handshaking)
			_handshaking.parseProtocol(_requests[i]);
		else if (_requests[i]->status == prot::status)
			_status.parseProtocol(_requests[i]);
		else if (_requests[i]->status == prot::login)
			std::cout << "Login\n";
		else if (_requests[i]->status == prot::play)
			std::cout << "Play\n";
		else
			std::cerr << "Invalid status\n";
	}
	_requests.clear();
	_isRunning = false;
}

bool	prot::Protocol::getIsRunning() const
{
	return _isRunning;
}
