//
// EPITECH PROJECT, 2019
// Epitain
// File description:
// HandshakingProtocol
//

#pragma once

#include "Epitain.hpp"

namespace prot {
	class HandshakingProtocol {
	public:
		HandshakingProtocol();

		void parseProtocol(char *data, int size);
	};
}
