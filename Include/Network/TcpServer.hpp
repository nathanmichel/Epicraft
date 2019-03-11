//
// EPITECH PROJECT, 2019
// Epitain
// File description:
// TcpServer
//

#pragma once

#include <list>
#include "Epitain.hpp"
#include "Session.hpp"

namespace net {
	class TcpServer {
	public:
		TcpServer(const unsigned short port);

		void	run();
		void	stop();

	private:
		void	listen();
		void	handleAccept(Session *session, const boost::system::error_code &e);

	private:
		boost::asio::io_context			_ioContext;
		boost::asio::ip::tcp::acceptor		_acceptor;
		std::list<std::shared_ptr<Session>>	_sessions;
	};
}
