#pragma once

#ifndef H_PINGVBOT
#define H_PINGVBOT

#include "GAM_base\base\GAMObject.h"
#include "GAM_base\base\MeshObject.h"

class PingvBot : public GAMVisElement
{
protected: 
	MeshObject* m_mesh;
public:
	PingvBot(void);
	PingvBot(LPDIRECT3DDEVICE9 t_DDevice, ErroreLoger* t_loger=0) : GAMVisElement(t_DDevice, t_loger)
	{
		
		//ErroreLoger* tloger = new ErroreLoger(_T("FuckMe.TXT"));
		//m_mesh = new MeshObject(t_DDevice, this, t_loger);
		m_mesh = new MeshObject(t_DDevice, this, t_loger);
		m_mesh->LoadObject(_T("Res\\Meshes\\penguin.x"), _T("Res\\Textures\\penguin.bmp"));
		m_mesh->SetPosition(D3DXVECTOR3(0, 0, 0));
		m_mesh->SetScale(D3DXVECTOR3(0.3, 0.3, 0.3));
	}
	virtual ~PingvBot(void);
	virtual void Draw();
	virtual GAMObject* Clone();
	virtual void SetPosition(D3DXVECTOR3 t_pos)
	{
		GAMVisElement::SetPosition(t_pos);
		m_mesh->RecalcMatrixGlobalOnly();
	}
	//Todo: need remake this method (not be pure virtual)
	virtual std::wstring GetTypeStr()
	{return wstring(_T("PingvAISquareMap"));}
	//virtual GAMObject* Clone() //Dosn't work!!!((
	//{return this;}
};

#endif H_PINGVBOT
