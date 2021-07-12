#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <algorithm>
#include <functional>
#include <chrono>
#include <boost/asio.hpp>
#include "Kaspersky.h"

void ProcessFolder::Go()
{
	for (const auto& file : std::filesystem::directory_iterator(m_directory))
	{
		processFile(file.path().string());
	}

	m_threadPool.join();
}   

void ProcessFolder::processFile(const std::string& i_file)
{
	boost::asio::post(m_threadPool, 
		[this, i_file]()
		{
			processFileThread(i_file);
		}
	);
}

void ProcessFolder::processFileThread(const std::string& i_file)
{
	std::ifstream input(i_file);
	std::string fileLine;
	if(!input.is_open())
	{
		m_syncResults.Add(Status::ERROR);
		return;
	}

	while (std::getline(input, fileLine))
	{
		if (Status status = containSuspiciousString(fileLine); status != Status::NOT_FOUND)
		{
			if (status == Status::JS_FOUND && std::string(i_file.end() - 3, i_file.end()) != ".js") continue;
			m_syncResults.Add(status);
			return;
		}
	}
}

Status ProcessFolder::containSuspiciousString(const std::string& i_line) const
{
	static const std::string jsSuspicious = "<script>evil_script()</script>";
	static const std::string unixSuspicious = "rm - rf ~/ Documents";
	static const std::string macSuspicious = "system(\"launchctl load / Library / LaunchAgents / com.malware.agent\")";
	
	//This lines to know if suspicious line is equal to to 
	//if(i_line == jsSuspicious)        return Status::JS_FOUND;
	//else if(i_line == unixSuspicious) return Status::UNIX_FOUND;
	//else if(i_line == macSuspicious)  return Status::MAC_FOUND;

	//This lines to know if suspicious line is substring of line
	if (i_line.end() != std::search(i_line.begin(), i_line.end(),
		std::boyer_moore_searcher(unixSuspicious.begin(), unixSuspicious.end())))
	{
		return Status::UNIX_FOUND;
	}
	else if (i_line.end() != std::search(i_line.begin(), i_line.end(),
		std::boyer_moore_searcher(macSuspicious.begin(), macSuspicious.end())))
	{
		return Status::MAC_FOUND;
	}
	else if (i_line.end() != std::search(i_line.begin(), i_line.end(),
		std::boyer_moore_searcher(jsSuspicious.begin(), jsSuspicious.end())))
	{
		return Status::JS_FOUND;
	}

	return Status::NOT_FOUND;
}

Results ProcessFolder::GetResults()
{
	return
	{
		std::distance(std::filesystem::directory_iterator{ m_directory }, std::filesystem::directory_iterator{}),
		m_syncResults.GetJs(), 
		m_syncResults.GetMac(), 
		m_syncResults.GetUnix(), 
		m_syncResults.GetErrors(),
		std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - m_startTime).count()
	};
}