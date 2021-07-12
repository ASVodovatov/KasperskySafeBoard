#include <iostream>
#include <boost/asio.hpp>

#include "Server.h"
#include "Kaspersky.h"

Server::Server(const boost::asio::ip::tcp::endpoint i_endpoint) :
m_endpoint(i_endpoint),
m_socket(m_ioService),
m_acceptor(m_ioService, m_endpoint)
{}

std::string Server::Recieve()
{
	boost::asio::streambuf recievedData;
	boost::asio::read_until(m_socket, recievedData, "\n");
	return std::string(boost::asio::buffer_cast<const char*>(recievedData.data()), recievedData.size());
}

void Server::Send(const std::string i_message)
{
	boost::asio::write(m_socket, boost::asio::buffer(i_message + "\n"));
}

void Server::Accept()
{
	m_acceptor.accept(m_socket);	
}

void Server::Close()
{
	m_socket.close();
}

