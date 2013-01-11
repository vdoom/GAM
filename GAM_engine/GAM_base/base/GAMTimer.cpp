//#include "GAMTimer.h"

//template <class T> GAMTimer<T>::GAMTimer(void)
//{
//	m_started = false;
//	m_needDelete = false;
//	m_elapsedTime = 0;
//	m_startTime = 0;
//	m_endTime = 0;
//}
//
//template <class T> GAMTimer<T>::GAMTimer(DWORD t_endTime, T *t_invoker, void (T::*t_action)())
//{
//	StartTimer(t_endTime, t_invoker, t_action);
//}
//
//template <class T> GAMTimer<T>::~GAMTimer(void)
//{
//}
//
//template <class T> /*inline*/ DWORD GAMTimer<T>::ElapsedTime()
//{
//	return (timeGetTime() - m_startTime);
//}
//
//template <class T> void GAMTimer<T>::Update()
//{
//	if(m_started && !m_needDelete)
//	{
//		if(ElapsedTime() >= m_endTime)
//		{
//			//(m_invoker->*m_action)();
//			m_needDelete = true;
//		}
//	}
//}
//
//template <class T> void GAMTimer<T>::StartTimer(DWORD t_endTime, T* t_ivoker, void (T::*t_action)())
//{
//	m_started = true;
//	m_startTime = timeGetTime();
//	m_action = t_action;
//	m_endTime = t_endTime; 
//	m_ivoker = t_invoker;
//}
//
//template <class Invoker> bool GAMTimer<Invoker>::IsStarted()
//{return m_started;}
//template <class Invoker> bool GAMTimer<Invoker>::IsNeedDelete()
//{return m_needDestroy;}