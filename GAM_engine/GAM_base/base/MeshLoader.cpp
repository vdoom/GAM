#include <d3d9.h>
#include <d3dx9.h>

#include "MeshLoader.h"
#include "..\log\ErroreLoger.h"

#include "OBJMeshLoader.h"
#include "XMeshLoader.h"

//HRESULT MeshLoader::LoadMesh()
//{
//	return LoadMesh(file_name);
//}

//MeshLoader* MeshLoader::InstantiateMeshLoader(std::wstring meshFileName, MeshObject* ref)
//{
//		std::wstring tmpstr;
//		int indexdot = meshFileName.find_last_of('.');
//		for(int i = indexdot; i<meshFileName.length(); i++)
//		{
//			tmpstr.push_back(meshFileName[i]);
//		}
//		if(tmpstr.compare(TEXT(".obj"))==0 || tmpstr.compare(TEXT(".OBJ"))==0)
//		{
//			//mshfo<<"is OBJ"<<endl;
//			return new OBJMeshLoader(meshFileName, ref);
//		}
//		else
//		{
//			//mshfo<<"is X"<<endl;
//			//return new XMeshLoader(meshFileName, ref);
//		}
//}

MeshLoader* MeshLoader::InstantiateMeshLoader(wstring meshFileName)
{
	std::wstring tmpstr;
	int indexdot = meshFileName.find_last_of('.');
	for(int i = indexdot; i<meshFileName.length(); i++)
	{
		tmpstr.push_back(meshFileName[i]);
	}
	if(tmpstr.compare(TEXT(".obj"))==0 || tmpstr.compare(TEXT(".OBJ"))==0)
	{
		//mshfo<<"is OBJ"<<endl;
		return new OBJMeshLoader(meshFileName);
	}
	else
	{
		return new XMeshLoader(meshFileName);
	}
}

//MeshLoader* MeshLoader::InstantiateMeshLoader(wstring meshFileName, ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice)
//{
//		std::wstring tmpstr;
//		int indexdot = meshFileName.find_last_of('.');
//		for(int i = indexdot; i<meshFileName.length(); i++)
//		{
//			tmpstr.push_back(meshFileName[i]);
//		}
//		if(tmpstr.compare(TEXT(".obj"))==0 || tmpstr.compare(TEXT(".OBJ"))==0)
//		{
//			//mshfo<<"is OBJ"<<endl;
//			return new OBJMeshLoader(meshFileName, t_loger, t_countMaterials, t_mesh, t_DDevice);
//		}
//		else
//		{
//			//mshfo<<"is X"<<endl;
//			//return new XMeshLoader(meshFileName, t_loger, t_countMaterials, t_mesh, t_DDevice);
//		}
//}




