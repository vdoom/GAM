#ifndef H_GAMOBJECT
#define H_GAMOBJECT

#include <vector>
#include "..\log\ErroreLoger.h"
#include <Objbase.h>
#include <string>

#define D3DFVF_MESHVERTEX   (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_TEX1)

struct GAMVERTEX
{
    D3DXVECTOR3 p;
    D3DXVECTOR3 n;
    FLOAT       tu, tv;

	GAMVERTEX & operator = (const GAMVERTEX & other )
	{
		if (this != &other) 
        {
			p = other.p;
			n = other.n;
			tu = other.tu;
			tv = other.tv;
        }
        return *this;
	}
	//Need to finish other basic operators
};
//typedef GAMObject* LPGAMObject;
//class GAMObject;

class GAMObject
{
private:
protected:
	std::vector<GAMObject*> items;
	std::wstring name;
	GUID guid;
	GAMObject* parent;
	D3DXMATRIX matrixLocalTransform;
	D3DXMATRIX matrixGlobalTransform;
	D3DXVECTOR3 vectorPosition;
	D3DXVECTOR3 vectorRotation;
	D3DXVECTOR3 vectorScale;
	D3DXVECTOR2 mipMap;
	LPDIRECT3DDEVICE9 DDevice;
	ErroreLoger* loger;
	bool visible;
	
	void StartUpInit()
	{
		parent = 0;
		visible = true;
		name = std::wstring(TEXT("GAMObject"));
		vectorScale = D3DXVECTOR3(1, 1, 1);
		CoCreateGuid(&guid);
		D3DXMatrixIdentity(&matrixLocalTransform);
		D3DXMatrixIdentity(&matrixGlobalTransform);
		//RecalcMatrixGlobal();
	}
	/*void SetLocalTransforMatrixToZero()
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				matrixLocalTransform.m[i][j] = 0;
			}
		}
		D3DXMatrixIdentity(&matrixLocalTransform);
	}
	void SetGlobalTransforMatrixToZero()
	{
		for(int i = 0; i < 4; i++)
		{
			for(int j = 0; j < 4; j++)
			{
				matrixGlobalTransform.m[i][j] = 0;
			}
		}
		D3DXMatrixIdentity(&matrixGlobalTransform);
	}*/
public:
	GAMObject()
	{
		StartUpInit();
		CoCreateGuid(&guid);
	}
	GAMObject(LPDIRECT3DDEVICE9 TDDevice, ErroreLoger* Tloger=0)
	{
		DDevice = TDDevice;
		loger = Tloger;
		StartUpInit();
		CoCreateGuid(&guid);
	}
	GAMObject(GAMObject* Tparent)
	{
		parent = Tparent;
		StartUpInit();
		CoCreateGuid(&guid);
		//RecalcMatrixGlobal();
	}
	GAMObject(LPDIRECT3DDEVICE9 TDDevice, GAMObject* Tparent, ErroreLoger* Tloger=0)
	{
		parent = Tparent;
		DDevice = TDDevice;
		loger = Tloger;
		StartUpInit();
		CoCreateGuid(&guid);
	}
	virtual ~GAMObject()
	{
		std::vector<GAMObject*>::iterator pos;
		for(pos = items.begin(); pos!=items.end(); pos++)
		{
			GAMObject* tmp = *pos;
			tmp->Delete();
			//items.erase(pos);
		}
		items.clear();
	}

	virtual void Draw() = 0;
	
	virtual D3DXVECTOR3 GetPosition()
	{ return vectorPosition; }
	virtual D3DXVECTOR3 GetRotation()
	{ return vectorRotation; }
	virtual D3DXVECTOR3 GetScale()
	{ return vectorScale; }

