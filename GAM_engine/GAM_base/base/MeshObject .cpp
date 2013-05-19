#include <d3d9.h>
#include <d3dx9.h>
#include <sstream>

#include "MeshObject.h"
#include "..\log\ErroreLoger.h"

void MeshObject::InitDefaultMaterials()
{
	ZeroMemory(&material, sizeof(D3DMATERIAL9));
	material.Diffuse.r=1.0f;
	material.Diffuse.g=1.0f;
	material.Diffuse.b=1.0f;
	material.Diffuse.a=0.0f;
	material.Ambient.r=1.0f;
	material.Ambient.g=1.0f;
	material.Ambient.b=1.0f;
	material.Ambient.a=0.0f;
	material.Specular.r=1.0f;
	material.Specular.g=1.0f;
	material.Specular.b=255.0f;
	material.Specular.a=0.0f;
	material.Emissive.r=0.25f;
	material.Emissive.g=0.25f;
	material.Emissive.b=0.25f;
	material.Emissive.a=0.25f;
	material.Power=1;
}

void MeshObject::DefaultInit()
{
	mesh = NULL;
	texture1 = NULL;
	InitDefaultMaterials();
}

void MeshObject::Init( LPD3DXMESH Tmesh, LPDIRECT3DTEXTURE9* Ttexture1, D3DMATERIAL9 Tmaterial, DWORD TcountMaterials, ErroreLoger* Tloger = 0)
{
	//typeStr 
	SetName(TEXT("newMesh "));
	if(mesh)
	{
		mesh->Release();
		mesh = NULL;
	}
	Tmesh->CloneMeshFVF(D3DXMESH_SYSTEMMEM, D3DFVF_MESHVERTEX, DDevice, &mesh);
	if(texture1)
	{
		texture1->Release();
		texture1 = NULL;
	}
	texture1 = *Ttexture1;
	texture1->AddRef();
	material = Tmaterial;
	countMaterials = TcountMaterials;

	loger = Tloger;
	InitDefaultMaterials();
}

void MeshObject::ReculcBounds()
{
	D3DXVECTOR3 Ul;
	D3DXVECTOR3 Lr;
	GAMVERTEX* vertices;
	LPDIRECT3DVERTEXBUFFER9 buff;
	mesh->GetVertexBuffer( &buff );
	buff->Lock( 0, 0, (void**)&vertices, 0 );
	D3DXComputeBoundingBox(&vertices[0].p, mesh->GetNumVertices(), D3DXGetFVFVertexSize(mesh->GetFVF()), &Lr, &Ul);
	buff->Unlock();
	buff->Release();
	//RecalcMatrixGlobal();
	bounds.SetBounds(Lr, Ul);
	bounds.SetTransformByMatrix(GetMatrxGlobalTransform());
}

Bounds MeshObject::GetBounds()
{
	return bounds;
}

HRESULT MeshObject::LoadMesh(wstring fileName)
{
	if(mesh)
	{
		mesh->Release();
		mesh = NULL;
	}
	MeshLoader* loader = MeshLoader::InstantiateMeshLoader(fileName);//, loger, &countMaterials, &mesh, DDevice);//MeshLoader::InstantiateMeshLoader(fileName, this);
	loader->LoadMesh(loger, &countMaterials, &mesh, DDevice);
	delete loader;
	ReculcBounds();
	return S_OK;
}

HRESULT MeshObject::LoadTexture(wstring fileName)
{
	if(texture1)
	{
		texture1->Release();
		texture1 = NULL;
	}

	HRESULT hr = D3DXCreateTextureFromFile( DDevice, fileName.c_str(), &texture1 );
	if( FAILED( hr ) )
	{
		if(loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hr;
			wstrstrm >> number;
			loger->SendToLog(GetTypeStr()+GetName()+TEXT("ErroreTextureLoad: Line 100 in MeshObjrct.cpp ")+number);
		}
		return hr;
	}
	return S_OK;
}

