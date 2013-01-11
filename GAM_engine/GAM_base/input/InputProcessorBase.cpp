#include "InputProcessorBase.h"
#include "..\app\GAMApp.h"

InputProcessorBase::InputProcessorBase(GAMInput* t_input)
{
	m_input = t_input;
}

InputProcessorBase::~InputProcessorBase(void)
{
}

void InputProcessorBase::UpdateInput(GAMApp* t_app)
{
	UpdateMouseState(t_app);
	UpdateMouseInput(t_app);
	UpdateKeyBoardInput(t_app);
}