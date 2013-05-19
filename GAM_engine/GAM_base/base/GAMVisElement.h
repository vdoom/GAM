#pragma once

#ifndef H_GAMVisElement
#define H_GAMVisElement

#include "GAMObject.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <D3dx9math.h>
#include <Vector>

#define D3DFVF_MESHVERTEX   (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

struct GAMVERTEX
{
    D3DXVECTOR3 p;
    D3DXVECTOR3 n;
    FLOAT       tu, tv;

	GAMVERTEX & operator = (const GAMVERTEX & other )
	{
		if (this != &other) 
        {
			p = other.p;
			n = other.n;
			tu = other.tu;
			tv = other.tv;
        }
        return *this;
	}
	//Need to finish other basic operators
};

class GAMVisElement : public GAMObject
{
protected:
	D3DXVECTOR3 vectorPosition;
	D3DXVECTOR3 vectorRotation;
	D3DXVECTOR3 vectorScale;
	D3DXVECTOR2 mipMap;
	LPDIRECT3DDEVICE9 DDevice;
	bool visible;
	D3DXMATRIX matrixLocalTransform;
	D3DXMATRIX matrixGlobalTransform;
	//GAMVisElement* parent;

	void StartUpInit()
	{
		//GAMObject::StartUpInit();
		D3DXMatrixIdentity(&matrixLocalTransform);
		D3DXMatrixIdentity(&matrixGlobalTransform);
		vectorScale = D3DXVECTOR3(1, 1, 1);
		visible = true;
		//parent = 0;
	}

public:

	//---------NEED-REFINE----------
	//GAMVisElement(void);
	GAMVisElement() : GAMObject()
	{
		StartUpInit();
	}
	GAMVisElement(LPDIRECT3DDEVICE9 TDDevice, ErroreLoger* Tloger=0) : GAMObject( Tloger)
	{
		StartUpInit();
		DDevice = TDDevice;
	}
	GAMVisElement(GAMObject* Tparent) : GAMObject(Tparent)
	{
		StartUpInit();
	}
	GAMVisElement(LPDIRECT3DDEVICE9 TDDevice, GAMObject* Tparent, ErroreLoger* Tloger=0) : GAMObject( Tparent, Tloger)
	{
		StartUpInit();
		DDevice = TDDevice;
	}

	virtual void Draw() = 0;
	virtual ~GAMVisElement(void)
	{}
	//------------------------------

	virtual D3DXVECTOR3 GetPosition()
	{ return vectorPosition; }
	virtual D3DXVECTOR3 GetRotation()
	{ return vectorRotation; }
	virtual D3DXVECTOR3 GetScale()
	{ return vectorScale; }

	virtual void SetPosition(D3DXVECTOR3 pos)
	{ 
		vectorPosition = pos;	
		D3DXMATRIX MatTemp;
		D3DXMatrixIdentity(&MatTemp);
		D3DXMatrixTranslation(&MatTemp, vectorPosition.x, vectorPosition.y, vectorPosition.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		RecalcMatrixGlobalOnly();
		//RecalcMatrixGlobal();
	}
	virtual void SetRotation(D3DXVECTOR3 angles)
	{ 
		vectorRotation = angles; 
		D3DXMATRIX MatTemp;
		D3DXMatrixIdentity(&MatTemp);
		D3DXMatrixRotationX(&MatTemp, vectorRotation.x);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixRotationY(&MatTemp, vectorRotation.y);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixRotationZ(&MatTemp, vectorRotation.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		//D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		RecalcMatrixGlobalOnly();
	}
	virtual void SetScale(D3DXVECTOR3 scale)
	{ 
		vectorScale = scale; 
		D3DXMATRIX MatTemp;
		D3DXMatrixIdentity(&MatTemp);
		D3DXMatrixScaling(&MatTemp, vectorScale.x, vectorScale.y, vectorScale.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		RecalcMatrixGlobalOnly();
		//RecalcMatrixGlobal();
	}


	bool IsVisible()
	{ return visible; }

	void SetVisible(bool Tvisible)
	{ visible = Tvisible; }

	void Show()
	{ visible = true; }

	void Hide()
	{ visible = false; }

	void SetDevice(LPDIRECT3DDEVICE9 TDDevice)
	{
		DDevice = TDDevice;
	}

	LPDIRECT3DDEVICE9 GetDevice()
	{ return DDevice;}

	D3DXMATRIX GetMatrxLocalTransform()
	{
		return matrixLocalTransform;
	}
	D3DXMATRIX GetMatrxGlobalTransform()
	{
		return matrixGlobalTransform;
	}

	void RecalcMatrixLocal()
	{
		D3DXMATRIX MatTemp;
		D3DXMatrixIdentity(&MatTemp);
		//SetLocalTransforMatrixToZero();
		//D3DXMatrixRotationAxis(&MatTemp,);
		D3DXMatrixRotationX(&MatTemp, vectorRotation.x);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixRotationY(&MatTemp, vectorRotation.y);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixRotationZ(&MatTemp, vectorRotation.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixScaling(&MatTemp, vectorScale.x, vectorScale.y, vectorScale.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixTranslation(&MatTemp, vectorPosition.x, vectorPosition.y, vectorPosition.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
	}
	void RecalcMatrixGlobal()
	{
		RecalcMatrixLocal();
		RecalcMatrixGlobalOnly();
	}

	void RecalcMatrixGlobalOnly()
	{
		if(parent != 0)
		{
			GAMVisElement *t_gve = dynamic_cast<GAMVisElement*>(parent);
			if(t_gve)
			{
				D3DXMatrixMultiply(&matrixGlobalTransform, &t_gve->GetMatrxGlobalTransform(), &matrixLocalTransform);
			}
		}
		else
		{
			matrixGlobalTransform = matrixLocalTransform;
		}
	}


	static D3DXMATRIX IdentityMatrix()
	{
		D3DXMATRIX tmp;
		D3DXMatrixIdentity(&tmp);
		return tmp;
	}

	void SetupLocalMatrinx(D3DXMATRIX t_locMatrix)
	{
		//todo: need refine!!!
	}
};
#endif