//
// EPITECH PROJECT, 2019
// Epitain
// File description:
// Protocol
//

#pragma once

#include "Epitain.hpp"
#include "Handshaking.hpp"

namespace prot {
	enum Status {
		handshaking,
		status,
		login,
		play
	};

	class Protocol {
	public:
		Protocol();

		void	parseProtocol(char *data, int size, Status &status);

	private:
		prot::Handshaking	_handshaking;
	};
}
