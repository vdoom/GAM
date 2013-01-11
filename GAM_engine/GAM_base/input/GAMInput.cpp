#include "GAMInput.h"

GAMInput::GAMInput(void)
{
	m_ppDIKB = NULL; 
	m_ppDDeviceKB = NULL;
	m_ppDIMO = NULL; 
	m_ppDDeviceMO = NULL;
	m_pErroreLoger = new ErroreLoger(wstring(TEXT("input.txt")));
	m_pErroreLoger->SendToLog(TEXT("GAMInput Created!"));
}

GAMInput::~GAMInput(void)
{
	TermKB();
	TermMO();
	m_pErroreLoger->SendToLog(TEXT("Destroy GAMInput!"));
	delete m_pErroreLoger;
}

void WINAPI GAMInput::TermKB()
{
	if (m_ppDIKB) 
	{ 
		if (m_ppDDeviceKB) 
		{ 
			// Always unacquire device before calling Release(). 
			m_ppDDeviceKB->Unacquire(); 
			m_ppDDeviceKB->Release();
			m_ppDDeviceKB = NULL; 
		} 
		m_ppDIKB->Release();
		m_ppDIKB = NULL; 
	} 
	m_pErroreLoger->SendToLog(TEXT("Terminate Mouse!"));
}
void WINAPI GAMInput::TermMO()
{ 
	if (m_ppDIMO) 
	{ 
		if (m_ppDDeviceMO) 
		{ 
			// Always unacquire device before calling Release(). 
			m_ppDDeviceMO->Unacquire(); 
			m_ppDDeviceMO->Release();
			m_ppDDeviceMO = NULL; 
		} 
		m_ppDIMO->Release();
		m_ppDIMO = NULL; 
	} 
	m_pErroreLoger->SendToLog(TEXT("Terminate KeyBoard!"));
}
HRESULT GAMInput::InitInputKB(HINSTANCE t_hinst)
{
	HRESULT hr; 

	// Create the DirectInput object. 
	hr = DirectInput8Create(t_hinst, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&m_ppDIKB, NULL); 

	//if FAILED(hr){ return FALSE; fuck<<"Can't create device \n";} 
	if (FAILED(hr)){return hr;}

	// Retrieve a pointer to an IDirectInputDevice8 interface 
	hr = m_ppDIKB->CreateDevice(GUID_SysKeyboard, &m_ppDDeviceKB, NULL); 

	if(FAILED(hr)) 
	{ 
		TermKB(); //fuck<<"Can't retrive keyboard \n";
		return hr;//FALSE; 
	} 

	hr = m_ppDDeviceKB->SetDataFormat(&c_dfDIKeyboard); 

	if(FAILED(hr))
	{ 
		TermKB(); //fuck<<"Can't get keyboard \n";
		return hr;//FALSE; 
	} 

	// Get access to the input device. 
	hr = m_ppDDeviceKB->Acquire(); 

	//if(hr==DIERR_INVALIDPARAM) fuck<<"An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called. This value is equal to the E_INVALIDARG standard COM return value.  \n";
	//if(hr==DIERR_NOTINITIALIZED) fuck<<"This object has not been initialized.  \n";
	//if(hr==DIERR_OTHERAPPHASPRIO) fuck<<"Another application has a higher priority level, preventing this call from succeeding. This value is equal to the E_ACCESSDENIED standard COM return value. This error can be returned when an application has only foreground access to a device but is attempting to acquire the device while in the background. \n";

	if(FAILED(hr))
	{ 
		TermKB(); //fuck<<"Can't get Access \n";
		return hr;//FALSE; 
	} 
	m_pErroreLoger->SendToLog(TEXT("Init KeyBoard Succes"));
	return S_OK;
}
HRESULT GAMInput::InitInputMO(HINSTANCE t_hinst)
{
	HRESULT hr; 

	hr = DirectInput8Create(t_hinst, DIRECTINPUT_VERSION, 
		IID_IDirectInput8, (void**)&m_ppDIMO, NULL); 


	if (FAILED(hr)){return hr;}//{ return FALSE; fuck<<"Can't create device \n";} 

	hr = m_ppDIMO->CreateDevice(GUID_SysMouse, &m_ppDDeviceMO, NULL); 
	//fuck<<"Mouse created; \n";
	if(FAILED(hr)) 
	{ 
		TermMO(); //fuck<<"Can't retrive keyboard \n";
		return hr;//FALSE; 
	} 

	hr = m_ppDDeviceMO->SetDataFormat(&c_dfDIMouse); 

	if(FAILED(hr)) 
	{ 
		TermMO(); //fuck<<"Can't get keyboard \n";
		return hr;//FALSE; 
	} 

	/*hr = g_lpDIDevice2->SetCooperativeLevel( hDlg, DISCL_BACKGROUND );
	if FAILED(hr) 
	{ 
	DI_TermM(); fuck<<"Can't set Cooperative \n";
	return FALSE; 
	} */

	DIPROPDWORD dipdw;
	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = 16; // Arbitary buffer size

	//if( FAILED( hr = g_lpDIDevice2->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph ) ) )
	//{TermMO();return hr;}	//fuck<<"Arbitary \n";

	hr = m_ppDDeviceMO->Acquire(); 

	if(FAILED(hr) )
	{ 
		TermMO(); //fuck<<"Can't get Access \n";
		return hr;//FALSE; 
	} 
	m_pErroreLoger->SendToLog(TEXT("Init Mouse Succes"));
	//return TRUE; 
	return S_OK;
}

