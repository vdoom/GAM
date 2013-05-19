#pragma once

#ifndef H_GAMCONSOLE
#define H_GAMCONSOLE

class GAMConsole //SingleTon
{
private:
	static GAMConsole* s_instance;
	GAMConsole(void);
	GAMConsole(const GAMConsole &t_consloe){}
	void operator = (GAMConsole t_console);
public:
	virtual ~GAMConsole(void);
	static GAMConsole* Instantiate()
	{
		if(s_instance == 0)
		{
			s_instance = new GAMConsole();
		}
		else
		{
			return s_instance;
		}
	}
	static GAMConsole* GetInstance()
	{
		return Instantiate();
	}
};

#endif
