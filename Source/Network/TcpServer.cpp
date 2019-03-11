//
// EPITECH PROJECT, 2019
// Epitain
// File description:
// TcpServer
//

#include "TcpServer.hpp"

net::TcpServer::TcpServer(const unsigned short port) :
	_acceptor(_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{

}

void	net::TcpServer::run()
{
	this->listen();
	_ioContext.run();
}

void	net::TcpServer::listen()
{
	Session *session = new Session(_acceptor.get_executor().context());

	_acceptor.async_accept(session->getSocket(),
			       boost::bind(&TcpServer::handleAccept, this, session,
					   boost::asio::placeholders::error));
}

void	net::TcpServer::handleAccept(Session *session,
				     const boost::system::error_code &e)
{
	if (!e) {
		_sessions.push_front(std::unique_ptr<Session>(session));
		session->run();
	}
	else
		delete session;
	listen();
}

void	net::TcpServer::stop()
{
	_sessions.clear();
	_ioContext.stop();
}
