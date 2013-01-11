#pragma once

#ifndef H_INPUTPROCESSORBASE
#define H_INPUTPROCESSORBASE

#include "GAMInput.h"

class GAMApp;
class InputProcessorBase
{
protected:
	ErroreLoger* loger;
	GAMInput* m_input;
public:
	InputProcessorBase(GAMInput* t_input);
	virtual ~InputProcessorBase(void);
	virtual void UpdateMouseState(GAMApp* t_app) = 0;
	virtual void UpdateMouseInput(GAMApp* t_app) = 0;
	virtual void UpdateKeyBoardInput(GAMApp* t_app) = 0;
	void UpdateInput(GAMApp* t_app);
};
#endif
