#pragma once

#ifndef H_GAMTIMER
#define H_GAMTIMER

#include <Windows.h.>
//TODO: NEED REFINE!!! NEED ADD CYCLIC PARAMETR;
template <class T> class GAMTimer
{
private: 
	T* m_invoker;
	DWORD m_startTime;
	DWORD m_endTime;
	bool m_started;
	bool m_needDestroy;
	void (T::*m_action)();
public:

	GAMTimer(void)
	{
		m_started = false;
		m_needDestroy = false;
		m_startTime = 0;
		m_endTime = 0;
	}
	
	GAMTimer(DWORD t_endTime, T *t_invoker, void (T::*t_action)())
	{
		StartTimer(t_endTime, t_invoker, t_action);
	}

	~GAMTimer(void)
	{
	}

	inline DWORD ElapsedTime()
	{
		return (timeGetTime() - m_startTime);
	}

	void Update()
	{
		if(m_started && !m_needDestroy)
		{
			if(ElapsedTime() >= m_endTime)
			{
				(m_invoker->*m_action)();
				m_needDestroy = true;
			}
		}
	}

	void StartTimer(DWORD t_endTime, T* t_invoker, void (T::*t_action)())
	{
		m_started = true;
		m_needDestroy = false;
		m_startTime = timeGetTime();
		m_action = t_action;
		m_endTime = t_endTime; 
		m_invoker = t_invoker;
	}

	bool IsStarted()
	{return m_started;}
	bool IsNeedDelete()
	{return m_needDestroy;}
};

#endif
