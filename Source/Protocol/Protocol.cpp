//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Protocol
//

#include "Protocol.hpp"
#include "Manager.hpp"

prot::Protocol::Protocol(mgr::Manager &manager) :
	_manager(manager),
	_handshaking(manager),
	_status(manager),
	_play(manager),
	_login(manager, _play)
{
	_requests.reserve(prot::REQUEST_BUFFER_SIZE);
	_writeIdx = 0;
	_readIdx = 0;
}

void	prot::Protocol::addRequest(const net::request_t *request)
{
	MUTEX.lock();
	_requests[_readIdx] = request;
	_readIdx = (_readIdx + 1) % REQUEST_BUFFER_SIZE;
	MUTEX.unlock();
}

void	prot::Protocol::parseProtocol()
{
	while (_writeIdx != _readIdx) {
		if (_requests[_writeIdx]->status == prot::handshaking)
			_handshaking.parseProtocol(_requests[_writeIdx]);
		else if (_requests[_writeIdx]->status == prot::status)
			_status.parseProtocol(_requests[_writeIdx]);
		else if (_requests[_writeIdx]->status == prot::login)
			_login.parseProtocol(_requests[_writeIdx]);
		else if (_requests[_writeIdx]->status == prot::play)
			std::cout << "Play" << std::hex << (int) _requests[_writeIdx]->data[0] << std::endl;
		else
			std::cerr << "Invalid status\n";
		delete _requests[_writeIdx];
		_writeIdx = (_writeIdx + 1) % REQUEST_BUFFER_SIZE;
	}
	_manager.threadStopping();
}
