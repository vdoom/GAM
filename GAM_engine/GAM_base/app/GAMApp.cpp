#include "GAMApp.h"
#include <D3dx9math.h>
#include <d3d9.h>
#include <d3dx9.h>

GAMApp::GAMApp(void)
{
	m_pD3D = NULL;
	m_pD3DDevice = NULL;
	m_pCamera = NULL;//new CXCamera();
	m_pInput = new GAMInput();
	m_pObjects = new vector<GAMObject*>();
	m_pErroreLoger = new ErroreLoger(wstring(TEXT("app.txt")));
}

GAMApp::~GAMApp(void)
{
	Cleanup();
	delete m_pInput;
}

GAMTime GAMApp::GetTime()
{
	return m_time;
}

void GAMApp::DefaulInitPresentParameters()
{
	ZeroMemory( &m_d3dpp, sizeof(m_d3dpp) );
	m_d3dpp.Windowed = true;
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//d3dpp.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	m_d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	m_d3dpp.BackBufferCount = 3;
	m_d3dpp.BackBufferWidth = 1024;
	m_d3dpp.BackBufferHeight = 600;
	m_d3dpp.EnableAutoDepthStencil = TRUE;
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
}

LPDIRECT3D9 GAMApp::GetDirect3D9()
{
	return m_pD3D;
}
LPDIRECT3DDEVICE9 GAMApp::GetDirect3DDevice9()
{
	return m_pD3DDevice;
}
D3DXMATRIXA16 GAMApp::GetProjectionMatrix()
{
	return m_matProj;
}

D3DPRESENT_PARAMETERS GAMApp::GetD3DPresentParameters()
{
	return m_d3dpp;
}
CXCamera* GAMApp::GetCamera()
{
	return m_pCamera;
}

