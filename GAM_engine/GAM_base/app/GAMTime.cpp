#include "GAMTime.h"

GAMTime::GAMTime(void)
{
	m_prevTime = GetTime();
	m_delta = 0;
}

GAMTime::~GAMTime(void)
{
}

void GAMTime::UpdateTime()
{
	DWORD newTime = GetTime();
	m_delta = newTime - m_prevTime;
	m_prevTime = newTime;
}

DWORD GAMTime::GetTime()
{
	return timeGetTime();
}

DWORD GAMTime::GetDelta()
{
	return m_delta;
}
