#pragma once

#ifndef H_GAMINPUT
#define H_GAMINPUT

#include <dinput.h>
#include "..\log\ErroreLoger.h"

#define KEYDOWN(name, key) (name[key] & 0x80) 

class GAMInput
{
protected:
	LPDIRECTINPUT8        m_ppDIKB; 
	LPDIRECTINPUTDEVICE8  m_ppDDeviceKB; 
	LPDIRECTINPUT8        m_ppDIMO; 
	LPDIRECTINPUTDEVICE8  m_ppDDeviceMO;
	ErroreLoger* m_pErroreLoger;
	HWND m_hDlg;

	void WINAPI TermKB(); // Release DI Keyboard
	void WINAPI TermMO(); // Release DI Mouse
public:
	GAMInput(void);
	~GAMInput(void);
	//void SetWindowHandle(HWND t_hDlg);
	//HWND GetWindowHandle();
	HRESULT InitInputKB(HINSTANCE t_hinst);
	HRESULT InitInputMO(HINSTANCE t_hinst);
	HRESULT WINAPI KBInput(/*[out]*/char** t_data); 
	HRESULT MOButtonInput(/*[out]*/DIDEVICEOBJECTDATA* t_moData );
	HRESULT MOStateInput(/*[out]*/DIMOUSESTATE* t_moState);
};

#endif
