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
#include "TcpServer.hpp"
#include "Protocol.hpp"

namespace mgr {
	class Manager;
}

namespace net {
	class TcpServer;

	class Session {
	public:
		Session(boost::asio::io_context &ioContext, net::TcpServer &server, mgr::Manager &manager);

		void				run();

		boost::asio::ip::tcp::socket	&getSocket();
		std::size_t			getId() const;

	private:
		void				listen();
		void				handleRead(const boost::system::error_code &e);
		int				readVarInt();
		void				writeVarInt(unsigned int value);

	private:
		boost::asio::ip::tcp::socket	_socket;
		net::TcpServer			&_server;
		mgr::Manager			&_manager;
		const std::size_t		_id;
		prot::Status			_status = prot::handshaking;
		//char				_buffer[8192 * 2];
		//int				_i = 0;
	};
}