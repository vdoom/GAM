#include <d3d9.h>
#include <d3dx9.h>
#include <sstream>

#include "VertexObject.h"

void VertexObject::DefaultInit()
{
	InitDefaultMaterials();
	texture1 = NULL;
	vertex_bufer = NULL;
	index_bufer = NULL;
	render_type = RenderType::Plane;
	indexing_type = IndexingType::Square;
}

void VertexObject::InitDefaultMaterials()
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
	material.Emissive.r=0.0f;
	material.Emissive.g=0.0f;
	material.Emissive.b=0.0f;
	material.Emissive.a=0.0f;
	material.Power=1;
}

void VertexObject::Init(std::vector<GAMVERTEX>& TVertices, std::vector<int>& TIndexec, LPD3DXMESH Tmesh, LPDIRECT3DTEXTURE9 Ttexture1, D3DMATERIAL9 Tmaterial, DWORD TcountMaterials, ErroreLoger* Tloger)
{
	//typeStr 
	
	for(int i=0; i<TVertices.size(); i++)
	{
		vertices.push_back(TVertices[i]);
	}

	for(int i=0; i<TIndexec.size(); i++)
	{
		indexes.push_back(TIndexec[i]);
	}

	SetName(TEXT("newVetices "));

	if(texture1)
	{
		texture1->Release();
		texture1 = NULL;
	}
	*texture1 = *Ttexture1;
	texture1->AddRef();
	
	countMaterials = TcountMaterials;

	loger = Tloger;

	material = Tmaterial;
}

void VertexObject::ReculcBounds()
{
	D3DXVECTOR3 Ul;
	D3DXVECTOR3 Lr;
	GAMVERTEX* c_vertices;
	vertex_bufer->Lock( 0, 0, (void**)&c_vertices, 0 );
	D3DXComputeBoundingBox(&c_vertices[0].p, vertex_count, D3DXGetFVFVertexSize(D3DFVF_MESHVERTEX), &Lr, &Ul);
	vertex_bufer->Unlock();
	//RecalcMatrixGlobal();
	bounds.SetBounds(Lr, Ul);
	bounds.SetTransformByMatrix(GetMatrxGlobalTransform());
}

wstring VertexObject::GetTypeStr()
{
	wstring typeStr = TEXT("VertexObject");
	return typeStr;
}

HRESULT VertexObject::CreatePlane(D3DXVECTOR3 Tmin, D3DXVECTOR3 Tmax, IndexingType Ttype)
{
	indexing_type = Ttype;
	short Indeces[6];
	GAMVERTEX vertices[] =
	{
		{  D3DXVECTOR3(Tmin.x, (Tmin.y+Tmax.y)/2, Tmax.z ), D3DXVECTOR3(1, 1, 1), 0.0, 0.0 },
		{  D3DXVECTOR3(Tmax.x, (Tmin.y+Tmax.y)/2, Tmax.z ), D3DXVECTOR3(1, 1, 1), 1.0, 0.0 },
		{  D3DXVECTOR3(Tmax.x, (Tmin.y+Tmax.y)/2, Tmin.z ), D3DXVECTOR3(1, 1, 1), 1.0, 1.0 },
		{  D3DXVECTOR3(Tmin.x, (Tmin.y+Tmax.y)/2, Tmin.z ), D3DXVECTOR3(1, 1, 1), 0.0, 1.0 }
	};

	if(vertex_bufer)
	{ vertex_bufer->Release(); }
	if(index_bufer)
	{ index_bufer->Release(); }

	HRESULT hr = DDevice->CreateVertexBuffer( 4*sizeof(GAMVERTEX),
                                0, D3DFVF_MESHVERTEX,
                                D3DPOOL_DEFAULT, &vertex_bufer, NULL );
	if(FAILED(hr))
	{
		if(loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hr;
			wstrstrm >> number;
			loger->SendToLog(GetTypeStr()+GetName()+TEXT("CreateVertexBuffer: Line 117 in VertexObject.cpp ")+number);
		}
		return hr;
	}
	VOID* pVertix;
	hr = vertex_bufer->Lock( 0, sizeof(vertices), (void**)&pVertix, 0 );
	if(FAILED(hr))
	{
		if(loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hr;
			wstrstrm >> number;
			loger->SendToLog(GetTypeStr()+GetName()+TEXT("LockVertexBuffer: Line 131 in VertexObject.cpp ")+number);
		}
		return hr;
	}
	memcpy( pVertix, vertices, sizeof(vertices) );
	vertex_bufer->Unlock();

	hr = DDevice->CreateIndexBuffer(sizeof(short)*6,0,D3DFMT_INDEX16, D3DPOOL_DEFAULT, &index_bufer, NULL );
	if(FAILED(hr))
	{
		if(loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hr;
			wstrstrm >> number;
			loger->SendToLog(GetTypeStr()+GetName()+TEXT("CreateIndexBuffer: Line 147 in VertexObject.cpp ")+number);
		}
		return hr;
	}
	if(indexing_type == IndexingType::Square)
	{
		Indeces[0]=0;
		Indeces[1]=1;
		Indeces[2]=2;
		Indeces[3]=3;
		Indeces[4]=0;
		Indeces[5]=1;
	}
	else if(indexing_type == IndexingType::Triangle)
	{
		Indeces[0]=0;
		Indeces[1]=2;
		Indeces[2]=1;
		Indeces[3]=0;
		Indeces[4]=3;
		Indeces[5]=2;
		/*Indeces[0]=0;
		Indeces[1]=2;
		Indeces[2]=1;
		Indeces[3]=0;
		Indeces[4]=2;
		Indeces[5]=3;*/
	}
	VOID* IndexData = NULL;
	hr = index_bufer->Lock(0, 0, &IndexData, 0);
	if(FAILED(hr))
	{
		if(loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hr;
			wstrstrm >> number;
			loger->SendToLog(GetTypeStr()+GetName()+TEXT("LockIndexBuffer: Line 185 in VertexObject.cpp ")+number);
		}
		return hr;
	}
	memcpy(IndexData, (void*)&Indeces, sizeof(Indeces));
	index_bufer->Unlock();

	//D3DXCreateTextureFromFile(pDevice,TEXT("white.jpg"),&g_texture);

	return S_OK;
}