	virtual void SetPosition(D3DXVECTOR3 pos)
	{ 
		vectorPosition = pos;	
		D3DXMATRIX MatTemp;
		D3DXMatrixIdentity(&MatTemp);
		D3DXMatrixTranslation(&MatTemp, vectorPosition.x, vectorPosition.y, vectorPosition.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		RecalcMatrixGlobalOnly();
		//RecalcMatrixGlobal();
	}
	virtual void SetRotation(D3DXVECTOR3 angles)
	{ 
		vectorRotation = angles; 
		D3DXMATRIX MatTemp;
		D3DXMatrixIdentity(&MatTemp);
		D3DXMatrixRotationX(&MatTemp, vectorRotation.x);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixRotationY(&MatTemp, vectorRotation.y);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixRotationZ(&MatTemp, vectorRotation.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		//D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		RecalcMatrixGlobalOnly();
	}
	virtual void SetScale(D3DXVECTOR3 scale)
	{ 
		vectorScale = scale; 
		D3DXMATRIX MatTemp;
		D3DXMatrixIdentity(&MatTemp);
		D3DXMatrixScaling(&MatTemp, vectorScale.x, vectorScale.y, vectorScale.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		RecalcMatrixGlobalOnly();
		//RecalcMatrixGlobal();
	}

	virtual void SetName(std::wstring str)
	{
		name = str;
	}

	virtual std::wstring GetName()
	{
		return name; 
	}

	virtual std::wstring GetTypeStr() = 0;

	void SetLoger(ErroreLoger* Tloger)
	{
		loger = Tloger;
	}
	
	bool IsVisible()
	{ return visible; }

	void SetVisible(bool Tvisible)
	{ visible = Tvisible; }

	void Show()
	{ visible = true; }

	void Hide()
	{ visible = false; }

	size_t ChildrenCount()
	{
		return items.size();
	}

	GUID GetGUID()
	{
		return guid;
	}

	std::wstring GetGUIDStr()
	{
		OLECHAR* bstrGuid;
		StringFromCLSID(guid, &bstrGuid);
		std::wstring str(bstrGuid);
		// ensure memory is freed
		::CoTaskMemFree(bstrGuid);

		return str;
	}

	vector<GAMObject*> GetObjectByName(std::wstring objname)
	{
		std::vector<GAMObject*> result;
		if(!items.empty())
		{
			for(int i=0; i<items.size(); i++)
			{
				if( objname == items[i]->GetName() )
					result.push_back((GAMObject*)items[i]);
			}
		}
		return result;
	}

	GAMObject* GetObjectByIndex(int objIndex)
	{
		if(objIndex>=0 && objIndex<items.size())
		{
			return (GAMObject*)items[objIndex];
		}
		else
		{
			return 0;
		}
	}
		
	GAMObject* GetObjectByGUID(GUID objGUID)
	{ return FindObjectByGUID(objGUID); }

	GAMObject* GetObjectByGUID(std::wstring objGUIDStr)
	{ return FindObjectByGUID(objGUIDStr); }

	GAMObject* FindObjectByGUID(GUID objGUID, bool recursively = false)
	{
		GAMObject* tmpreturn = 0;
		if(!items.empty())
		{
			if(!recursively)
			{
				for(int i = 0; i<items.size(); i++)
				{
					if(items[i]->GetGUID() == guid)
					{
						tmpreturn = items[i];
						break;
					}
				}
			}
			else
			{
				GAMObject* tmp = 0;
				for(int i = 0; i<items.size(); i++)
				{
					if(items[i]->GetGUID() == guid)tmpreturn = items[i];
					else tmp = FindObjectByGUID(objGUID, true);
					if(tmp != 0)
					{
						tmpreturn = tmp;
						break;
					}
				}
			}
		}
		return tmpreturn;
	}

	GAMObject* FindObjectByGUID(std::wstring objGUID, bool recursively = false)
	{
		GAMObject* tmpreturn = 0;
		if(!items.empty())
		{
			if(!recursively)
			{
				for(int i = 0; i<items.size(); i++)
				{
					if(items[i]->GetGUIDStr() == GetGUIDStr())
					{
						tmpreturn = (GAMObject*)items[i];
						break;
					}
				}
			}
			else
			{
				GAMObject* tmp = 0;
				for(int i = 0; i<items.size(); i++)
				{
					if(items[i]->GetGUIDStr() == GetGUIDStr())tmpreturn = items[i];
					else tmp = FindObjectByGUID(objGUID, true);
					if(tmp != 0)
					{
						tmpreturn = tmp;
						break;
					}
				}
			}
		}
		return tmpreturn;
	}

	void SetParent(GAMObject* Tparent)
	{
		parent = Tparent;
		//RecalcMatrixGlobal();
	}

	void SetDevice(LPDIRECT3DDEVICE9 TDDevice)
	{
		DDevice = TDDevice;
	}

	LPDIRECT3DDEVICE9 GetDevice()
	{ return DDevice;}

	void AddChild(GAMObject* obj)
	{
		obj->SetParent((GAMObject*)this);
		items.push_back((GAMObject*)obj);
	}

	GAMObject* GetChild(int index)
	{
		return GetObjectByIndex(index);
	}

	void RemoveChild(int index)
	{
		GetChild(index)->Delete();
	}

	void Delete()// use carefully
	{
		std::vector<GAMObject*>::iterator pos;
		for(pos = items.begin(); pos!=items.end(); pos++)
		{
			GAMObject* tmp = *pos;
			tmp->Delete();
			//items.erase(pos);
		}
		items.clear();

		delete this;
	}

	D3DXMATRIX GetMatrxLocalTransform()
	{
		return matrixLocalTransform;
	}
	D3DXMATRIX GetMatrxGlobalTransform()
	{
		return matrixGlobalTransform;
	}

	void RecalcMatrixLocal()
	{
		D3DXMATRIX MatTemp;
		D3DXMatrixIdentity(&MatTemp);
		//SetLocalTransforMatrixToZero();
		//D3DXMatrixRotationAxis(&MatTemp,);
		D3DXMatrixRotationX(&MatTemp, vectorRotation.x);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixRotationY(&MatTemp, vectorRotation.y);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixRotationZ(&MatTemp, vectorRotation.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixScaling(&MatTemp, vectorScale.x, vectorScale.y, vectorScale.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
		D3DXMatrixTranslation(&MatTemp, vectorPosition.x, vectorPosition.y, vectorPosition.z);
		D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
	}
	void RecalcMatrixGlobal()
	{
		RecalcMatrixLocal();
		RecalcMatrixGlobalOnly();
	}

	void RecalcMatrixGlobalOnly()
	{
		if(parent != 0)
		{
			//parent->RecalcMatrixLocal();
			D3DXMatrixMultiply(&matrixGlobalTransform, &parent->GetMatrxGlobalTransform(), &matrixLocalTransform);
		}
		else
		{
			matrixGlobalTransform = matrixLocalTransform;
		}
	}

	virtual GAMObject* Clone() = 0;

	static D3DXMATRIX IdentityMatrix()
	{
		D3DXMATRIX tmp;
		D3DXMatrixIdentity(&tmp);
		return tmp;
	}
};

#endif