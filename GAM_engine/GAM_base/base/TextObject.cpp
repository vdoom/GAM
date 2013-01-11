#include <d3d9.h>
#include <d3dx9.h>
#include <sstream>

#include "TextObject.h"

wstring TextObject::GetTypeStr()
{
	wstring typeStr = TEXT("TextObject");
	return typeStr;
}

HRESULT TextObject::CreateText(wstring t_text, float t_deviation, float t_extrusion , wstring t_font)
{
	hdc = CreateCompatibleDC(0);
    // Создание шрифта     
    hFont = CreateFont(0, 0, 0, 0, FW_NORMAL, false, false, false, false, DEFAULT_CHARSET, 
	 OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, t_font.c_str()); 
 
    // Делаем данный шрифт текущим шрифтом
    hFontOld = (HFONT)SelectObject(hdc, hFont);
    
    // Создание трехмерной сетки, представляющую строку текста
	HRESULT hr = D3DXCreateText(DDevice, hdc, t_text.c_str(), t_deviation, t_extrusion, &mesh, NULL, NULL);
	if(FAILED(hr))
	{
		if(loger)
		{
			wstring number;
			wstringstream wstrstrm;
			wstrstrm << hr;
			wstrstrm >> number;
			loger->SendToLog(GetTypeStr()+GetName()+TEXT("ErroreTextureLoad: Line 33 in MeshObjrct.cpp ")+number);
		}
	 return hr;
	}

    // Восстанавление бывшего до этого шрифта
    SelectObject(hdc, hFontOld);
    // Освобождение памяти указателя на шрифт
    DeleteObject(hFont);
    // Освобождение памяти дискриптора контекста устройства
    DeleteDC(hdc);
	
	return S_OK;
}

GAMObject* TextObject::Clone()
{
	TextObject* tmpMeshobject = new TextObject(DDevice, this->parent, mesh, &texture1, material, countMaterials);
	return (GAMObject*) tmpMeshobject;
}

