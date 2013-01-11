#ifndef H_BOUNDS
#define H_BOUNDS

#include <d3d9.h>
#include <d3dx9.h>
#include "..\math\Xmath.h"

using namespace XMath;

class Bounds
{
private:
	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
protected:
public:
	Bounds()
	{}
	Bounds(D3DXVECTOR3 Tmin, D3DXVECTOR3 Tmax)
	{
		min = Tmin;
		max = Tmax;
	}
	~Bounds()
	{}
	void SetBounds(D3DXVECTOR3 Tmin, D3DXVECTOR3 Tmax)
	{
		min = Tmin;
		max = Tmax;
	}
	double GetMaxX()
	{ return max.x; }
	double GetMaxY()
	{ return max.y; }
	double GetMaxZ()
	{ return max.z; }
	double GetMinX()
	{ return min.x; }
	double GetMinY()
	{ return min.y; }
	double GetMinZ()
	{ return min.z; }
	D3DXVECTOR3 GetCenter()
	{ return D3DXVECTOR3( (max.x + min.x) / 2, (max.y + min.y) / 2, (max.z + min.z) / 2); }
	D3DXVECTOR3 GetMaxCoord()
	{ return max; }
	D3DXVECTOR3 GetMinCoord()
	{ return min; }
	void SetTransformByMatrix(D3DXMATRIX transMatrix)
	{
		min = TransformVector3ByMatrix(transMatrix, min);
		max = TransformVector3ByMatrix(transMatrix, max);
	}
};

#endif
