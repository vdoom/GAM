#pragma once

#ifndef H_TEXTO_BJECT
#define H_TEXTO_BJECT

#include "MeshObject.h"

class TextObject : public MeshObject
{
private:
	MeshObject::LoadObject;
	MeshObject::LoadMesh;
protected:
	HFONT hFont;   // Дескриптор нового шрифта   ???????????????????????  
	HFONT hFontOld;    // Дескриптор старого шрифта   ???????????????????????
    HDC hdc;   //???????????????????????

public:
	TextObject():MeshObject()
	{}
	TextObject(LPDIRECT3DDEVICE9 TDDevice, ErroreLoger* Tloger=0):MeshObject(TDDevice, Tloger)
	{}
	TextObject(GAMObject* Tparent):MeshObject(Tparent)
	{}
	TextObject(LPDIRECT3DDEVICE9 TDDevice, GAMObject* Tparent, ErroreLoger* Tloger=0):MeshObject(TDDevice, Tparent, Tloger)
	{}
	TextObject(LPDIRECT3DDEVICE9 TDDevice, LPD3DXMESH Tmesh, LPDIRECT3DTEXTURE9 *Ttexture1, D3DMATERIAL9 Tmaterial, DWORD TcountMaterials, ErroreLoger* Tloger = 0):MeshObject(TDDevice, Tloger)
	{
		Init(Tmesh, Ttexture1, Tmaterial,TcountMaterials, Tloger);
	}
	TextObject(LPDIRECT3DDEVICE9 TDDevice, GAMObject* Tparent, LPD3DXMESH Tmesh, LPDIRECT3DTEXTURE9* Ttexture1, D3DMATERIAL9 Tmaterial, DWORD TcountMaterials, ErroreLoger* Tloger = 0):MeshObject(TDDevice, Tparent, Tloger)
	{
		Init(Tmesh, Ttexture1, Tmaterial,TcountMaterials, Tloger);
	}
	virtual ~TextObject()
	{}

	HRESULT CreateText(wstring t_text, float t_deviation = 0.001f, float t_extrusion = 0.4f, wstring t_font = TEXT("Times New Roman"));

	virtual wstring GetTypeStr();
	virtual GAMObject* Clone();
	//virtual void Draw();
};

#endif
