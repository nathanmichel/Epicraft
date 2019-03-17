//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Fetcher sources
//

#include "Fetcher.hpp"

net::Fetcher::Fetcher(boost::asio::io_service &ioService, boost::asio::ssl::context &context,
                      const std::string &path) : _resolver(ioService), _socket(ioService, context) {
    std::ostream requestStream(&_request);
    requestStream << "GET " << path << " HTTP/1.0\r\n";
    requestStream << "Host: " << _host << "\r\n";
    requestStream << "Accept: */*\r\n";
    requestStream << "Connection: close\r\n\r\n";


    misc::toLog("Request", "GET on " + _host + path);

    tcp::resolver::query query(_host, "https");
    _resolver.async_resolve(query, boost::bind(&Fetcher::handleResolve, this,
                                               boost::asio::placeholders::error,
                                               boost::asio::placeholders::iterator));
}

void net::Fetcher::handleResolve(const boost::system::error_code &err, tcp::resolver::iterator endpoint_iterator) {
    if (!err) {
        _socket.set_verify_mode(boost::asio::ssl::verify_peer);
        _socket.set_verify_callback(boost::bind(&Fetcher::verifyCertificate, this, _1, _2));

        boost::asio::async_connect(_socket.lowest_layer(), endpoint_iterator,
                                   boost::bind(&Fetcher::handleConnect, this,
                                               boost::asio::placeholders::error));
    } else
        std::cout << "Error resolve: " << err.message() << "\n";
}

bool net::Fetcher::verifyCertificate(bool preverified, boost::asio::ssl::verify_context &contex) {
    // https://github.com/alexandruc/SimpleHttpsClient/blob/master/https_client.cpp
    return true;
}

void net::Fetcher::handleConnect(const boost::system::error_code &err) {
    if (!err) {
        _socket.async_handshake(boost::asio::ssl::stream_base::client,
                                boost::bind(&Fetcher::handleHandshake, this,
                                            boost::asio::placeholders::error));
    } else
        std::cout << "Connect failed: " << err.message() << "\n";
}

void net::Fetcher::handleHandshake(const boost::system::error_code &err) {
    if (!err) {
        boost::asio::async_write(_socket, _request,
                                 boost::bind(&Fetcher::handleWriteRequest, this,
                                             boost::asio::placeholders::error));
    } else
        std::cout << "Handshake failed: " << err.message() << "\n";
}

void net::Fetcher::handleWriteRequest(const boost::system::error_code &err) {
    if (!err) {
        boost::asio::async_read_until(_socket, _response, "\r\n",
                                      boost::bind(&Fetcher::handleReadStatus, this,
                                                  boost::asio::placeholders::error));
    } else
        std::cout << "Error write req: " << err.message() << "\n";
}

void net::Fetcher::handleReadStatus(const boost::system::error_code &err) {
    if (!err) {
        std::istream responseStream(&_response);
        std::string httpVersion;
        responseStream >> httpVersion;
        unsigned int statusCode;
        responseStream >> statusCode;
        std::string statusMessage;
        std::getline(responseStream, statusMessage);
        if (!responseStream || httpVersion.substr(0, 5) != "HTTP/") {
            std::cout << "Invalid response\n";
            return;
        }
        if (statusCode != 200) {
            std::cout << "Response returned with status code ";
            std::cout << statusCode << "\n";
            return;
        }

        boost::asio::async_read_until(_socket, _response, "\r\n\r\n",
                                      boost::bind(&Fetcher::handleReadHeaders, this,
                                                  boost::asio::placeholders::error));
    } else
        std::cout << "Error: " << err.message() << "\n";
}

void net::Fetcher::handleReadHeaders(const boost::system::error_code &err) {
    if (!err) {
        std::istream responseStream(&_response);
        std::string header;
        while (std::getline(responseStream, header) && header != "\r")
            _header << header << "\n";
        _header << "\n";

        if (_response.size() > 0)
            _content << &_response;

        boost::asio::async_read(_socket, _response,
                                boost::asio::transfer_at_least(1),
                                boost::bind(&Fetcher::handleReadContent, this,
                                            boost::asio::placeholders::error));
    } else
        std::cout << "Error: " << err << "\n";
}

void net::Fetcher::handleReadContent(const boost::system::error_code &err) {
    if (!err) {
        _content << &_response;

        boost::asio::async_read(_socket, _response,
                                boost::asio::transfer_at_least(1),
                                boost::bind(&Fetcher::handleReadContent, this,
                                            boost::asio::placeholders::error));
    } else if (err != boost::asio::error::eof)
        std::cout << "Error: " << err << "\n";
}

std::stringstream &net::Fetcher::getHeader() {
    return _header;
}

std::string net::Fetcher::getContent() {
    return _content.str();
}