void VertexObject::ChangeRenderMode(RenderType TrenType)
{
	render_type = TrenType;
}
//HRESULT VertexObject::ChangeIndexingMode(IndexingType TindexingMode)
//{
//	indexing_type = TindexingMode;
//	short Indeces[6];
//	HRESULT hr = DDevice->CreateIndexBuffer(sizeof(short)*6,0,D3DFMT_INDEX16, D3DPOOL_DEFAULT, &index_bufer, NULL );
//	if(FAILED(hr))
//	{
//		if(loger)
//		{
//			wstring number;
//			wstringstream wstrstrm;
//			wstrstrm << hr;
//			wstrstrm >> number;
//			loger->SendToLog(GetTypeStr()+GetName()+TEXT("CreateIndexBuffer: Line 147 in VertexObject.cpp ")+number);
//		}
//		return hr;
//	}
//	if(indexing_type == IndexingType::Square)
//	{
//		Indeces[0]=0;
//		Indeces[1]=1;
//		Indeces[2]=2;
//		Indeces[3]=3;
//		Indeces[4]=0;
//		Indeces[5]=1;
//	}
//	else if(indexing_type == IndexingType::Triangle)
//	{
//		Indeces[0]=0;
//		Indeces[1]=2;
//		Indeces[2]=1;
//		Indeces[3]=0;
//		Indeces[4]=3;
//		Indeces[5]=2;
//		/*Indeces[0]=0;
//		Indeces[1]=2;
//		Indeces[2]=1;
//		Indeces[3]=0;
//		Indeces[4]=2;
//		Indeces[5]=3;*/
//	}
//	VOID* IndexData = NULL;
//	hr = index_bufer->Lock(0, 0, &IndexData, 0);
//	return S_OK;
//}
HRESULT VertexObject::LoadTexture(wstring fileName)
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
			loger->SendToLog(GetTypeStr()+GetName()+TEXT("ErroreTextureLoad: Line 172 in VertexObject.cpp ")+number);
		}
		return hr;
	}
	return S_OK;
}

void VertexObject::Draw()
{
	if(DDevice == NULL)
	{
		loger->SendToLog(_T("DDevice Is Null!!!"));
	}
	/*else
	{
		loger->SendToLog(_T("DDevice Is NOT NULL!!!"));
	}*/
	DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,TRUE);
	//DDevice->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCCOLOR  );
	//DDevice->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_INVSRCCOLOR );

	DDevice->SetMaterial( &material);  
	if(texture1)
	{
		DDevice->SetTexture( 0,texture1);
	}
	
	DDevice->SetStreamSource( 0, vertex_bufer, 0, sizeof(GAMVERTEX) );
	DDevice->SetIndices(index_bufer);
	
	DDevice->SetFVF( D3DFVF_MESHVERTEX);
	if(render_type == RenderType::Plane)DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0,0,4,0,3);
	DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
	if(render_type == RenderType::Greed)DDevice->DrawIndexedPrimitive(D3DPT_LINESTRIP, 0,0,4,0,6);
}

//Todo: Need refine !!!!!!!!!!!!!!!!!!!!!!
GAMObject* VertexObject::Clone()
{
	//NADA DODELAT' !!!!!!!!!!!!!!!!!!!!!!
	return new VertexObject();
}

HRESULT VertexObject::CreateTextureFromSurface(LPDIRECT3DSURFACE9 pSurface, RECT* pSrcRect, RECT* pDestRect, LPDIRECT3DTEXTURE9* ppTexture)
{
	int width, height;
	RECT Src;
	D3DSURFACE_DESC surfDesc;
	pSurface->GetDesc(&surfDesc);

	if( !pSrcRect )
	{
		width = surfDesc.Width;
		height = surfDesc.Height;
		Src.left = Src.top = 0;
		Src.right = width;
		Src.bottom = height;
	}
	else
	{
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

VertexObject* VertexObject::InstantiateVertexObjectBySphere(LPDIRECT3DDEVICE9 t_Device, float radius)// NADA DODELAT'
{
	LPD3DXMESH tmp_mesh = NULL;
	HRESULT hr = D3DXCreateSphere(t_Device, radius, 10, 10, &tmp_mesh, NULL);
	VertexObject* tmp_vertexObject = new VertexObject();
	tmp_vertexObject->SetDevice(t_Device);
	tmp_vertexObject->vertex_count = tmp_mesh->GetNumVertices();
	tmp_mesh->GetVertexBuffer(&tmp_vertexObject->vertex_bufer);
	tmp_mesh->GetIndexBuffer(&tmp_vertexObject->index_bufer);
	//.........................................................

	return new VertexObject();
}