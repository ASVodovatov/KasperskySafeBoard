#pragma once

#include <mutex>
#include <chrono>
#include <boost/asio.hpp>

#include "../Common.h"

namespace
{
	enum class Status
	{
    	JS_FOUND,
    	UNIX_FOUND,
    	MAC_FOUND,
		NOT_FOUND,
		ERROR
	};

	//Synchronized access to total results of analyzer
	class SynchronizedResults {
	public:
		SynchronizedResults(){}

		void Add(const Status i_status) 
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			switch (i_status)
			{
			case Status::JS_FOUND:
				++m_jsFound;
				break;
			case Status::MAC_FOUND:
				++m_macFound;
				break;
			case Status::UNIX_FOUND:
				++m_unixFound;
				break;
			case Status::ERROR:
				++m_errors;
				break;
			default:
				break;
			}
		}

		size_t GetJs()     const { return m_jsFound; }
		size_t GetUnix()   const { return m_unixFound; }
		size_t GetMac()    const { return m_macFound; }
		size_t GetErrors() const { return m_errors; }
	private:
		std::mutex m_mutex;
		size_t m_jsFound = 0;
		size_t m_unixFound = 0;
		size_t m_macFound = 0;
		size_t m_errors = 0;
	};
	}
class ProcessFolder
{
public:
    ProcessFolder(std::string i_directory) :
        m_directory(i_directory), 
		m_startTime(std::chrono::steady_clock::now()),
		m_threadPool(std::thread::hardware_concurrency() > 0 ? std::thread::hardware_concurrency() : 2)
    {}

	//Run analyzing and ger results
    void Go();

	Results GetResults();	

private:
    std::string m_directory;
    std::chrono::steady_clock::time_point m_startTime;
    SynchronizedResults m_syncResults;
	boost::asio::thread_pool m_threadPool;

	//There are two versions of checkings: Equality of full strings and Containing suspicious string in file's substr
    Status containSuspiciousString(const std::string& i_line) const;

	//Process file and write status of file in results 
    void processFileThread(const std::string& i_file);
    
	//Add new processing file thread to pool 
	void processFile(const std::string& i_file);
};

