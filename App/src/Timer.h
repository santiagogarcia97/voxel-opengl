#pragma once

#include <Windows.h>

class Timer
{
public:
	Timer()
	{
		QueryPerformanceFrequency(&m_SystemFreq);
		QueryPerformanceCounter(&m_LastUpdate);
		QueryPerformanceCounter(&m_CurrentTime);
	}

	void update()
	{
		m_LastUpdate = m_CurrentTime;
		QueryPerformanceCounter(&m_CurrentTime);
	}
	float get_deltatime() const
	{
		return float(m_CurrentTime.QuadPart - m_LastUpdate.QuadPart) / m_SystemFreq.QuadPart;
	}
	
private:
	// ticks per second
	LARGE_INTEGER m_SystemFreq;
	// ticks
	LARGE_INTEGER m_LastUpdate;	
	LARGE_INTEGER m_CurrentTime;
	
};