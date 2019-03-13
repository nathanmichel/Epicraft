//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Handshaking
//

#pragma once

#include "Epicraft.hpp"

namespace prot {
	class Handshaking {
	public:
		Handshaking();

		void parseProtocol(char *data, int size);
	};
}
