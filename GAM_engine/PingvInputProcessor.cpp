#include "PingvInputProcessor.h"
#include "PingvApp.h"

PingvInputProcessor::PingvInputProcessor(GAMInput* t_input) : InputProcessorBase(t_input)
{
	PressKey_W = 0;	
	//PressKey_A = 0;
	//PressKey_S = 0;
	//PressKey_D = 0;
	//PressKey = 0;
	MouseMove = 0;
	MouseButtonPress = 0; 
	loger = new ErroreLoger(wstring(_T("input_procexxor.txt")));
}

PingvInputProcessor::~PingvInputProcessor(void)
{
}

//TODO: Need refine!!!
void PingvInputProcessor::UpdateKeyBoardInput(GAMApp* t_app)
{
	
	#define KEYDOWN(name, key) (name[key] & 0x80) 
	char *tt_data=0;
	m_input->KBInput(&tt_data);
 
	PingvApp* m_apptt = 0;
	m_apptt = dynamic_cast<PingvApp*>(t_app);
	if(tt_data!=0)
	{loger->SendToLog(_T("Presssdfsdfs"));
		if(KEYDOWN(tt_data, DIK_W))// && PressKey_W != 0 && m_apptt!=0)
		{
			loger->SendToLog(_T("PressW"));
			(m_apptt->*PressKey_W)();
		}
		if(KEYDOWN(tt_data, DIK_A))
		{
			loger->SendToLog(_T("PressA"));
			(m_apptt->*PressKey_A)();
		}
		if(KEYDOWN(tt_data, DIK_S))
		{
			loger->SendToLog(_T("PressS"));
			(m_apptt->*PressKey_S)();
		}
		if(KEYDOWN(tt_data, DIK_D))
		{
			loger->SendToLog(_T("PressD"));
			(m_apptt->*PressKey_D)();
		}
		//else
		//{loger->SendToLog(_T("notPressWWW"));}
	}
	else
	{loger->SendToLog(_T("notPress"));}
	//(m_apptt->*PressKey_W)();
}

void PingvInputProcessor::UpdateMouseInput(GAMApp* t_app)
{}

void PingvInputProcessor::UpdateMouseState(GAMApp* t_app)
{}