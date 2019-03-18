//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Login
//

#pragma once

#include "Epicraft.hpp"
#include "Play.hpp"
#include "MojangAPI.hpp"
#include "Log.hpp"

namespace mgr {
	class Manager;
}

namespace prot {
	class Login {
	public:
		Login(mgr::Manager &manager, prot::Play &play);

		void	parseProtocol(const net::request_t *request);

	private:
		void	loginSuccess(const std::string uuid, const std::string name, const net::request_t *req);
		void	parseLogin(const net::request_t *request);

	private:
		mgr::Manager	&_manager;
		prot::Play	&_play;
		net::MojangAPI	_mojangAPI;
	};
}
