#ifndef H_GAMOBJECT
#define H_GAMOBJECT

#include <vector>
#include "..\log\ErroreLoger.h"
#include <Objbase.h>
#include <string>


//typedef GAMObject* LPGAMObject;
//class GAMObject;

class GAMObject
{
private:
protected:
	std::vector<GAMObject*> items;
	std::wstring name;
	GUID guid;
	//todo: remove hierarhi to GAMVisElement
	GAMObject* parent;
	
	ErroreLoger* loger;
	
	
	virtual void StartUpInit()
	{
		parent = 0;
		name = std::wstring(TEXT("GAMObject"));
		CoCreateGuid(&guid);
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
	GAMObject(/*LPDIRECT3DDEVICE9 TDDevice,*/ ErroreLoger* Tloger)
	{
		//DDevice = TDDevice;
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
	GAMObject(/*LPDIRECT3DDEVICE9 TDDevice,*/ GAMObject* Tparent, ErroreLoger* Tloger)
	{
		parent = Tparent;
		//DDevice = TDDevice;
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

	
	virtual GAMObject* Clone() = 0;

	
};

#endif