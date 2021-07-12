#pragma once

#include <boost/asio.hpp>

class Client
{
public:
	Client(const boost::asio::ip::tcp::endpoint i_endpoint);
	bool Send(const std::string i_message);
	std::string Recieve();

private:
	boost::asio::io_service m_ioService;
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::ip::tcp::endpoint m_endpoint;
};
