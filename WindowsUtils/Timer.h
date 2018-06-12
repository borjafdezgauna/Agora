#pragma once
#include <chrono>
#include <string>
using namespace std;

class CTimer
{
	bool m_bRunning = false;
	std::chrono::system_clock::time_point m_t0;
	std::chrono::system_clock::time_point m_stopTimePoint;
public:
	CTimer();

	void start();
	void stop();
	double getElapsedTime(bool resetTimer = false);
	string getElapsedTimeAsString(bool resetTimer = false);
};