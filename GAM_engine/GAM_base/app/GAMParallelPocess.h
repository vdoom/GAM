#pragma once

#ifndef H_GAMPARALLELPROCESS
#define H_GAMPARALLELPROCESS

#include <omp.h>

class GAMParallelPocess
{
protected:
	virtual void Run() = 0;
public:
	GAMParallelPocess(void);
	virtual ~GAMParallelPocess(void);
	void Start();
};

#endif
