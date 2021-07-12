#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "Client.h"
#include "ResultsProcessor.h"

int main(int argc, char* argv[]) 
{
	if (argc < 2)
	{
		std::cerr << "Not enough arguments\n";
		return 0;
	}
	if (argc > 2)
	{
		std::cerr << "Too many arguments\n";
		return 0;
	}
	
	Client client({boost::asio::ip::address::from_string("127.0.0.1"), 1237 });
	client.Send(argv[1]);
	
	const std::string stop = "Stop";
	if(stop == argv[1]) return 0;
	
	std::string recievedString = client.Recieve();
	if(recievedString != "NotExist")
	{
		std::cout << "This directory does not exists\n";
		return 0;
	}
	ResultsProcessor results(recievedString);
	results.PrintResultString();
    return 0;
}