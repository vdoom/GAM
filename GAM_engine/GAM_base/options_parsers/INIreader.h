#include <Windows.h>
#include <tchar.h>
#include <math.h>
#include <intsafe.h>
#include <iostream>

using namespace std;

class INIreader
{
private:
	int tsize;
	wstring* currdir;
protected:
public:
	INIreader()
	{
		currdir = new wstring();
	}
	INIreader(LPWSTR filename)//open file in current dir
	{
		currdir = new wstring();
		openFileC(filename);
	}
	//~INIreader();
	int ReadInt(LPWSTR Attribute, LPWSTR Key, int defaultInt)
	{
		int Tint;
		Tint = GetPrivateProfileInt(Attribute, Key, defaultInt, currdir->c_str());
		return Tint;
	}
	LPTSTR ReadStr(LPWSTR Attribute, LPWSTR Key, LPCTSTR defaultStr)
	{
		LPTSTR ret = new TCHAR[300];
		GetPrivateProfileString(Attribute, Key, defaultStr, ret, 298,currdir->c_str());
		return ret;
	}
	double ReadDoub(LPWSTR Attribute, LPWSTR Key, LPCTSTR defaultStr)
	{
		wchar_t* tmp;
		double res = 0.0;
		res = wcstod(ReadStr(Attribute, Key, defaultStr), &tmp);
		return res;
	}
	void openFileA(LPWSTR filename)//Open file with absolute path
	{
		currdir = new wstring(filename);
	}
	void openFileC(LPWSTR filename)//open file in current dir
	{
		LPWSTR tmp;
		tmp = new wchar_t[1000];
		GetCurrentDirectory(1000, tmp);
		wstring* stmp = new wstring(tmp);
		* currdir += *stmp;
		stmp = new wstring(filename);
		* currdir += *stmp;
		delete[] tmp;
	}
};
