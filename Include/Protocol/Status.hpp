//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Status
//

#pragma once

#include "Epicraft.hpp"

namespace mgr {
	class Manager;
}

namespace prot {
	class Status {
	public:
		Status(mgr::Manager &manager);

		void	parseProtocol(const net::request_t *request);

	private:
		void	getServerInformation(const std::size_t id);
		void	parsePing(const net::request_t *request);

	private:
		mgr::Manager	&_manager;
	};
}
