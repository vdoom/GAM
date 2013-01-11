class CXFrustum;

class CXFrustum
{
private:
protected:
	D3DXPLANE m_Planes[6];
public:
	CXFrustum(LPDIRECT3DDEVICE9 pDevice);
	bool TestPoint(FLOAT XPOS, FLOAT YPOS, FLOAT ZPOS);
	bool TestCube(float XCentre, float YCentre, float ZCentre, float Size);
	bool TestRectangle(float XCentre, float YCentre, float ZCentre, float XSize, float YSize, float ZSize);
	bool TestSphere(float XCentre, float YCentre, float ZCentre, float Radius);
	bool TestMesh(LPD3DXBASEMESH pMesh);
};

CXFrustum::CXFrustum(LPDIRECT3DDEVICE9 pDevice)
{
	D3DXMATRIX Matrix, ViewMatrix, ProjectionMatrix;

	pDevice->GetTransform(D3DTS_VIEW, &ViewMatrix);
	pDevice->GetTransform(D3DTS_PROJECTION, &ProjectionMatrix);
	D3DXMatrixMultiply(&Matrix, &ViewMatrix, &ProjectionMatrix);

	m_Planes[0].a = Matrix._14 + Matrix._13;
	m_Planes[0].b = Matrix._24 + Matrix._23;
	m_Planes[0].c = Matrix._34 + Matrix._33;
	m_Planes[0].d = Matrix._44 + Matrix._43;
	D3DXPlaneNormalize(&m_Planes[0], &m_Planes[0]);

	m_Planes[1].a = Matrix._14 - Matrix._13;
	m_Planes[1].b = Matrix._24 - Matrix._23;
	m_Planes[1].c = Matrix._34 - Matrix._33;
	m_Planes[1].d = Matrix._44 - Matrix._43;
	D3DXPlaneNormalize(&m_Planes[1], &m_Planes[1]);

	m_Planes[2].a = Matrix._14 + Matrix._11;
	m_Planes[2].b = Matrix._24 + Matrix._21;
	m_Planes[2].c = Matrix._34 + Matrix._31;
	m_Planes[2].d = Matrix._44 + Matrix._41;
	D3DXPlaneNormalize(&m_Planes[2], &m_Planes[2]);

	m_Planes[3].a = Matrix._14 - Matrix._11;
	m_Planes[3].b = Matrix._24 - Matrix._21;
	m_Planes[3].c = Matrix._34 - Matrix._31;
	m_Planes[3].d = Matrix._44 - Matrix._41;
	D3DXPlaneNormalize(&m_Planes[3], &m_Planes[3]);

	m_Planes[4].a = Matrix._14 - Matrix._12;
	m_Planes[4].b = Matrix._24 - Matrix._22;
	m_Planes[4].c = Matrix._34 - Matrix._32;
	m_Planes[4].d = Matrix._44 - Matrix._42;
	D3DXPlaneNormalize(&m_Planes[4], &m_Planes[4]);
		
	m_Planes[5].a = Matrix._14 + Matrix._12;
	m_Planes[5].b = Matrix._24 + Matrix._22;
	m_Planes[5].c = Matrix._34 + Matrix._32;
	m_Planes[5].d = Matrix._44 + Matrix._42;
	D3DXPlaneNormalize(&m_Planes[5], &m_Planes[5]);
}

bool CXFrustum::TestPoint(FLOAT XPOS, FLOAT YPOS, FLOAT ZPOS)
{
	for(short Counter = 0; Counter < 6; Counter++)
	{
		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XPOS, YPOS, ZPOS)) < 0.0f)
			return false;
	}

	return true;
}

bool CXFrustum::TestCube(float XCentre, float YCentre, float ZCentre, float Size)
{
	for(short Counter = 0; Counter < 6; Counter++)
	{
		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre - Size, YCentre - Size, ZCentre - Size)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre + Size, YCentre - Size, ZCentre - Size)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre - Size, YCentre + Size, ZCentre - Size)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre + Size, YCentre + Size, ZCentre - Size)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre - Size, YCentre - Size, ZCentre + Size)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre + Size, YCentre - Size, ZCentre + Size)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre - Size, YCentre + Size, ZCentre + Size)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre + Size, YCentre + Size, ZCentre + Size)) >= 0.0f)
			continue;

		return false;
	}

	return true;
}

bool CXFrustum::TestRectangle(float XCentre, float YCentre, float ZCentre, float XSize, float YSize, float ZSize)
{
	for(short Counter = 0; Counter < 6; Counter++)
	{
		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre - XSize, YCentre - YSize, ZCentre - ZSize)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre + XSize, YCentre - YSize, ZCentre - ZSize)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre - XSize, YCentre + YSize, ZCentre - ZSize)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre + XSize, YCentre + YSize, ZCentre - ZSize)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre - XSize, YCentre - YSize, ZCentre + ZSize)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre + XSize, YCentre - YSize, ZCentre + ZSize)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre - XSize, YCentre + YSize, ZCentre + ZSize)) >= 0.0f)
			continue;

		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre + XSize, YCentre + YSize, ZCentre + ZSize)) >= 0.0f)
			continue;

		return false;
	}

	return true;
}

bool CXFrustum::TestSphere(float XCentre, float YCentre, float ZCentre, float Radius)
{
	for(short Counter = 0; Counter < 6; Counter++)
	{
		if(D3DXPlaneDotCoord(&m_Planes[Counter], &D3DXVECTOR3(XCentre, YCentre, ZCentre)) < -Radius)
			return false;
	}

	return true;
}

bool CXFrustum::TestMesh(LPD3DXBASEMESH pMesh)
{
	if(pMesh)
	{
		DWORD NumVertices = pMesh->GetNumVertices();
		DWORD FVF = pMesh->GetFVF();
		UINT FVFSize = D3DXGetFVFVertexSize(FVF);
		LPVOID ppData = NULL;

		pMesh->LockVertexBuffer(D3DLOCK_READONLY, &ppData);

		if(ppData)
		{
			D3DXVECTOR3 Centre(0,0,0);
			FLOAT Radius = 0;

			D3DXComputeBoundingSphere((D3DXVECTOR3*)ppData, NumVertices, FVFSize, &Centre, &Radius);

			if(TestSphere(Centre.x, Centre.y, Centre.z, Radius))
			{
				pMesh->UnlockVertexBuffer();
				return true;
			}
		}

		pMesh->UnlockVertexBuffer();
	}

	return false;
}