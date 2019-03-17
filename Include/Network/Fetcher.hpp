//
// EPITECH PROJECT, 2019
// Epicraft
// File description:
// Fetcher header
//

#pragma once

#include <istream>
#include <ostream>
#include <sstream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/asio/ssl.hpp>

#include "Epicraft.hpp"
#include "Log.hpp"

using boost::asio::ip::tcp;

namespace net {
    class Fetcher {
    public:
        Fetcher(boost::asio::io_service &ioService, boost::asio::ssl::context &context,
                const std::string &path);

        std::stringstream &getHeader();
        std::string getContent();

    private:
        void handleResolve(const boost::system::error_code &err,
                           tcp::resolver::iterator endpoint_iterator);
        bool verifyCertificate(bool preverified, boost::asio::ssl::verify_context &contex);
        void handleConnect(const boost::system::error_code &err);
        void handleHandshake(const boost::system::error_code &err);
        void handleWriteRequest(const boost::system::error_code &err);
        void handleReadStatus(const boost::system::error_code &err);
        void handleReadHeaders(const boost::system::error_code &err);
        void handleReadContent(const boost::system::error_code &err);

    private:
        tcp::resolver _resolver;
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> _socket;
        boost::asio::streambuf _request;
        boost::asio::streambuf _response;
        const std::string _host = "api.mojang.com";
        std::stringstream _header;
        std::stringstream _content;
    };
}
