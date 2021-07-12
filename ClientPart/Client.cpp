#include <iostream>
#include <sstream>
#include <boost/asio.hpp>
#include "ResultsProcessor.h"
#include "Client.h"

Client::Client(const boost::asio::ip::tcp::endpoint i_endpoint):
m_endpoint(i_endpoint),
m_socket(m_ioService)
{
	m_socket.connect(m_endpoint);
}

bool Client::Send(const std::string i_message)
{
	boost::system::error_code error;
	boost::asio::write( m_socket, boost::asio::buffer(i_message + "\n"), error );
	return true;
}

std::string Client::Recieve()
{
	boost::system::error_code error;
	boost::asio::streambuf resievedData;
	boost::asio::read(m_socket, resievedData, boost::asio::transfer_all(), error);

	return std::string(boost::asio::buffer_cast<const char*>(resievedData.data()), resievedData.size());
}

