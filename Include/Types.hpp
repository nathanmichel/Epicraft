//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Types
//

#pragma once

#include <vector>

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
}
