#include "PingvAISquareMap.h"

PingvAISquareMap::PingvAISquareMap(void)
{
}

PingvAISquareMap::~PingvAISquareMap(void)
{
}

PingvAISquareMap::PingvAISquareMap(LPDIRECT3DDEVICE9 TDDevice, int t_width, int t_height, int t_coll_count, int t_row_count, D3DXVECTOR3 t_centralPose)
{
	m_width = t_width, m_height = t_width, m_map.coll_count = t_coll_count, m_map.row_count = t_row_count;
	m_centralPose = t_centralPose;
	m_map.map = new int*[m_map.row_count];
	for(int i = 0; i < m_map.row_count; i++)
	{
		m_map.map[i] = new int[m_map.coll_count];
	}
	m_map.map[3][4] = 99;
	m_map.map[5][7] = 99;
	for(int i = 0; i < m_map.coll_count; i++)
	{
		for(int j = 0; j < m_map.row_count; j++)
		{
			m_square.push_back(new MapSquare(TDDevice));
			m_square[m_square.size()-1]->posOnMap = Point(i, j);
			m_square[m_square.size()-1]->LoadTexture(TEXT("Res\\Textures\\white.png"));
			m_square[m_square.size()-1]->SetRenderType(VertexObject::RenderType::Greed);
			m_square[m_square.size()-1]->CreatePlane(
				D3DXVECTOR3(t_centralPose.x + i, t_centralPose.y, t_centralPose.z + j), 
				D3DXVECTOR3(t_centralPose.x+(i+t_width), t_centralPose.y, t_centralPose.z+(j+t_height)), 
				VertexObject::IndexingType::Square);
			//m_square[m_square.size()-1]->ChangeIndexingMode(VertexObject::IndexingType::Triangle);
			//m_square[m_square.size()-1]->SetRenderType(VertexObject::RenderType::Plane);
		}
	}
	//Undone: Need create Squares
	//Vector<VertexObject> m_square; //visible Squares
}

void PingvAISquareMap::Draw()
{
	for(int i = 0; i<m_square.size(); i++)
	{
		//Todo: need fix this
		//if(m_map.map[m_square[i]->posOnMap.y, m_square[i]->posOnMap.x] > 0 
		//	&& m_square[i]->GetIndexingType() == VertexObject::IndexingType::Square)
		//{
		//	//if(loger)
		//	//{
		//		wstring tmp(_T(""));
		//		wstring number;
		//		wstringstream wstrstrm;
		//		wstrstrm << m_map.map[m_square[i]->posOnMap.x];
		//		wstrstrm >> number;
		//		tmp+=number;
		//		wstrstrm << m_map.map[m_square[i]->posOnMap.y];
		//		wstrstrm >> number;
		//		tmp+=number;
		//		//tmp
		//		//loger->SendToLog(tmp);
		//	//}
		//	m_square[i]->ChangeRenderMode(VertexObject::RenderType::Plane);
		//	m_square[i]->ChangeIndexingMode(VertexObject::IndexingType::Triangle);
		//}
		//else if(m_map.map[m_square[i]->posOnMap.y, m_square[i]->posOnMap.x] == 0 
		//	&& m_square[i]->GetIndexingType() == VertexObject::IndexingType::Triangle)
		//{
		//	m_square[i]->ChangeRenderMode(VertexObject::RenderType::Greed);
		//	m_square[i]->ChangeIndexingMode(VertexObject::IndexingType::Square);
		//}
		m_square[i]->Draw();
	}
	//Todo: Need draw Squares
}

GAMObject* PingvAISquareMap::Clone()
{
	//Todo: Need Refine
	return dynamic_cast<GAMObject*>(this);
}
