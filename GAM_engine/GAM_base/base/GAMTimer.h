#pragma once

#ifndef H_GAMTIMER
#define H_GAMTIMER

#include <Windows.h.>
#include "GAMObject.h"
//TODO: NEED REFINE!!! NEED ADD CYCLIC PARAMETR;
template <class T> class GAMTimer : public GAMObject
{
private: 
	T* m_invoker;
	DWORD m_startTime;
	DWORD m_endTime;
	bool m_started;
	bool m_needDestroy;
	bool m_cyclic;
	void (T::*m_action)();
public:

	GAMTimer(void)
	{
		m_started = false;
		m_needDestroy = false;
		m_startTime = 0;
		m_endTime = 0;
	}
	
	GAMTimer(DWORD t_endTime, T *t_invoker, void (T::*t_action)(), bool t_cyclic = false)
	{
		StartTimer(t_endTime, t_invoker, t_action, t_cyclic);
	}

	virtual ~GAMTimer(void)
	{
	}

	virtual std::wstring GetTypeStr()
	{return wstring(_T("GAMTimer"));}

	inline DWORD ElapsedTime()
	{
		return (timeGetTime() - m_startTime);
	}

	virtual void Draw()
	{
		Update();
	}

	//Todo: need refine!!!
	virtual GAMObject* Clone()
	{
		return new GAMTimer<T>(m_endTime, m_invoker, m_action, m_cyclic);
		//return new GAMTimer(*this);
	}

	void Update()
	{
		if(m_started && !m_needDestroy)
		{
			if(ElapsedTime() >= m_endTime)
			{
				(m_invoker->*m_action)();
				if(!m_cyclic)
				{
					m_needDestroy = true;
				}
				else
				{
					m_startTime = timeGetTime();
				}
			}
		}
	}

	void StartTimer(DWORD t_endTime, T* t_invoker, void (T::*t_action)(), bool t_cyclic = false)
	{
		m_started = true;
		m_needDestroy = false;
		m_startTime = timeGetTime();
		m_action = t_action;
		m_endTime = t_endTime; 
		m_invoker = t_invoker;
		m_cyclic = t_cyclic;
	}

	bool IsStarted()
	{return m_started;}
	bool IsNeedDelete()
	{return m_needDestroy;}
	void KillNextTime()
	{
		m_cyclic = false;
		m_needDestroy = true;
	}
};

#endif
