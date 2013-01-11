#pragma once

#ifndef H_INPUTPROCESSOR
#define H_INPUTPROCESSOR

#include "GAMInput.h"
class InputProcessor
{
private:
	GAMInput* m_input;
public:
	InputProcessor(GAMInput* t_input);
	~InputProcessor(void);
};
#endif
