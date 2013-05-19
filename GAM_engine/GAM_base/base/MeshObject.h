#ifndef H_MESH_OBJECT
#define H_MESH_OBJECT

#include "GAMVisElemen.h"
#include "MeshLoader.h"
#include "Xmath.h"
#include "Bounds.h"

using namespace XMath;

const int MAX_OBJECT_EFFECT = 10;
class MeshObject : public GAMVisElement
{
private:
	
protected:
	
	LPD3DXMESH mesh;
	//----For-shaders-------------------- 
	LPD3DXEFFECT m_pEffect[MAX_OBJECT_EFFECT];
	char* m_pTechniqueName[MAX_OBJECT_EFFECT];
	D3DXVECTOR4 m_Light[MAX_OBJECT_EFFECT];
	//---------------------------------
	LPDIRECT3DTEXTURE9 texture1;
	D3DMATERIAL9 material;
	DWORD countMaterials; 	
	Bounds bounds;
	bool m_useShaders;

	void InitDefaultMaterials();
	void DefaultInit();
	void Init( LPD3DXMESH Tmesh, LPDIRECT3DTEXTURE9* Ttexture1, D3DMATERIAL9 Tmaterial, DWORD TcountMaterials, ErroreLoger* Tloger);
	void ReculcBounds();
	HRESULT CreateTextureFromSurface(LPDIRECT3DSURFACE9 pSurface, RECT* pSrcRect, RECT* pDestRect, LPDIRECT3DTEXTURE9* ppTexture);

public:
	MeshObject()
	{
		DefaultInit();
	}
	MeshObject(LPDIRECT3DDEVICE9 TDDevice, ErroreLoger* Tloger=0) : GAMVisElement(TDDevice, Tloger)
	{
		DefaultInit();
	}
	MeshObject(GAMObject* Tparent) : GAMVisElement(Tparent)
	{
		DefaultInit();
	}
	MeshObject(LPDIRECT3DDEVICE9 TDDevice, GAMObject* Tparent, ErroreLoger* Tloger=0):GAMVisElement(TDDevice, Tparent, Tloger)
	{
		DefaultInit();
	}
	MeshObject(LPDIRECT3DDEVICE9 TDDevice, LPD3DXMESH Tmesh, LPDIRECT3DTEXTURE9* Ttexture1, D3DMATERIAL9 Tmaterial, DWORD TcountMaterials, ErroreLoger* Tloger = 0):GAMVisElement(TDDevice, Tloger)
	{
		DefaultInit();
		Init(Tmesh,  Ttexture1, Tmaterial, TcountMaterials, Tloger);
	}
	MeshObject(LPDIRECT3DDEVICE9 TDDevice, GAMObject* Tparent, LPD3DXMESH Tmesh, LPDIRECT3DTEXTURE9* Ttexture1, D3DMATERIAL9 Tmaterial, DWORD TcountMaterials, ErroreLoger* Tloger = 0) : GAMVisElement(TDDevice, Tparent, Tloger)
	{
		DefaultInit();
		Init(Tmesh,  Ttexture1, Tmaterial, TcountMaterials, Tloger);
	}
	virtual ~MeshObject()
	{
		if(mesh) mesh->Release();
		if(texture1) texture1->Release();
	}
	
	Bounds GetBounds();

	virtual HRESULT LoadMesh(wstring fileName);

	virtual HRESULT LoadTexture(wstring fileName);

	virtual HRESULT LoadTextureBySurface(wstring fileName);

	virtual HRESULT LoadObject(wstring meshFileName, wstring textureFileName);

	virtual void SetTexture(LPDIRECT3DTEXTURE9 Ttexture);

	virtual void SetMesh(LPD3DXMESH Tmesh);

	virtual void SetTransformToMesh();

	virtual void Draw();

	virtual GAMObject* Clone();

	virtual wstring GetTypeStr();

	virtual void SetMipMap(D3DXVECTOR2 TmipMap);

	//---For-Shaders-----------
	void SetShaders(LPD3DXEFFECT shader, int index);
	void SetTechnique(char* name, int index);
	void SetLightPos(D3DXVECTOR4 pos, int index);
	void SetShaderParam(int ef_index);
	//--------------------------

};

#endif