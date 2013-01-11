/*-------------------------------------
		Statick Singleton !!!
		Use Only In GAMApp!!!
-------------------------------------*/
#pragma once

#ifndef H_GAMTIME
#define H_GAMTIME

#include <Windows.h.>

class GAMApp;

class GAMTime
{
	friend class GAMApp;
private:
	DWORD m_prevTime;
	DWORD m_delta;
	void UpdateTime();
public:
	GAMTime(void);
	~GAMTime(void);
	DWORD GetTime();
	DWORD GetDelta();
};

#endif
