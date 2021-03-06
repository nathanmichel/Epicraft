//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Manager
//

#pragma once

#include <thread>
#include <unistd.h>
#include "Epicraft.hpp"
#include "TcpServer.hpp"
#include "Protocol.hpp"

namespace prot {
	class Protocol;
}

namespace mgr {
	class Manager {
	public:
		Manager();

		void	run();

		void	callback(const net::request_t *request);
		void	callback(const net::response_t *response);

		void	threadStopping();

	private:
		net::TcpServer	_server;
		prot::Protocol	_protocol;
		bool		_threadRunning;
	};
}
