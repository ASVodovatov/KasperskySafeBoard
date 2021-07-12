#pragma once

#include <iostream>
#include <boost/asio.hpp>


class Server
{
public:
	Server(const boost::asio::ip::tcp::endpoint i_endpoint);
	std::string Recieve();
	void Send(const std::string i_message);
	void Accept();
	void Close();
private:
	boost::asio::io_service m_ioService;
	boost::asio::ip::tcp::endpoint m_endpoint;
	boost::asio::ip::tcp::socket m_socket;
	boost::asio::ip::tcp::acceptor m_acceptor;
};

 
 