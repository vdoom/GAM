#include "MeshLoader.h"

#ifndef H_OBJMESH_LOADER
#define H_OBJMESH_LOADER

class OBJMeshLoader : public MeshLoader
{
private:

public:
	OBJMeshLoader()
	{}
	/*OBJMeshLoader(wstring meshFileName, MeshObject* TrefObject):MeshLoader(meshFileName, TrefObject)
	{}*/
	OBJMeshLoader(wstring meshFileName):MeshLoader(meshFileName)
	{}
	/*OBJMeshLoader(wstring meshFileName, ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice):MeshLoader(meshFileName, t_loger, t_countMaterials, t_mesh, t_DDevice)
	{}*/
	virtual ~OBJMeshLoader()
	{}

	//virtual HRESULT LoadMesh(wstring meshFileName);
	virtual HRESULT LoadMesh(wstring meshFileName, ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice);
	virtual HRESULT LoadMesh(ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice);
};

#endif