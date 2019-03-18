//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Play
//

#pragma once

#include "Epicraft.hpp"

namespace mgr {
	class Manager;
}

namespace prot {
	class Play {
	public:
		Play(mgr::Manager &manager);

		void	joinGame(const net::request_t *request);
		void	parseProtocol(const net::request_t *request);

	private:
		void	playerPositionAndLook(const net::request_t *request);
		void	playerAbilities(const net::request_t *request);
		void	spawnPosition(const net::request_t *request);

	private:
		mgr::Manager	&_manager;
	};
}
