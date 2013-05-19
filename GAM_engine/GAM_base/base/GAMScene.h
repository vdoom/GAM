#pragma once

#ifndef	H_GAMSCENE
#define	H_GAMSCENE

#include "GAMVisElement.h"

class GAMScene : public GAMVisElement
{
public:
	GAMScene(void);
	virtual ~GAMScene(void);
	virtual void Draw() = 0;
	void LoadScene();
	void DeleteScene();
	void CreateScene();
	void ClearingScene();
};

#endif