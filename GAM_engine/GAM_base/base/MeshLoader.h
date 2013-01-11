#include <string>
#include "..\log\ErroreLoger.h"

#ifndef H_MESH_LOADER
#define H_MESH_LOADER
class OBJMeshLoader;
class XMeshLoader;
class MeshObject;

class MeshLoader 
{
private:
protected:
	LPD3DXBUFFER materialBuffer;

	//LPDIRECT3DDEVICE9 DDevice;
	//ErroreLoger* loger;
	//DWORD* countMaterials; 	
	//LPD3DXMESH mesh;

	//MeshObject* refObject;
	std::wstring file_name;
public:

	MeshLoader()
	{}
	//MeshLoader(wstring meshFileName, MeshObject* TrefObject)
	//{
	//	file_name = meshFileName;
	//	refObject = TrefObject;
	//	//LoadMesh(file_name);
	//}
	MeshLoader(wstring meshFileName)
	{
		file_name = meshFileName;
	}
	/*MeshLoader(wstring meshFileName, ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice)
	{
		file_name = meshFileName;
		loger = t_loger;
		countMaterials = t_countMaterials;
		mesh = *t_mesh;
		DDevice = t_DDevice;
	}*/
	virtual ~MeshLoader()
	{}

	//virtual HRESULT LoadMesh();
	//virtual HRESULT LoadMesh(std::wstring meshFileName) = 0;
	virtual HRESULT LoadMesh(std::wstring meshFileName, ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice) = 0;
	virtual HRESULT LoadMesh(ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice) = 0;

	//static MeshLoader* InstantiateMeshLoader(wstring meshFileName, MeshObject* ref); //VOZ,OGNO NADA UBRAT'

	static MeshLoader* InstantiateMeshLoader(wstring meshFileName);

	//static MeshLoader* InstantiateMeshLoader(wstring meshFileName, ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice);
};

#endif

