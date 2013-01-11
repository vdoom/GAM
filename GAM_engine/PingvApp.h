#pragma once

#ifndef H_PINGVAPP
#define H_PINGVAPP

#include "GAM_base\app\GAMApp.h"
#include "GAM_base\base\TextObject.h"
#include "GAM_base\base\VertexObject.h"
#include "GAM_base\base\GAMTimer.h"
#include "PingvInputProcessor.h"

class PingvApp : public GAMApp
{
private:
	GAMTimer<PingvApp>* m_timer;
	PingvInputProcessor* m_PingvInputProcessor;
	void MoveCamera()
	{
		this->m_pCamera->MoveUp(5.5);
		//wchar_t *YY=new wchar_t[10];
		//_itow(GetTime().GetDelta(), YY, 10);
		m_pErroreLoger->SendToLog(wstring(_T("Move")));
	}
public:
	PingvApp()
	{	
		//m_timer.StartTimer(6000, this, &PingvApp::MoveCamera); //= new GAMTimer<PingvApp>(6000, this, &PingvApp::MoveCamera);
	}
	virtual ~PingvApp()
	{}

	virtual HRESULT Init3D(HWND t_hWnd)
	{
		HRESULT hr = GAMApp::Init3D(t_hWnd);
		if(FAILED(hr))
		{return hr; }

		TextObject* txtObject = new TextObject(m_pD3DDevice, m_pErroreLoger);
		txtObject->CreateText(_T("Hdkhfkhdfksdhshsiuhfsiuhfgisdhfgshurghsergiuhserghieurhguihe"));
		m_pObjects->push_back(txtObject);

		VertexObject* objectVert = new VertexObject(m_pD3DDevice, m_pErroreLoger);
		objectVert->LoadTexture(TEXT("Res\\Textures\\ground.jpg"));
		objectVert->SetRenderType(VertexObject::RenderType::Plane);
		objectVert->CreatePlane(D3DXVECTOR3(-10, 0, -10), D3DXVECTOR3(10 ,0 ,10), VertexObject::IndexingType::Triangle);
		m_pObjects->push_back(objectVert);

		m_timer = new GAMTimer<PingvApp>(6000, this, &PingvApp::MoveCamera);
	}
	virtual HRESULT InitInput(HINSTANCE t_hinst)
	{
		GAMApp::InitInput(t_hinst);
		m_PingvInputProcessor = new PingvInputProcessor(m_pInput);
		InitInputProcessor(m_PingvInputProcessor);
		// = dynamic_cast<PingvInputProcessor*>(m_pInputProcessor);
		//m_inputProcessor = new PingvInputProcessor(m_pInput);
		//TODO: NEED REFINE!!!
		m_PingvInputProcessor->PressKey_W = &PingvApp::MoveCamera;
		return S_OK;
	}

	virtual void Render()
	{
		GAMApp::Render();
		m_timer->Update();//->Update();
		//m_inputProcessor->UpdateInput();
	}
};

#endif