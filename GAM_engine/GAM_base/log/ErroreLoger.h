
#ifndef H_ERRORE_LOGER
#define H_ERRORE_LOGER

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <tchar.h>

using namespace std;

class ErroreLoger
{
private:
	SYSTEMTIME time;
	wofstream logFile;
public:
	ErroreLoger()
	{
		logFile.open(wstring(TEXT("newlog.txt")).c_str(),ios_base::trunc);
	}
	ErroreLoger(wstring filename)
	{
		logFile.open(filename.c_str(),ios_base::trunc);
	}
	~ErroreLoger()
	{
		if(logFile.is_open())
		{
			logFile.flush();
			logFile.close();
		}
	}
	wstring GetTime()
	{
		wchar_t buff[20];
		wstring timeStr = TEXT("[");
		GetSystemTime(&time);
		GetLocalTime(&time);
		_itow( time.wHour, buff, 10 );
		timeStr.append(buff);
		timeStr.append(TEXT(":"));
		_itow( time.wMinute, buff, 10 );
		timeStr.append(buff);
		timeStr.append(TEXT(":"));
		_itow( time.wSecond, buff, 10 );
		timeStr.append(buff);
		timeStr.append(TEXT(":"));
		_itow( time.wMilliseconds, buff, 10 );
		timeStr.append(buff);
		timeStr.append(TEXT("]"));
		return timeStr;
	}
	void OpenFile(wstring filename)
	{
		logFile.open(filename.c_str(),ios_base::trunc);
	}
	void SendToLog(wstring textLog)
	{
		logFile<<GetTime().c_str()<<textLog.c_str()<<endl;
		//logFile<<textLog.c_str()<<endl;
		logFile.flush();
	}
};

#endif