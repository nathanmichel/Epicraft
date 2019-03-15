//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Handshaking
//

#pragma once

#include "Epicraft.hpp"
#include "VarInt.hpp"

namespace mgr {
	class Manager;
}

namespace prot {
	class Handshaking {
	public:
		Handshaking(mgr::Manager &manager);

		void	parseProtocol(const net::request_t *request);

	private:
		void	parseHandshake(const buffer_t &data, const int size, prot::StateStatus &status);

	private:
		mgr::Manager	&_manager;
	};
}
