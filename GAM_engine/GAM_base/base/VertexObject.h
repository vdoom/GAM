#pragma once

#ifndef H_VERTEX_OBJECT
#define H_VERTEX_OBJECT

#include <vector>
#include "GAMObject.h"
#include "Xmath.h"
#include "Bounds.h"

class VertexObject : public GAMObject
{
public:
	enum RenderType
	{
		Greed = 0,
		Plane = 1,
		Dots = 2
	};
	enum IndexingType
	{
		Triangle=0,
		Square = 1
	};
private:
protected:
	friend VertexObject;

	LPDIRECT3DTEXTURE9 texture1;
	D3DMATERIAL9 material;
	DWORD countMaterials; 	
	Bounds bounds;
	std::vector<GAMVERTEX> vertices;// S ETIM NADA SHOTO ZDELAT
	std::vector<int> indexes;// S ETIM NTOJE
	RenderType render_type;
	IndexingType indexing_type;
	long vertex_count;
	LPDIRECT3DVERTEXBUFFER9 vertex_bufer;
	LPDIRECT3DINDEXBUFFER9 index_bufer;

	void InitDefaultMaterials();
	void Init(std::vector<GAMVERTEX>&, std::vector<int>&, LPD3DXMESH Tmesh, LPDIRECT3DTEXTURE9 Ttexture1, D3DMATERIAL9 Tmaterial, DWORD TcountMaterials, ErroreLoger* Tloger = 0);
	void DefaultInit();
	void ReculcBounds();
	HRESULT CreateTextureFromSurface(LPDIRECT3DSURFACE9 pSurface, RECT* pSrcRect, RECT* pDestRect, LPDIRECT3DTEXTURE9* ppTexture);
public:

	VertexObject()
	{
		DefaultInit();
	}
	VertexObject(LPDIRECT3DDEVICE9 TDDevice, ErroreLoger* Tloger=0):GAMObject(TDDevice, Tloger)
	{
		DefaultInit();
	}
	VertexObject(GAMObject* TParent) : GAMObject(TParent)
	{
		DefaultInit();
	}
	VertexObject(LPDIRECT3DDEVICE9 TDDevice, GAMObject* Tparent, ErroreLoger* Tloger=0):GAMObject(TDDevice, Tparent, Tloger)
	{
		DefaultInit();
	}
	VertexObject(LPDIRECT3DDEVICE9 TDDevice, std::vector<GAMVERTEX>& TVertices, std::vector<int>& TIndexec, LPD3DXMESH Tmesh, LPDIRECT3DTEXTURE9 Ttexture1, D3DMATERIAL9 Tmaterial, DWORD TcountMaterials, ErroreLoger* Tloger = 0):GAMObject(TDDevice, Tloger)
	{
		DefaultInit();
		Init(TVertices, TIndexec, Tmesh, Ttexture1, Tmaterial, TcountMaterials, Tloger);
	}
	VertexObject(LPDIRECT3DDEVICE9 TDDevice, GAMObject* Tparent, std::vector<GAMVERTEX>& TVertices, std::vector<int>& TIndexec, LPD3DXMESH Tmesh, LPDIRECT3DTEXTURE9 Ttexture1, D3DMATERIAL9 Tmaterial, DWORD TcountMaterials, ErroreLoger* Tloger = 0):GAMObject(TDDevice, Tparent, Tloger)
	{
		DefaultInit();
		Init(TVertices, TIndexec, Tmesh, Ttexture1, Tmaterial, TcountMaterials, Tloger);
	}
	virtual ~VertexObject()
	{
		vertices.clear();
		indexes.clear();
		if(vertex_bufer)
		{
			vertex_bufer->Release();
		}
		if(index_bufer)
		{
			index_bufer->Release();
		}
		if(texture1)
		{
			texture1->Release();
		}
	}

	virtual wstring GetTypeStr();
	virtual GAMObject* Clone();
	virtual void Draw();

	void SetRenderType(RenderType TRendertpe){render_type = TRendertpe;}
	RenderType GetRenderType(){ return render_type;}

	HRESULT Create(); //OB'YAZATELNO DODELAT'
	HRESULT CreatePlane(D3DXVECTOR3 Tmin, D3DXVECTOR3 Tmax, IndexingType Ttype);
	HRESULT CreateByBounds();
	HRESULT LoadTexture(wstring fileName);
	HRESULT LoadData();
	void ChangeRenderMode(RenderType);

	static VertexObject* InstantiateVertexObjectByBox();
	static VertexObject* InstantiateVertexObjectByMesh();
	static VertexObject* InstantiateVertexObjectByPlane();
	static VertexObject* InstantiateVertexObjectByBounds();
	static VertexObject* InstantiateVertexObjectBySphere(LPDIRECT3DDEVICE9 t_Device, float radius = 10);
	static VertexObject* InstantiateVertexObjectByParallelepiped();
};

#endif