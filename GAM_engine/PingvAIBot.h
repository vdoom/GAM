#pragma once

#ifndef H_PINGVAIBOT
#define H_PINGVAIBOT

#include "PingvBot.h"
#include "PingvAISquareMap.h"
//#include "GAM_base\base\GAMParallelPocess.h"

class PingvAIBot : protected PingvBot
{
private:
	PingvMap m_map;//Use Only personal map. It's Need for multy threading work
public:
	PingvAIBot(void);
	virtual ~PingvAIBot(void);
	virtual void Draw();
	virtual GAMObject* Clone();
};

#endif H_PINGVAIBOT