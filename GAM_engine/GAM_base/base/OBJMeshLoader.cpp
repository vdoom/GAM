#include <d3d9.h>
#include <d3dx9.h>
#include <sstream>
#include <vector>

#include "OBJMeshLoader.h"
#include "MeshObject.h"
#include "..\log\ErroreLoger.h"

//HRESULT OBJMeshLoader::LoadMesh(wstring meshFileName)
//{
//	D3DVERTEXELEMENT9 VERTEX_DECL[] =
//	{
//		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0},
//		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0},
//		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0},
//		D3DDECL_END()
//	};
//
//	struct VERTEX
//	{
//		D3DXVECTOR3 position;
//		D3DXVECTOR3 normal;
//		D3DXVECTOR2 texcoord;
//	};
//	vector <DWORD> m_Indices;      
//	vector <DWORD> m_Attributes;
//	vector <VERTEX> m_Vertices;
//	// Create temporary storage for the input data. Once the data has been loaded into
//	// a reasonable format we can create a D3DXMesh object and load it with the mesh data.
//	vector<D3DXVECTOR3> Positions ;
//	vector<D3DXVECTOR2> TexCoords;
//	vector<D3DXVECTOR3> Normals ;
//
//	DWORD dwCurSubset = 0;
//
//	// File input
//	WCHAR strCommand[256] = {0};
//	wifstream InFile( meshFileName.c_str() );
//	if( !InFile )
//	{
//		if(loger)
//		{
//			loger->SendToLog(TEXT("ErroreMeshLoad: Line 44 in OBJMeshLoader.cpp; Cant Open File")+ meshFileName);
//		}
//		return E_FAIL;
//	}
//	//       return DXTRACE_ERR( L"wifstream::open", E_FAIL );
//
//	for(; ; )
//	{
//		InFile >> strCommand;
//		if( !InFile )
//			break;
//
//		if( 0 == wcscmp( strCommand, L"#" ) )
//		{
//			// Comment
//		}
//		else if( 0 == wcscmp( strCommand, L"v" ) )
//		{
//			// Vertex Position
//			float x, y, z;
//			InFile >> x >> y >> z;
//			Positions.push_back( D3DXVECTOR3( x, y, z ) );
//		}
//		else if( 0 == wcscmp( strCommand, L"vt" ) )
//		{
//			// Vertex TexCoord
//			float u, v;
//			InFile >> u >> v;
//			TexCoords.push_back( D3DXVECTOR2( u, 1-v ) );
//		}
//		else if( 0 == wcscmp( strCommand, L"vn" ) )
//		{
//			// Vertex Normal
//			float x, y, z;
//			InFile >> x >> y >> z;
//			Normals.push_back( D3DXVECTOR3( x, y, z ) );
//			//Normals.push_back( D3DXVECTOR3( 1, 1, 1 ) );//( D3DXVECTOR3( x, y, z ) );
//		}
//		else if( 0 == wcscmp( strCommand, L"f" ) )
//		{
//			// Face
//			UINT iPosition, iTexCoord, iNormal;
//			VERTEX vertex;
//
//			for( UINT iFace = 0; iFace < 3; iFace++ )
//			{
//				ZeroMemory( &vertex, sizeof( VERTEX ) );
//
//				// OBJ format uses 1-based arrays
//				InFile >> iPosition;
//				vertex.position = Positions[ iPosition - 1 ];
//
//				if( '/' == InFile.peek() )
//				{
//					InFile.ignore();
//
//					if( '/' != InFile.peek() )
//					{
//						// Optional texture coordinate
//						InFile >> iTexCoord;
//						//mshfo<<iTexCoord - 1<<endl;
//						vertex.texcoord = TexCoords[iTexCoord - 1 ];
//					}
//
//					if( '/' == InFile.peek() )
//					{
//						InFile.ignore();
//
//						// Optional vertex normal
//						InFile >> iNormal;
//						vertex.normal = Normals[ iNormal - 1 ];
//					}
//				}
//				//DWORD index = AddVertex( iPosition, &vertex );
//				m_Vertices.push_back(vertex);
//			
//				//if ( index == (DWORD)-1 )
//				//	return E_OUTOFMEMORY;
//
//				m_Indices.push_back( m_Vertices.size()-1);
//			}
//			m_Attributes.push_back( dwCurSubset );
//		}
//		else if( 0 == wcscmp( strCommand, L"mtllib" ) )
//		{
//			// Material library
//			//InFile >> strMaterialFilename;
//		}
//		else if( 0 == wcscmp( strCommand, L"usemtl" ) )
//		{
//			// Material
//		   /* WCHAR strName[MAX_PATH] = {0};
//			InFile >> strName;*/
//		}
//		else
//		{
//			// Unimplemented or unrecognized command
//		}
//
//		InFile.ignore( 1000, '\n' );
//	}
//
//	InFile.close();
//
//
//	HRESULT hg = D3DXCreateMesh( m_Indices.size() / 3, m_Vertices.size(),
//						  D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX_DECL,
//						  DDevice, &mesh );
//	if(FAILED( hg ))
//	{
//		if(loger)
//		{
//			wstring number;
//			wstringstream wstrstrm;
//			wstrstrm << hg;
//			wstrstrm >> number;
//			loger->SendToLog(TEXT("ErroreMeshLoad: Line 160 in OBJMeshLoader.cpp ")+number);
//		}
//		return hg;
//	}
//
//	// Copy the vertex data
//	VERTEX* pVertex;
//	hg = mesh->LockVertexBuffer( 0, ( void** )&pVertex );
//	if(FAILED( hg ))
//	{
//		if(loger)
//		{
//			wstring number;
//			wstringstream wstrstrm;
//			wstrstrm << hg;
//			wstrstrm >> number;
//			loger->SendToLog(TEXT("ErroreMeshLoad: Line 176 in OBJMeshLoader.cpp ")+number);
//		}
//		return hg;
//	}
//
//	for( DWORD i=0; i<m_Vertices.size(); i++ )
//	{
//		pVertex[i] = m_Vertices[i];
//	}
//
//	mesh->UnlockVertexBuffer();
//	m_Vertices.clear();
//
//	DWORD* pIndex;
//	hg = mesh->LockIndexBuffer( 0, ( void** )&pIndex );
//	for( DWORD i=0; i<m_Indices.size(); i++ )
//	{
//		pIndex[i] = m_Indices[i];
//	}
//
//	mesh->UnlockIndexBuffer();
//	m_Indices.clear();
//
//	DWORD* pSubset;
//	hg = mesh->LockAttributeBuffer( 0, &pSubset ) ;
//	for( DWORD i=0; i<m_Attributes.size(); i++ )
//	{
//		pSubset[i] = m_Attributes[i];
//	}
//
//	mesh->UnlockAttributeBuffer();
//	m_Attributes.clear();
//
//	if(FAILED( hg))
//	{
//		if(loger)
//		{
//			wstring number;
//			wstringstream wstrstrm;
//			wstrstrm << hg;
//			wstrstrm >> number;
//			loger->SendToLog(TEXT("ErroreMeshLoad: Line 217 in OBJMeshLoader.cpp ")+number);
//		}
//	}
//
//	DWORD* aAdjacency = new DWORD[mesh->GetNumFaces() * 3];
//	if( aAdjacency == NULL )
//	{
//		if(loger)
//		{
//			wstring number;
//			wstringstream wstrstrm;
//			wstrstrm << E_OUTOFMEMORY;
//			wstrstrm >> number;
//			loger->SendToLog(TEXT("ErroreMeshLoad: Line 230 in OBJMeshLoader.cpp ")+number);
//		}
//		return E_OUTOFMEMORY;
//	}
//
//	mesh->GenerateAdjacency( 1e-6f, aAdjacency ) ;
//	mesh->OptimizeInplace( D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, aAdjacency, NULL, NULL, NULL ) ;
//	
//	if(loger && mesh)
//	{
//		loger->SendToLog(TEXT("ErroreMeshLoad: Seccesfull load!!! "));
//	}
//	return S_OK;
//}
//
HRESULT OBJMeshLoader::LoadMesh(wstring meshFileName, ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice)
{
	D3DVERTEXELEMENT9 VERTEX_DECL[] =
	{
		{ 0,  0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_POSITION, 0},
		{ 0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_NORMAL,   0},
		{ 0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT,  D3DDECLUSAGE_TEXCOORD, 0},
		D3DDECL_END()
	};

	struct VERTEX
	{
		D3DXVECTOR3 position;
		D3DXVECTOR3 normal;
		D3DXVECTOR2 texcoord;
	};
	vector <DWORD> m_Indices;      
	vector <DWORD> m_Attributes;
	vector <VERTEX> m_Vertices;
	// Create temporary storage for the input data. Once the data has been loaded into
	// a reasonable format we can create a D3DXMesh object and load it with the mesh data.
	vector<D3DXVECTOR3> Positions ;
	vector<D3DXVECTOR2> TexCoords;
	vector<D3DXVECTOR3> Normals ;

	DWORD dwCurSubset = 0;

	// File input
	WCHAR strCommand[256] = {0};
	wifstream InFile( meshFileName.c_str() );
	if( !InFile )
	{
		if(t_loger)
		{
			t_loger->SendToLog(TEXT("ErroreMeshLoad: Line 44 in OBJMeshLoader.cpp; Cant Open File")+ meshFileName);
		}
		return E_FAIL;
	}
	//       return DXTRACE_ERR( L"wifstream::open", E_FAIL );

	for(; ; )
	{
		InFile >> strCommand;
		if( !InFile )
			break;

		if( 0 == wcscmp( strCommand, L"#" ) )
		{
			// Comment
		}
		else if( 0 == wcscmp( strCommand, L"v" ) )
		{
			// Vertex Position
			float x, y, z;
			InFile >> x >> y >> z;
			Positions.push_back( D3DXVECTOR3( x, y, z ) );
		}
		else if( 0 == wcscmp( strCommand, L"vt" ) )
		{
			// Vertex TexCoord
			float u, v;
			InFile >> u >> v;
			TexCoords.push_back( D3DXVECTOR2( u, 1-v ) );
		}
		else if( 0 == wcscmp( strCommand, L"vn" ) )
		{
			// Vertex Normal
			float x, y, z;
			InFile >> x >> y >> z;
			Normals.push_back( D3DXVECTOR3( x, y, z ) );
			//Normals.push_back( D3DXVECTOR3( 1, 1, 1 ) );//( D3DXVECTOR3( x, y, z ) );
		}
		else if( 0 == wcscmp( strCommand, L"f" ) )
		{
			// Face
			UINT iPosition, iTexCoord, iNormal;
			VERTEX vertex;

			for( UINT iFace = 0; iFace < 3; iFace++ )
			{
				ZeroMemory( &vertex, sizeof( VERTEX ) );

				// OBJ format uses 1-based arrays
				InFile >> iPosition;
				vertex.position = Positions[ iPosition - 1 ];

				if( '/' == InFile.peek() )
				{
					InFile.ignore();

					if( '/' != InFile.peek() )
					{
						// Optional texture coordinate
						InFile >> iTexCoord;
						//mshfo<<iTexCoord - 1<<endl;
						vertex.texcoord = TexCoords[iTexCoord - 1 ];
					}

					if( '/' == InFile.peek() )
					{
						InFile.ignore();

						// Optional vertex normal
						InFile >> iNormal;
						vertex.normal = Normals[ iNormal - 1 ];
					}
				}
				//DWORD index = AddVertex( iPosition, &vertex );
				m_Vertices.push_back(vertex);
			
				//if ( index == (DWORD)-1 )
				//	return E_OUTOFMEMORY;

				m_Indices.push_back( m_Vertices.size()-1);
			}
			m_Attributes.push_back( dwCurSubset );
		}
		else if( 0 == wcscmp( strCommand, L"mtllib" ) )
		{
			// Material library
			//InFile >> strMaterialFilename;
		}
		else if( 0 == wcscmp( strCommand, L"usemtl" ) )
		{
			// Material
		   /* WCHAR strName[MAX_PATH] = {0};
			InFile >> strName;*/
		}
		else
		{
			// Unimplemented or unrecognized command
		}

		InFile.ignore( 1000, '\n' );
	}

	InFile.close();


	HRESULT hg = D3DXCreateMesh( m_Indices.size() / 3, m_Vertices.size(),
						  D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX_DECL,
						  t_DDevice, &t_mesh[0] );
	if(FAILED( hg ))
	{
		if(t_loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hg;
			wstrstrm >> number;
			t_loger->SendToLog(TEXT("ErroreMeshLoad: Line 160 in OBJMeshLoader.cpp ")+number);
		}
		return hg;
	}

	// Copy the vertex data
	VERTEX* pVertex;
	hg = t_mesh[0]->LockVertexBuffer( 0, ( void** )&pVertex );
	if(FAILED( hg ))
	{
		if(t_loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hg;
			wstrstrm >> number;
			t_loger->SendToLog(TEXT("ErroreMeshLoad: Line 176 in OBJMeshLoader.cpp ")+number);
		}
		return hg;
	}

	for( DWORD i=0; i<m_Vertices.size(); i++ )
	{
		pVertex[i] = m_Vertices[i];
	}

	t_mesh[0]->UnlockVertexBuffer();
	m_Vertices.clear();

	DWORD* pIndex;
	hg = t_mesh[0]->LockIndexBuffer( 0, ( void** )&pIndex );
	for( DWORD i=0; i<m_Indices.size(); i++ )
	{
		pIndex[i] = m_Indices[i];
	}

	t_mesh[0]->UnlockIndexBuffer();
	m_Indices.clear();

	DWORD* pSubset;
	hg = t_mesh[0]->LockAttributeBuffer( 0, &pSubset ) ;
	for( DWORD i=0; i<m_Attributes.size(); i++ )
	{
		pSubset[i] = m_Attributes[i];
	}

	t_mesh[0]->UnlockAttributeBuffer();
	m_Attributes.clear();

	if(FAILED( hg))
	{
		if(t_loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hg;
			wstrstrm >> number;
			t_loger->SendToLog(TEXT("ErroreMeshLoad: Line 217 in OBJMeshLoader.cpp ")+number);
		}
	}

	DWORD* aAdjacency = new DWORD[t_mesh[0]->GetNumFaces() * 3];
	if( aAdjacency == NULL )
	{
		if(t_loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << E_OUTOFMEMORY;
			wstrstrm >> number;
			t_loger->SendToLog(TEXT("ErroreMeshLoad: Line 230 in OBJMeshLoader.cpp ")+number);
		}
		return E_OUTOFMEMORY;
	}

	t_mesh[0]->GenerateAdjacency( 1e-6f, aAdjacency ) ;
	t_mesh[0]->OptimizeInplace( D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, aAdjacency, NULL, NULL, NULL ) ;
	
	if(t_loger && t_mesh)
	{
		t_loger->SendToLog(TEXT("ErroreMeshLoad: Seccesfull load!!! "));
	}
	return S_OK;
}

HRESULT OBJMeshLoader::LoadMesh(ErroreLoger* t_loger, DWORD* t_countMaterials, LPD3DXMESH *t_mesh, LPDIRECT3DDEVICE9 t_DDevice)
{
	return LoadMesh(file_name, t_loger, t_countMaterials, t_mesh, t_DDevice);
}