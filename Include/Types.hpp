//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Types
//

#pragma once

#include <vector>
#include <array>

typedef std::vector<char> buffer_t;

namespace prot {
	enum StateStatus {
		handshaking,
		status,
		login,
		play
	};
}

namespace net {
	typedef	struct {
		buffer_t		data;
		int			size;
		prot::StateStatus	&status;
		std::size_t		id;
	}				request_t;

	typedef struct {
		buffer_t	data;
		int		size;
		std::size_t	id;
	}			response_t;

	typedef std::vector<const net::request_t *> requests_t;
}

namespace game {
	typedef unsigned char angle_t;

	enum Dimension : int {
		nether = -1,
		overworld = 0,
		end = 1
	};
};