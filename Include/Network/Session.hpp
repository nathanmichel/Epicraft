//
// EPITECH PROJECT, 2019
// Epitain
// File description:
// Session
//

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include "Epitain.hpp"

namespace net {
	class Session {
	public:
		Session(boost::asio::io_context &ioContext);

		void	run();
		boost::asio::ip::tcp::socket	&getSocket();

	private:
		void	listen();
		void	handleRead(const boost::system::error_code &e);
		int	readVarInt();

	private:
		boost::asio::ip::tcp::socket	_socket;
		unsigned char				_buffer;
	};
}
