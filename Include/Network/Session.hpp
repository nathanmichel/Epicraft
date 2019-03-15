//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Session
//

#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/array.hpp>
#include "Epicraft.hpp"
#include "TcpServer.hpp"

namespace mgr {
	class Manager;
}

namespace net {
	class TcpServer;

	class Session {
	public:
		Session(boost::asio::io_context &ioContext, net::TcpServer &server, mgr::Manager &manager);

		void				run();

		void				putResponse(const net::response_t *response);

		boost::asio::ip::tcp::socket	&getSocket();
		std::size_t			getId() const;

	private:
		void				listen();
		void				handleRead(const boost::system::error_code &e);
		int				readVarInt();

	private:
		boost::asio::ip::tcp::socket	_socket;
		net::TcpServer			&_server;
		mgr::Manager			&_manager;
		const std::size_t		_id;
		prot::StateStatus		_status = prot::handshaking;
	};
}
