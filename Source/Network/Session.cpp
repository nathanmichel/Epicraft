//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Session
//

#include "Session.hpp"
#include "Manager.hpp"

net::Session::Session(boost::asio::io_context &ioContext, net::TcpServer &server, mgr::Manager &manager) :
	_socket(ioContext),
	_server(server),
	_manager(manager),
	_id((std::size_t) &_socket)
{

}

void		net::Session::run()
{
	listen();
}

void		net::Session::listen()
{
	async_read(_socket, boost::asio::buffer((char *) NULL, 0),
		   boost::bind(&Session::handleRead, this,
			       boost::asio::placeholders::error));
}

void		net::Session::handleRead(const boost::system::error_code &e)
{
	int size = readVarInt();
	static int it = 0;

	if (size > 0) {
		it++;
		boost::system::error_code error;
		buffer_t data(size);

		boost::asio::read(_socket, boost::asio::buffer(data, size),
				  boost::asio::transfer_exactly(size), error);

		net::request_t *request = new net::request_t { data, size, _status, _id };
		_manager.callback(request);
		listen();
	} else {
		_server.removeSession(_id);
	}
}

int		net::Session::readVarInt()
{
	boost::system::error_code error;
	char buffer;
	int numRead = 0;
	int result = 0;
	int value;

	do {
		boost::asio::read(_socket, boost::asio::buffer(&buffer, 1),
				  boost::asio::transfer_exactly(1), error);
		if (error)
			return -1;
		value = (buffer & 0b01111111);
		result = result | (value << (7 * numRead));
		numRead++;
		if (numRead > 5)
			return -1;
	} while ((buffer & 0b10000000) != 0);
	return result;
}

void				net::Session::putResponse(const net::response_t *response)
{
	if (response->size > 0)
		boost::asio::write(_socket, boost::asio::buffer(response->data, response->size));
}

boost::asio::ip::tcp::socket	&net::Session::getSocket()
{
	return _socket;
}

std::size_t	net::Session::getId() const
{
	return _id;
}
