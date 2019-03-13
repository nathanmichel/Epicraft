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

namespace mgr {
	class Manager {
	public:
		Manager();

		void	run();
		void	callback(char *data, int size, prot::Status &status);

	private:
		net::TcpServer	_server;
		prot::Protocol	_protocol;
	};
}
