#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <filesystem>
#include "Server.h"
#include "Kaspersky.h"

int main() {
	Server server(boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1237 ));
	std::cout << "== Scan service is started =\n";
	
	while(true)
	{
		server.Accept();	
		std::string resievedData = server.Recieve();
		resievedData.pop_back();
		
		if(resievedData == "Stop") 
		{
			server.Close();
			return 0;
		}
		if(!std::filesystem::exists(resievedData))
		{
			server.Send("NotExist");
			server.Close();
			continue;
		}
		ProcessFolder process(resievedData);
		process.Go();
		auto [numberOfFiles, jsTotal, unixTotal, macTotal, errorsTotal, durationInSeconds] = process.GetResults();
		std::string total = 
			std::to_string(numberOfFiles) + " " +
			std::to_string(jsTotal)       + " " +
			std::to_string(unixTotal)     + " " +
			std::to_string(macTotal)      + " " +
			std::to_string(errorsTotal)   + " " +
			std::to_string(durationInSeconds);  

		server.Send(total);
		server.Close();
	}
   	return 0;
}