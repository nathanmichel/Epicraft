//
// EPITECH PROJECT, 2019
// Epitain
// File description:
// Handshaking
//

#pragma once

#include "Epitain.hpp"

namespace prot {
	class Handshaking {
	public:
		Handshaking();

		void parseProtocol(char *data, int size);
	};
}
