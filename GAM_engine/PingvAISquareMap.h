#pragma once

#ifndef H_PINGVAISQUAREMAP
#define H_PINGVAISQUAREMAP

#include <vector>
#include <sstream>
#include "GAM_base\base\GAMObject.h"
#include "GAM_base\base\VertexObject.h"

using namespace std;

//base on matrix
struct PingvMap
{
	//Todo: Need Destroy Map
	int** map;
	int row_count;
	int coll_count;
};
struct Point
{
	int x;
	int y;
	Point()
	{ x = -1; y = -1;}
	Point(int t_x, int t_y)
	{x = t_x; y = t_y;}
};

class MapSquare : public VertexObject
{
public:
	Point posOnMap;
	//ErroreLoger *tloger;
	MapSquare(LPDIRECT3DDEVICE9 TDDevice) : VertexObject(TDDevice)
	{
		InitDefaultMaterials();
		posOnMap = Point(0,0);
		loger = new ErroreLoger(_T("FUCK.txt"));
	}
	HRESULT ChangeIndexingMode(IndexingType TindexingMode)
	{
		
		loger->SendToLog(_T("Fuck"));
		indexing_type = TindexingMode;
		short Indeces[6];
		HRESULT hr = DDevice->CreateIndexBuffer(sizeof(short)*6,0,D3DFMT_INDEX16, D3DPOOL_DEFAULT, &index_bufer, NULL );
		if(FAILED(hr))
		{
			//if(loger)
			//{
				wstring number;
				wstringstream wstrstrmaa;
				wstrstrmaa << hr;
				wstrstrmaa >> number;
				loger->SendToLog(GetTypeStr()+GetName()+TEXT("CreateIndexBuffer: Line 147 in VertexObject.cpp ")+number);
			//}
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
		memcpy(IndexData, (void*)&Indeces, sizeof(Indeces));
		index_bufer->Unlock();

		return S_OK;
	}
};

class PingvAISquareMap : virtual public GAMObject
{
private:
	int m_width, m_height; //m_coll_count, m_row_count;
	D3DXVECTOR3 m_centralPose;
	//int **m_map;
	PingvMap m_map;
	vector<MapSquare*> m_square; //visible Squares
public:
	PingvAISquareMap(void);
	PingvAISquareMap(LPDIRECT3DDEVICE9 TDDevice, int t_width, int t_height, int t_coll_count, int t_row_count, D3DXVECTOR3 t_centralPose);
	virtual ~PingvAISquareMap(void);
	virtual void Draw();
	virtual GAMObject* Clone(); //Todo: need refine Clone Method in PingvAISqaureMap
	virtual std::wstring GetTypeStr()
	{return wstring(_T("PingvAISquareMap"));}
};

#endif
