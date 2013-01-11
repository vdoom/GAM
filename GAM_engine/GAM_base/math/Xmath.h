
#ifndef H_XMATH_LIB
#define H_XMATH_LIB
#include <math.h>
#include <intsafe.h>
namespace XMath
{
//! Matemtical Library for game development

static double sqr (double a)
{
	return a*a;
}

//! length between two vectors
/*!
	This Function need when you wont to calculate a length betwen two vectors or dots
	
	\param xa is double x-dimension valuea of first vector
	\param xb is double x-dimension valuea of second vector
	\param ya is double y-dimension valuea of first vector
	\param yb is double y-dimension valuea of second vector
	\return double value of length betwen two vectors
	\sa PLength	
*/

static double PLength(double xa,double xb,double ya,double yb)
{
	return sqrt(sqr(xa-xb)+sqr(ya-yb));
}

static double* MultMat(double** a, double* b, int n)
{
	double* c = new double[n]; // POSIBLE MEMMORE LEAK
	double sum =0;
	for(int i=0; i<5;i++)
	{
		sum=0;
		for(int j=0; j<n; j++)sum+=a[j][i]*b[j];
		c[i]=sum;
	}
	return c;
}

static double FAngle3(double a, double b, double c)
{
	double angle;
	angle = (sqr(a)+sqr(b)-sqr(c))/(2*a*b);
	return acos(angle);
}
static double ToDegree(double radian)
{
	return radian*(180.0f / D3DX_PI);
}
static double ToRadian(double degree)
{
	return degree*(D3DX_PI / 180.0f);
}
static int DigCount(int j)
{
	int i = 0;
	div_t div_result;
	
	if(j)
	{
		do
		{
			i++;
			div_result=div(j,pow((double)10,(double)i));
		}while(div_result.quot!=0);
		return i;
	}
	else return 0;
}
static int GetDig(int d, int i)
{
	div_t div_result;

	if(DigCount(d)>=i && i!=0)
	{
		div_result=div(d%(int)pow((double)10,(double)i),pow((double)10,(double)i-1));
		return div_result.quot;
	}
	else return -1;
}

static D3DXVECTOR3 RotDotY(D3DXVECTOR3 Dot, D3DXVECTOR3 CntRot, double Angle )
{
	D3DXVECTOR3 tmp;
	tmp.x = CntRot.x+(Dot.x-CntRot.x)*cos(Angle)-(Dot.z-CntRot.z)*sin(Angle);
	tmp.z = CntRot.z+(Dot.x-CntRot.x)*sin(Angle)+(Dot.z-CntRot.z)*cos(Angle);
	tmp.y = Dot.y;
	return tmp;
}

static D3DXVECTOR3 RotDotX(D3DXVECTOR3 Dot, D3DXVECTOR3 CntRot, double Angle )
{
	D3DXVECTOR3 tmp;
	tmp.y = CntRot.y+(Dot.y-CntRot.y)*cos(Angle)-(Dot.z-CntRot.z)*sin(Angle);
	tmp.z = CntRot.z+(Dot.y-CntRot.y)*sin(Angle)+(Dot.z-CntRot.z)*cos(Angle);
	tmp.x = Dot.x;
	return tmp;
}

static D3DXVECTOR3 RotDotZ(D3DXVECTOR3 Dot, D3DXVECTOR3 CntRot, double Angle )
{
	D3DXVECTOR3 tmp;
	tmp.x = CntRot.x+(Dot.x-CntRot.x)*cos(Angle)-(Dot.y-CntRot.y)*sin(Angle);
	tmp.y = CntRot.y+(Dot.x-CntRot.x)*sin(Angle)+(Dot.y-CntRot.y)*cos(Angle);
	tmp.z = Dot.z;
	return tmp;
}

static D3DXVECTOR3 TransformVector3ByMatrix(D3DXMATRIX transMat, D3DXVECTOR3 vectorForTransform)
{
	double *tmp = new double [4];
	tmp[0] = vectorForTransform.x;
	tmp[1] = vectorForTransform.y;
	tmp[2] = vectorForTransform.z;
	tmp[3] = 0;

	double** mat = new double*[4]; 
	for(int i=0; i<4; i++) mat[i] = new double[4];
	
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			mat[i][j] = transMat.m[i][j];
		}
	}
	
	double* tmp2 = MultMat(mat, tmp, 4);

	D3DXVECTOR3 result = D3DXVECTOR3(tmp2[0], tmp2[1], tmp2[2]);
	delete [] tmp;
	//delete [] tmp2; // POSIBLE MEMMORE LEAK
	for(int i=0; i<4; i++) delete [] mat[i];
	delete [] mat;

	return result;
}

static char* IntToStr(int dig)//48-57
{
	char* tmp;
	if(DigCount(dig))
	{
		tmp = new char[DigCount(dig)+1];
		char* c = new char[1];
		for(int i=1; i<=DigCount(dig); i++)
		{
			LongToChar(GetDig(dig, i)+48, c);
			tmp[DigCount(dig)-i] = *c;//(char)(48+i);// *c;
		}
		LongToChar(0, c);
		tmp[DigCount(dig)]=(char)0;//*c;
		return tmp;
	}
	return 0;
}

static wchar_t* IntToStrW(int dig)//48-57
{
	char* tmp;
	wchar_t* ret;
	if(DigCount(dig))
	{
		tmp = new char[DigCount(dig)+1];
		char* c = new char[1];
		for(int i=1; i<=DigCount(dig); i++)
		{
			LongToChar(GetDig(dig, i)+48, c);
			tmp[DigCount(dig)-i] = *c;//(char)(48+i);// *c;
		}
		LongToChar(0, c);
		tmp[DigCount(dig)]=(char)0;//*c;

		size_t origsize = strlen(tmp) + 1;
		const size_t newsize = 100;
		size_t convertedChars = 0;
		ret = new wchar_t[newsize];
	    mbstowcs_s(&convertedChars, ret, origsize, tmp, _TRUNCATE);

		return ret;
	}
	return 0;
}

static wchar_t* wchar_tINIT(wchar_t* ini)
{
	ini[0]=0;
	return ini;
}
static wchar_t* CharToWchar_t(char* Tchars)
{
	size_t origsize = strlen(Tchars) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t* ret = new wchar_t[newsize];
	mbstowcs_s(&convertedChars, ret, origsize, Tchars, _TRUNCATE);
	return ret;
}

}
#endif
