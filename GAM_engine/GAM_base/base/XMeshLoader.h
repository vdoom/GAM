#include "MeshLoader.h"

#ifndef H_XMESH_LOADER
#define H_XMESH_LOADER

class XMeshLoader : public MeshLoader
{
private:

public:
	XMeshLoader()
	{}
	/*XMeshLoader(wstring meshFileName, MeshObject* TrefObject):MeshLoader(meshFileName, TrefObject)
	{}*/
	XMeshLoader(wstring meshFileName):MeshLoader(meshFileName)
	{}
	/*XMeshLoader(wstring meshFileName, ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice):MeshLoader(meshFileName, t_loger, t_countMaterials,  t_mesh, t_DDevice)
	{}*/
	virtual ~XMeshLoader()
	{}

	//virtual HRESULT LoadMesh(wstring meshFileName);
	virtual HRESULT LoadMesh(wstring meshFileName, ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice);
	virtual HRESULT LoadMesh(ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice);
};

#endif