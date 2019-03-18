//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Protocol
//

#pragma once

#include "Epicraft.hpp"
#include "Handshaking.hpp"
#include "Status.hpp"
#include "Login.hpp"
#include "Play.hpp"

namespace mgr {
	class Manager;
}

namespace prot {
	const std::size_t REQUEST_BUFFER_SIZE = 128;

	class Protocol {
	public:
		Protocol(mgr::Manager &manager);

		void	addRequest(const net::request_t *request);
		void	parseProtocol();

	private:
		mgr::Manager		&_manager;
		prot::Handshaking	_handshaking;
		prot::Status		_status;
		prot::Play		_play;
		prot::Login		_login;
		net::requests_t		_requests;
		std::size_t		_writeIdx;
		std::size_t		_readIdx;
	};
}
