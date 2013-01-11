#include <d3d9.h>
#include <d3dx9.h>
#include <sstream>

#include "XMeshLoader.h"
#include "MeshObject.h"
#include "..\log\ErroreLoger.h"

//HRESULT XMeshLoader::LoadMesh(wstring meshFileName)
//{
//	HRESULT hr = D3DXLoadMeshFromX( meshFileName.c_str(), D3DXMESH_SYSTEMMEM, DDevice , NULL, 
//		&materialBuffer, NULL, countMaterials, &mesh );
//	if( FAILED( hr ) )
//	{
//		if(loger)
//		{
//			wstring number;
//			wstringstream wstrstrm;
//			wstrstrm << hr;
//			wstrstrm >> number;
//			loger->SendToLog(TEXT("ErroreMeshLoad: Line 21 in XMeshLoader.cpp ")+number);
//		}
//		return hr;
//	}
//
//	materialBuffer->Release();
//	mesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM ,D3DFVF_MESHVERTEX, DDevice, &mesh);
//
//	return S_OK;
//}

HRESULT XMeshLoader::LoadMesh(wstring meshFileName, ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice)
{
	HRESULT hr = D3DXLoadMeshFromX( meshFileName.c_str(), D3DXMESH_SYSTEMMEM, t_DDevice , NULL, 
		&materialBuffer, NULL, t_countMaterials, &t_mesh[0] );
	if( FAILED( hr ) )
	{
		if(t_loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hr;
			wstrstrm >> number;
			t_loger->SendToLog(TEXT("ErroreMeshLoad: Line 21 in XMeshLoader.cpp ")+number);
		}
		return hr;
	}

	materialBuffer->Release();
	t_mesh[0]->CloneMeshFVF(D3DXMESH_SYSTEMMEM ,D3DFVF_MESHVERTEX, t_DDevice, &t_mesh[0]);

	return S_OK;
}

HRESULT XMeshLoader::LoadMesh(ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice)
{
	return LoadMesh(file_name, t_loger, t_countMaterials, t_mesh, t_DDevice);
}

