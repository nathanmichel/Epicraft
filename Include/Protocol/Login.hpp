//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Login
//

#pragma once

#include "Epicraft.hpp"

namespace mgr {
	class Manager;
}

namespace prot {
	class Login {
	public:
		Login(mgr::Manager &manager);

		void	parseProtocol(const net::request_t *request);

	private:
		void	loginSuccess(const std::string uuid, const std::string name);
		void	parseLogin(const buffer_t &data, const int size);

	private:
		mgr::Manager	&_manager;
	};
}