HRESULT GAMApp::Init3D(HWND t_hWnd)
{

	if (NULL==(m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		return E_FAIL;
	// Get the current desktop display mode, so we can set up a backa
	// buffer of the same format
	D3DDISPLAYMODE d3ddm;
	if( FAILED( m_pD3D->GetAdapterDisplayMode( D3DADAPTER_DEFAULT, &d3ddm ) ) )
		return E_FAIL;
	m_pD3D->CheckDeviceMultiSampleType( D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL , D3DFMT_R8G8B8, true,//FALSE, 
		D3DMULTISAMPLE_2_SAMPLES, NULL );
	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp; 
	ZeroMemory( &d3dpp, sizeof(d3dpp) );
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	//d3dpp.MultiSampleType = D3DMULTISAMPLE_2_SAMPLES;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 3;
	d3dpp.BackBufferWidth = 1366;
	d3dpp.BackBufferHeight = 768;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	//ID3DXFont         *g_pFont = NULL;

	//ID3DXFont* g_pFont=new ID3DXFont[1] ;
	// Create the D3DDevice
	if( FAILED( m_pD3D->CreateDevice( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, t_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		//D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pD3DDevice ) ) )

	{
		return E_FAIL;
	}

	D3DXMatrixPerspectiveFovLH( &m_matProj, D3DX_PI/4, 16/8, 1.0f, 500.0f );
	m_pD3DDevice->SetTransform( D3DTS_PROJECTION, &m_matProj );

	m_pCamera = new CXCamera(m_pD3DDevice);
	m_pCamera->LookAtPos(&D3DXVECTOR3(0.0f, 15.0f,0.1f),&D3DXVECTOR3(0.0f, 0.0f, 0.0f),&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	m_pCamera->Roll(D3DXToRadian(180));

	m_pD3DDevice->SetRenderState( D3DRS_ZENABLE, TRUE );
	//g_pD3DDevice->SetRenderState( D3DRS_FILLMODE ,D3DFILL_WIREFRAME );
	//g_pD3DDevice->SetRenderState( D3DRS_AMBIENT, 0xffffffff );

	m_pD3DDevice->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	//g_pD3DDevice->SetRenderState(D3DRS_FOGENABLE , TRUE );
	m_pD3DDevice->SetRenderState( D3DRS_CULLMODE, D3DCULL_NONE );
	m_pD3DDevice->SetRenderState( D3DRS_LIGHTING, TRUE );

	return S_OK;
}

void GAMApp::Cleanup()
{
	if( m_pD3DDevice != NULL )
		m_pD3DDevice->Release();

	if( m_pD3D != NULL )
		m_pD3D->Release();
	for (vector<GAMObject*>::const_iterator it = m_pObjects->begin(); it != m_pObjects->end(); ++it) 
	{
		GAMObject* tmp = *it;
		tmp->Delete();
	}
	m_pObjects->clear();

	delete m_pCamera;
}

void GAMApp::Render()
{
	//proccesing input actions
	m_pInputProcessor->UpdateInput(this);
	
	//update time
	m_time.UpdateTime();

	//draw scene
	m_pD3DDevice->Clear( 0, NULL, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER, 
		D3DCOLOR_XRGB(0,120,0), 1.0f, 0 );
	m_pD3DDevice->BeginScene();

	D3DMATERIAL9 mtrl;
	ZeroMemory( &mtrl, sizeof(mtrl) );
	mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
	mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
	mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
	mtrl.Diffuse.a = mtrl.Ambient.a = 0.50f;
	m_pD3DDevice->SetMaterial( &mtrl );


	D3DXVECTOR3 vecDir;
	D3DLIGHT9 light;
	ZeroMemory( &light, sizeof(light) );
	light.Type = D3DLIGHT_DIRECTIONAL;

	light.Range = 100000;//10000000.0f;
	//light.Specular.b=255;
	//g_pD3DDevice->SetLight( 0, &light );

	//g_pD3DDevice->LightEnable( 0, TRUE);

	light.Diffuse.r = 50.0f;
	light.Diffuse.g = 50.0f;
	light.Diffuse.b = 50.0f;

	light.Direction = D3DXVECTOR3(0,0,-1);
	/*if(plr!=NULL)
	{
		D3DXVECTOR3 newVec;
		D3DXVec3Normalize(&newVec, &plr->POS);
		light.Direction = newVec;
	}*/
	//light.Direction
	//light.Position = plr->POS;
	m_pD3DDevice->SetLight( 1, &light );

	m_pD3DDevice->LightEnable( 1, TRUE);

	m_pD3DDevice->SetRenderState( D3DRS_MULTISAMPLEANTIALIAS, TRUE );
	m_pD3DDevice->SetSamplerState(0,D3DSAMP_MAGFILTER, D3DTEXF_ANISOTROPIC);
	m_pD3DDevice->SetSamplerState(0,D3DSAMP_MAXANISOTROPY, 16);
	//        g_pD3DDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );

	for (vector<GAMObject*>::const_iterator it = m_pObjects->begin(); it != m_pObjects->end(); ++it) 
	{
		if(((GAMObject*)*it)->IsNeedKill())
		{
			((GAMObject*)*it)->Delete();
			
			if((it+1) != m_pObjects->end())
			{
				++it;
				m_pObjects->erase(it-1);
			}
			else
			{
				m_pObjects->erase(it);
				break;
			}
		}
		else
		{
			((GAMObject*)*it)->Draw();
		}
	}

	m_pCamera->Update();
	m_pD3DDevice->EndScene();
	m_pD3DDevice->Present( NULL, NULL, NULL, NULL );
}


HRESULT GAMApp::InitInput(HINSTANCE t_hinst)
{
	HRESULT hr = m_pInput->InitInputKB(t_hinst);
	if(FAILED(hr))
	{return hr;}

	hr = m_pInput->InitInputMO(t_hinst);
	if(FAILED(hr))
	{return hr;}

	return S_OK;
}
HRESULT GAMApp::InitInputProcessor(InputProcessorBase* t_pInputProcessor)
{
	m_pInputProcessor = t_pInputProcessor;
	return S_OK;
}