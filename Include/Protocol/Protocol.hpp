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

		static int	readVarInt(const buffer_t &data, const std::size_t offset,
					   const int size, int &resSize);
		static void	writeVarInt(unsigned int value, buffer_t &data);
		static int	getVarIntSize(unsigned int value);

	private:
		mgr::Manager		&_manager;
		prot::Handshaking	_handshaking;
		prot::Status		_status;
		std::vector<const net::request_t *>	_requests;
	};
}
