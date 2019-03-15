//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// TcpServer
//

#include "TcpServer.hpp"

net::TcpServer::TcpServer(const unsigned short port, mgr::Manager &manager) :
	_manager(manager),
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
	Session *session = new Session(_acceptor.get_executor().context(), *this, _manager);

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
	} else {
		delete session;
	}
	listen();
}

void	net::TcpServer::stop()
{
	_sessions.clear();
	_ioContext.stop();
}

void	net::TcpServer::removeSession(const std::size_t id)
{
	_sessions.erase(std::remove_if(_sessions.begin(),
				       _sessions.end(),
				       [id](std::shared_ptr<net::Session> s) { return s->getId() == id; }),
			_sessions.end());
}

void	net::TcpServer::putResponse(const net::response_t *response)
{
	for (auto session : _sessions) {
		if (session->getId() == response->id) {
			session->putResponse(response);
			return;
		}
	}
}
