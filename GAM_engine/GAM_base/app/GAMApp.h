#pragma once

#ifndef H_GAMAPP
#define H_GAMAPP

#include <d3d9.h>
#include <d3dx9.h>
#include <D3dx9math.h>
#include <Vector>
#include "GAMTime.h"
#include "..\input\GAMInput.h"
#include "..\input\InputProcessorBase.h"
#include "..\camera\Camera.h"
#include "..\log\ErroreLoger.h"
#include "..\base\GAMVisElement.h"
//#include "gClasses\Camera.h"

class GAMApp
{
protected: 
	//--------COMMON--------
	ErroreLoger* m_pErroreLoger;
	vector<GAMObject*>* m_pObjects;
	GAMTime m_time;
	//----------------------
	//---------INPUT--------------
	GAMInput* m_pInput;
	InputProcessorBase* m_pInputProcessor;
	//----------------------------
	//--------RENDER--------------
	LPDIRECT3D9			m_pD3D;
	LPDIRECT3DDEVICE9	m_pD3DDevice;
	CXCamera*           m_pCamera;
	D3DXMATRIXA16		m_matProj;
	D3DPRESENT_PARAMETERS m_d3dpp; 
	void DefaulInitPresentParameters();
	//-----------------------------
public:
	GAMApp(void);
	virtual ~GAMApp(void);
	GAMTime GetTime();
	//----RENDER------
	LPDIRECT3D9 GetDirect3D9();
	LPDIRECT3DDEVICE9 GetDirect3DDevice9();
	D3DXMATRIXA16 GetProjectionMatrix();
	D3DPRESENT_PARAMETERS GetD3DPresentParameters();
	CXCamera* GetCamera();
	virtual HRESULT Init3D(HWND t_hWnd);
	virtual void Cleanup();
	virtual void Render();
	//------------------
	//-----INPUT--------
	virtual HRESULT InitInput(HINSTANCE t_hinst);
	HRESULT InitInputProcessor(InputProcessorBase* t_pinputProcessor);
	//------------------
};
#endif 
