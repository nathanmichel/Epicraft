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
//#include "Manager.hpp"

namespace mgr {
	class Manager;
}

namespace net {
	class Session;

	class TcpServer {
	public:
		TcpServer(const unsigned short port, mgr::Manager &manager);

		void	run();
		void	stop();

		void	removeSession(const std::size_t id);

	private:
		void	listen();
		void	handleAccept(Session *session, const boost::system::error_code &e);

	private:
		mgr::Manager				&_manager;
		boost::asio::io_context			_ioContext;
		boost::asio::ip::tcp::acceptor		_acceptor;
		std::list< std::shared_ptr<Session> >	_sessions;
	};
}