HRESULT WINAPI GAMInput::KBInput(/*[out]*/char** t_data)
{
	//char     buffer[256]; 
	char *buffer = new char[256];
	for(int i =0; i++; i<256)buffer[i]=0;
	HRESULT  hr; 

	hr = m_ppDDeviceKB->GetDeviceState(sizeof(char)*256,(LPVOID)buffer); 
	//*t_data = buffer;
	if FAILED(hr) 
	{ 
		// If it failed, the device has probably been lost. 
		// Check for (hr == DIERR_INPUTLOST) 
		// and attempt to reacquire it here.
		int count=0;
		while( hr == DIERR_INPUTLOST && (count++)<100) 
		{hr = m_ppDDeviceKB->Acquire();}
		m_pErroreLoger->SendToLog(TEXT("GAMInput DIERR_INPUTLOST !!!"));
		t_data=0;
		return hr; 
	} 

	//// Turn the spaceship right or left 
	char *dfdf=0;// new char*();
	dfdf = buffer;
	//if(dfdf!=0)
	//{
	//if (KEYDOWN(dfdf, DIK_W)) m_pErroreLoger->SendToLog(TEXT("Press W"));
	//else  m_pErroreLoger->SendToLog(TEXT("DONT Press W"));}
	//// Turn right. 
	//else if(KEYDOWN(buffer, DIK_LEFT)) Camera->MoveRight(-0.1f); 
	//// Turn left. 
	//int mv[] = {0,0,0,0};
	//bool dontMove = false;
	*t_data = buffer;//t_data = (char**)buffer;
	return S_OK;
}
HRESULT GAMInput::MOButtonInput(DIDEVICEOBJECTDATA* moData)
{
	DIDEVICEOBJECTDATA didod[16 ];  // Receives buffered data 
	DWORD              dwElements;
	DWORD              i;
	HRESULT            hr;

	if( NULL == m_ppDDeviceMO ) 
		return E_FAIL;

	dwElements = 16;
	hr = m_ppDDeviceMO->GetDeviceData( sizeof(DIDEVICEOBJECTDATA),
		didod, &dwElements, 0 );
	if( hr != DI_OK ) 
	{
		hr =m_ppDDeviceMO->Acquire();
		while( hr == DIERR_INPUTLOST ) 
			hr = m_ppDDeviceMO->Acquire();

		// Update the dialog text 
		if( hr == DIERR_OTHERAPPHASPRIO || 
			hr == DIERR_NOTACQUIRED ) 
		{m_pErroreLoger->SendToLog(TEXT("GAMInput DIERR_OTHERAPPHASPRIO ||DIERR_NOTACQUIRED !!!"));}//fuck<<"fucka \n";

		return hr; 
	}
	moData = didod;
	return S_OK;
}
HRESULT GAMInput::MOStateInput(DIMOUSESTATE *t_moState)
{
	HRESULT       hr;
	DIMOUSESTATE dims2;      // DirectInput mouse state structure

	if( NULL == m_ppDDeviceMO ) 
		return E_FAIL;

	// Get the input's device state, and put the state in dims
	ZeroMemory( &dims2, sizeof(dims2) );
	hr = m_ppDDeviceMO->GetDeviceState( sizeof(DIMOUSESTATE), &dims2 );

	if(hr==DIERR_INPUTLOST ) m_pErroreLoger->SendToLog(TEXT("Access to the input device has been lost. It must be reacquired.\n"));
	if(hr==DIERR_INVALIDPARAM ) m_pErroreLoger->SendToLog(TEXT("An invalid parameter was passed to the returning function, or the object was not in a state that permitted the function to be called. This value is equal to the E_INVALIDARG standard COM return value.\n"));
	if(hr==DIERR_NOTACQUIRED )m_pErroreLoger->SendToLog(TEXT("The operation cannot be performed unless the device is acquired\n"));
	if(hr==DIERR_NOTINITIALIZED  ) m_pErroreLoger->SendToLog(TEXT("This object has not been initialized.\n"));
	if(hr==E_PENDING  )m_pErroreLoger->SendToLog(TEXT("Data is not yet available.\n"));

	if( FAILED(hr) ) 
	{
		m_pErroreLoger->SendToLog(TEXT("Can't get Access to data \n"));;
		hr = m_ppDDeviceMO->Acquire();
		while( hr == DIERR_INPUTLOST ) hr = m_ppDDeviceMO->Acquire();
		return hr;
	}
	t_moState = &dims2;
	return S_OK;
}
//void GAMInput::SetWindowHandle(HWND t_hDlg)
//{
//	m_hDlg = thDlg;
//}
//
//HWND GAMInput::GetWindowHandle()
//{
//	return m_hDlg
//}