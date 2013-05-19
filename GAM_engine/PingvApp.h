#pragma once

#ifndef H_PINGVAPP
#define H_PINGVAPP

#include "GAM_base\app\GAMApp.h"
#include "GAM_base\base\TextObject.h"
#include "GAM_base\base\VertexObject.h"
#include "GAM_base\base\GAMTimer.h"
#include "PingvInputProcessor.h"
#include "PingvAISquareMap.h"
#include "PingvBot.h"

class PingvApp : public GAMApp
{
private:
	GAMTimer<PingvApp>* m_timer;
	//Todo: Need refine!!! Input Processor must have Acces to camera moving
	PingvInputProcessor* m_PingvInputProcessor;
	//Todo: Need refine
	void MoveCamera()
	{
		this->m_pCamera->MoveUp(0.1);
		//wchar_t *YY=new wchar_t[10];
		//_itow(GetTime().GetDelta(), YY, 10);
		m_pErroreLoger->SendToLog(wstring(_T("Move")));
	}
	void MoveCameraLeft()
	{
		this->m_pCamera->MoveRight(-0.1);
	}
	void MoveCameraRight()
	{
		this->m_pCamera->MoveRight(0.1);
	}
	void MoveCameraDown()
	{
		this->m_pCamera->MoveUp(-0.1);
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

		
		//TextObject* txtObject = new TextObject(m_pD3DDevice, m_pErroreLoger);
		//txtObject->CreateText(_T("Hdkhfkhdfksdhshsiuhfsiuhfgisdhfgshurghsergiuhserghieurhguihe"));
		//m_pObjects->push_back(txtObject);

		VertexObject* objectVert = new VertexObject(m_pD3DDevice, m_pErroreLoger);
		objectVert->LoadTexture(TEXT("Res\\Textures\\ground.jpg"));
		objectVert->SetRenderType(VertexObject::RenderType::Plane);
		objectVert->CreatePlane(D3DXVECTOR3(-10, 0, -10), D3DXVECTOR3(10 ,0 ,10), VertexObject::IndexingType::Triangle);
		m_pObjects->push_back(objectVert);

		PingvAISquareMap* map = new PingvAISquareMap(m_pD3DDevice, 2, 2, 18, 18, D3DXVECTOR3(-9.5, 0.2, -9.5));
		m_pObjects->push_back(map);

		//MeshObject* m_mesh;
		//m_mesh = new MeshObject(m_pD3DDevice, m_pErroreLoger);
		//todo: need fix this
		//m_mesh->LoadObject(_T("Res\\Meshes\\penguin.x"), _T("Res\\Textures\\penguin.bmp"));
		//m_mesh->SetPosition(D3DXVECTOR3(3,0,3));//(D3DXVECTOR3(1, 1, 1));
		//m_mesh->SetScale(D3DXVECTOR3(0.2, 0.2, 0.2));
		PingvBot* bot = new PingvBot(m_pD3DDevice, m_pErroreLoger);
		bot->SetPosition(D3DXVECTOR3(2,0,10));
		m_pObjects->push_back(bot); //Todo: need individual method for additing objects
		/*m_timer = new GAMTimer<PingvApp>(1000, this, &PingvApp::MoveCamera, false);
		m_pObjects->push_back(m_timer);*/
	}
	//Todo: Need remake
	virtual HRESULT InitInput(HINSTANCE t_hinst)
	{
		GAMApp::InitInput(t_hinst);
		m_PingvInputProcessor = new PingvInputProcessor(m_pInput);
		InitInputProcessor(m_PingvInputProcessor);
		// = dynamic_cast<PingvInputProcessor*>(m_pInputProcessor);
		//m_inputProcessor = new PingvInputProcessor(m_pInput);
		//TODO: NEED REMAKE!!!
		m_PingvInputProcessor->PressKey_W = &PingvApp::MoveCamera;
		m_PingvInputProcessor->PressKey_A = &PingvApp::MoveCameraLeft;
		m_PingvInputProcessor->PressKey_S = &PingvApp::MoveCameraDown;
		m_PingvInputProcessor->PressKey_D = &PingvApp::MoveCameraRight;
		return S_OK;
	}

	virtual void Render()
	{
		GAMApp::Render();
		//m_timer->Update();//->Update();
		//m_inputProcessor->UpdateInput();
	}
};

#endif