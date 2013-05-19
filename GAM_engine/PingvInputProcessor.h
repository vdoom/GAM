#pragma once

#ifndef H_PINGVINPUTPROCESSOR
#define H_PINGVINPUTPROCESSOR

#include "GAM_base\input\InputProcessorBase.h"
#include "GAM_base\app\GAMApp.h"
class PingvApp;
class PingvInputProcessor : public InputProcessorBase
{
public:
	//-------------KEY-ACTIONS--------------
	void (PingvApp::*PressKey_W)();
	void (PingvApp::*PressKey_A)();
	void (PingvApp::*PressKey_S)();
	void (PingvApp::*PressKey_D)();
	//void (*PressKey)(char* t_key);
	//void SetupMet(void (*Press)()){(*Press)();}
	//------------MOUSE-ACTIONS-------------
	void (*MouseMove)(long int t_x, long int t_y, long int t_z);
	void (*MouseButtonPress)(int t_button);
	//--------------------------------------
	PingvInputProcessor(GAMInput* t_input);
	virtual ~PingvInputProcessor(void);

	virtual void UpdateMouseState(GAMApp* t_app);
	virtual void UpdateMouseInput(GAMApp* t_app);
	virtual void UpdateKeyBoardInput(GAMApp* t_app);
};

#endif
