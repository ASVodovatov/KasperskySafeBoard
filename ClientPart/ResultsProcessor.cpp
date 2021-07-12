#include <iostream>
#include <sstream>
#include "ResultsProcessor.h"

std::string ResultsProcessor::secondsToHHMMSS(const size_t i_durationInSeconds)
{
	size_t hours = 0;
	size_t minutes = 0;
	size_t seconds = 0;
	hours = i_durationInSeconds / 3600;
	minutes = (i_durationInSeconds - 3600 * hours) / 60;
	seconds = i_durationInSeconds % 60;    
	return 
		(hours   < 10 ? "0" + std::to_string(hours)   : std::to_string(hours))   + ":" +
		(minutes < 10 ? "0" + std::to_string(minutes) : std::to_string(minutes)) + ":" +
		(seconds < 10 ? "0" + std::to_string(seconds) : std::to_string(seconds));
}

void ResultsProcessor::PrintResultString()
{
	std::cout << "====== Scan result ======\n";
	std::cout << "Processed files : " << m_results.numberOfFiles                      << '\n';
	std::cout << "JS detects : "      << m_results.jsResult                           << '\n';
	std::cout << "Unix detects : "    << m_results.unixResult                         << '\n';
	std::cout << "macOS detects : "   << m_results.macResult                          << '\n';
	std::cout << "Errors : "          << m_results.errors                             << '\n';
	std::cout << "Execution time : "  << secondsToHHMMSS(m_results.durationInSeconds) << '\n';
	std::cout << "=========================\n";
}

Results ResultsProcessor::ParseResultsString(const std::string& i_string)
{
	std::stringstream ss(i_string);
	Results results;
	ss >> results.numberOfFiles;
	ss >> results.jsResult;
	ss >> results.unixResult;
	ss >> results.macResult;
	ss >> results.errors;
	ss >> results.durationInSeconds;
	return results;
}