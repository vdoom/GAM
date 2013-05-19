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
	static GAMTime* s_instance;
	DWORD m_prevTime;
	DWORD m_delta;
	void UpdateTime();
	GAMTime(void);
	GAMTime(const GAMTime &t_time){}
	void operator = (GAMTime t_console){}
public:
	~GAMTime(void);
	DWORD GetTime();
	DWORD GetDelta();
	static GAMTime* Instantiate()
	{
		if(s_instance == 0)
		{
			s_instance = new GAMTime();
		}
		else
		{
			return s_instance;
		}
	}
	static GAMTime* GetInstance()
	{
		return Instantiate();
	}
};

#endif
