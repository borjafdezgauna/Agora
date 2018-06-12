
#include "Timer.h"


CTimer::CTimer()
{
	m_t0 = std::chrono::system_clock::now();
}

void CTimer::start()
{
	m_t0= std::chrono::system_clock::now();
	m_bRunning = true;
}

void CTimer::stop()
{
	if (m_bRunning)
	{
		m_stopTimePoint = std::chrono::system_clock::now();
		m_bRunning = false;
	}
}

double CTimer::getElapsedTime(bool resetTimer)
{
	std::chrono::system_clock::time_point t1;
	
	if (m_bRunning)
		t1 = std::chrono::system_clock::now();
	else
		t1 = m_stopTimePoint;

	auto timeDiff = t1 - m_t0;

	if (resetTimer) start();

	return (std::chrono::duration<double, std::ratio<1>>(timeDiff)).count();
}
#include <sstream>
#include <iomanip>
string CTimer::getElapsedTimeAsString(bool resetTimer)
{
	double timeInSeconds = getElapsedTime(resetTimer);

	int seconds = (int) floor(timeInSeconds);

	int hours = seconds / 3600;
	int minutes = (seconds - (hours * 3600)) / 60;
	seconds = seconds % 60;

	stringstream result;
	result << std::setw(2) << std::setfill('0') << to_string(hours) << ":" << std::setw(2) << std::setfill('0') << to_string(minutes) << ":" << std::setw(2) << std::setfill('0') << to_string(seconds);
	return result.str();
}