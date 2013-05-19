#include <Windows.h>
#include <mmsystem.h>
#include <stdlib.h>
#include <tchar.h>
#include <strsafe.h>
#include <basetsd.h>
#include <dinput.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

#include "PingvApp.h"

PingvApp* m_app;

LRESULT WINAPI MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch( msg )
	{
	case WM_DESTROY:
		PostQuitMessage( 0 );
		return 0;
	}

	return DefWindowProc( hWnd, msg, wParam, lParam );
}

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT )
{
	m_app = new PingvApp();
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc, 0L, 0L, 
		GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
		TEXT("GAM_engine"), NULL };
	RegisterClassEx( &wc );

	// Create the application's window
	HWND hWnd = CreateWindow( TEXT("GAM_engine"),TEXT("GAME"), 
		WS_OVERLAPPEDWINDOW, 100, 100, 1024, 600,
		GetDesktopWindow(), NULL, wc.hInstance, NULL );
	//if(!DI_Init(hInst)) fuck<<"All Fuck";// init Direct input device
	//if(!DI_InitM(hInst,hWnd)) fuck<<"All Fuck M";// init Direct input device

	m_app->Init3D(hWnd);
	m_app->InitInput(hInst);
	//init3d( hWnd ); //init DirectX (3D)

	//D3DXMatrixIdentity(&matworld);

	ShowWindow( hWnd, SW_SHOWDEFAULT );
	UpdateWindow( hWnd );
	MSG msg; 
	ZeroMemory( &msg, sizeof(msg) );
	while( msg.message!=WM_QUIT )
	{
		if(  PeekMessage( &msg, NULL, 0U, 0U, PM_REMOVE ))
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
		m_app->Render();
		//else
		/*ProcessKBInput();
		ReadBufferedData( hWnd );
		ReadImmediateData( hWnd );
		Render();*/
		//fpsT++;
		/*if(TimeCounter+1000 <= timeGetTime())
		{
			TimeCounter=timeGetTime();
			fps=fpsT;
			fpsT=0;
		}*/
	}


	// Clean up everything and exit the app
	delete m_app;
	//Cleanup();
	UnregisterClass(TEXT("GAM_engine"), wc.hInstance );
	return 0;

	return 0;
}