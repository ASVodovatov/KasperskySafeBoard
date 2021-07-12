#pragma once

#include "../Common.h"

class ResultsProcessor
{
public:
	ResultsProcessor(const std::string& i_resultString): m_results(ParseResultsString(i_resultString))
	{}

	void PrintResultString();

private:
	Results m_results;

	std::string secondsToHHMMSS(const size_t i_durationInSeconds);
	Results ParseResultsString(const std::string& i_string);

};