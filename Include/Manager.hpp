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

		void	callbackServer(const net::request_t *request);
		void	callbackProtocol(const net::response_t *response);

	private:
		net::TcpServer	_server;
		prot::Protocol	_protocol;
		std::thread	_thread;
	};
}