HRESULT MeshObject::LoadTextureBySurface(wstring fileName)
{
	/*if(texture1)
	{
		texture1->Release();
		texture1 = NULL;
	}*/
	//--------------------------------------------------
	HRESULT hr;

	LPDIRECT3DSURFACE9 surface = NULL;
	D3DXIMAGE_INFO info;
	hr = DDevice->CreateOffscreenPlainSurface(32,32, D3DFMT_X8R8G8B8, D3DPOOL_DEFAULT,&surface,NULL);
	hr = D3DXLoadSurfaceFromFile(surface, NULL,NULL, fileName.c_str(), NULL,D3DX_DEFAULT,D3DCOLOR_XRGB(0,0,0),&info);

	// This is the fun part.  Get a surface from the texture you want to copy *to*. You will load your first surface to this second surface which is basically a pointer to your texture.
	LPDIRECT3DSURFACE9 tempSurf;
	texture1->GetSurfaceLevel(0,&tempSurf);

	// Load the first surface to the texture (second surface)
	D3DXLoadSurfaceFromSurface(tempSurf,NULL,NULL,surface,NULL,NULL,D3DX_FILTER_NONE,0);

	// Finally, copy your new surface to your texture.  I do that by locking my surface, copying it to my texture, unlocking and so on...

	//surface->LockRect(&rect,NULL,0);
	//surface->UnlockRect();

	//HRESULT hr = D3DXCreateTextureFromFile( DDevice, fileName.c_str(), &texture1 );
	//----------------------------------------------------------
	if( FAILED( hr ) )
	{
		if(loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hr;
			wstrstrm >> number;
			loger->SendToLog(GetTypeStr()+GetName()+TEXT("ErroreTextureLoad: Line 100 in MeshObjrct.cpp ")+number);
		}
		return hr;
	}
	return S_OK;
}
HRESULT MeshObject::LoadObject(wstring meshFileName, wstring textureFileName)
{
	//LoadTexture(textureFileName);
	if(SUCCEEDED(LoadMesh(meshFileName)) && SUCCEEDED(LoadTexture(textureFileName)))
	{return S_OK;}
	else {return E_FAIL;}
}
void MeshObject::SetTexture(LPDIRECT3DTEXTURE9 Ttexture)
{
	if(texture1)
	{
		texture1->Release();
	}

	texture1 = Ttexture;
}
void MeshObject::SetMesh(LPD3DXMESH Tmesh)
{
	if(mesh)
	{
		mesh->Release();
	}

	mesh = Tmesh;
}
void MeshObject::SetTransformToMesh()
{
	GAMVERTEX* vertices;
	LPDIRECT3DVERTEXBUFFER9 buff;
	DWORD dwNumVertices = mesh->GetNumVertices();
	mesh->GetVertexBuffer( &buff );
	buff->Lock( 0, 0, (void**)&vertices, 0 );
	for( DWORD i=0; i<dwNumVertices; i++ )
	{ 
		vertices[i].p = TransformVector3ByMatrix(matrixGlobalTransform, vertices[i].p);
	}
	buff->Unlock();
	buff->Release();
}
void MeshObject::Draw()
{
	if(visible)
	{
		DDevice->SetTransform(D3DTS_WORLD, &matrixGlobalTransform);

		DDevice->SetMaterial( &material);   
		if(texture1)DDevice->SetTexture( 0,texture1);
		mesh->DrawSubset(0);
		DDevice->SetTransform(D3DTS_WORLD, &GAMVisElement::IdentityMatrix());
	}
	if(!items.empty())
	{
		for(int i=0; i<items.size(); i++)
		{
			items[i]->Draw();
		}
	}
}
GAMObject* MeshObject::Clone()
{
	MeshObject* tmpMeshobject = new MeshObject(DDevice, this->parent, mesh, &texture1, material, countMaterials);
	return (GAMObject*) tmpMeshobject;
}
wstring MeshObject::GetTypeStr()
{
	wstring typeStr = TEXT("MeshObject");
	return typeStr;
}
void MeshObject::SetMipMap(D3DXVECTOR2 TmipMap)
{
	GAMVERTEX* vertices;
	LPDIRECT3DVERTEXBUFFER9 buff;
	DWORD dwNumVertices = mesh->GetNumVertices();
	mesh->GetVertexBuffer( &buff );
	buff->Lock( 0, 0, (void**)&vertices, 0 );
	for( DWORD i=0; i<dwNumVertices; i++ )
	{ 
		vertices[i].tu  *= mipMap.x;
		vertices[i].tv  *= mipMap.y;
	}
	buff->Unlock();
	buff->Release();
}

HRESULT MeshObject::CreateTextureFromSurface(LPDIRECT3DSURFACE9 pSurface, RECT* pSrcRect, RECT* pDestRect, LPDIRECT3DTEXTURE9* ppTexture)
{//TODO: NEED REFINE & TEST
	int width, height;
	RECT Src;
	D3DSURFACE_DESC surfDesc;
	pSurface->GetDesc(&surfDesc);
	if( !pSrcRect ){
	width = surfDesc.Width;
	height = surfDesc.Height;
	Src.left = Src.top = 0;
	Src.right = width;
	Src.bottom = height;
	}
	else{
	width = pSrcRect->right - pSrcRect->left; // + 1;
	height = pSrcRect->bottom - pSrcRect->top; // + 1;
	Src = *pSrcRect;
	}

	D3DXCreateTexture(DDevice, width, height, 
	1, 0, surfDesc.Format, D3DPOOL_DEFAULT, ppTexture) ;

	// Retrieve the surface image of the texture.
	LPDIRECT3DSURFACE9 pTexSurface;
	LPDIRECT3DTEXTURE9 pTexture = *ppTexture;
	pTexture->GetLevelDesc(0, &surfDesc);
	pTexture->GetSurfaceLevel(0, &pTexSurface);

	// Create a clean surface to clear the texture with.
	LPDIRECT3DSURFACE9 pCleanSurface;
	D3DLOCKED_RECT lockRect;
	DDevice->CreateOffscreenPlainSurface(
	surfDesc.Width, surfDesc.Height, surfDesc.Format, D3DPOOL_DEFAULT, &pCleanSurface, NULL);
	pCleanSurface->LockRect(&lockRect, NULL, 0) ;
	memset((BYTE*)lockRect.pBits, 0, surfDesc.Height * lockRect.Pitch);
	pCleanSurface->UnlockRect() ;

	DDevice->UpdateSurface(pCleanSurface, NULL, pTexSurface, NULL);
	pCleanSurface->Release();

	// Copy the image to the texture.
	POINT destPoint = { 0, 0 };
	DDevice->UpdateSurface(pSurface, &Src, pTexSurface, &destPoint);
	pTexSurface->Release();

	return S_OK;
}

void MeshObject::SetShaders(LPD3DXEFFECT shader, int index)
{
	m_pEffect[index] = shader;
}
void MeshObject::SetTechnique(char* name, int index)
{
	if(name!=NULL)
	{
		m_pTechniqueName[index] = name;
		m_pEffect[index]->SetTechnique(name);
	}
}
void MeshObject::SetLightPos(D3DXVECTOR4 pos, int index)
{
	m_Light[index] = pos;
}
void MeshObject::SetShaderParam(int ef_index)
{
	//TODO: NEED REFINE
}