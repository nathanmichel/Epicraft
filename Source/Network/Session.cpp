//
// EPITECH PROJECT, 2019
// Epitain
// File description:
// Session
//

#include "Session.hpp"

net::Session::Session(boost::asio::io_context &ioContext) :
	_socket(ioContext)
{

}

void	net::Session::run()
{
	listen();
}

void	net::Session::listen()
{
	async_read(_socket, boost::asio::buffer((char *) NULL, 0),
		   boost::bind(&Session::handleRead, this,
			       boost::asio::placeholders::error));
}

void	net::Session::handleRead(const boost::system::error_code &e)
{
	int size = readVarInt();
	boost::system::error_code error;
	char *data = new char[size];

	boost::asio::read(_socket, boost::asio::buffer(data, size),
			  boost::asio::transfer_exactly(size), error);
	write(1, data, size);
	listen();
}

int	net::Session::readVarInt()
{
	boost::system::error_code error;
	int numRead = 0;
	int result = 0;

	do {
		boost::asio::read(_socket, boost::asio::buffer(&_buffer, 1),
				  boost::asio::transfer_exactly(1), error);
		if (error)
			exit(1);
		int value = (_buffer & 0b01111111);

		result = result | (value << (7 * numRead));
		numRead++;
		if (numRead > 5) {
			throw "Int to long";
		}
	} while ((_buffer & 0b10000000) != 0);
	return result;
}

boost::asio::ip::tcp::socket	&net::Session::getSocket()
{
	return _socket;
}
