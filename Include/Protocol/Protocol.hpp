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

namespace mgr {
	class Manager;
}

namespace prot {
	class Protocol {
	public:
		Protocol(mgr::Manager &manager);

		void	addRequest(const net::request_t *request);
		void	parseProtocol();

		bool	getIsRunning() const;

	private:
		mgr::Manager		&_manager;
		prot::Handshaking	_handshaking;
		prot::Status		_status;
		net::requests_t		_requests;
		bool			_isRunning;
	};
}
