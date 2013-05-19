//#include "GAMVisElemen.h"
//#include <d3d9.h>
//#include <d3dx9.h>
//#include <D3dx9math.h>
//#include <Vector>

//void GAMVisElement::SetPosition(D3DXVECTOR3 pos)
//{ 
//	vectorPosition = pos;	
//	D3DXMATRIX MatTemp;
//	D3DXMatrixIdentity(&MatTemp);
//	D3DXMatrixTranslation(&MatTemp, vectorPosition.x, vectorPosition.y, vectorPosition.z);
//	D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
//	RecalcMatrixGlobalOnly();
//	//RecalcMatrixGlobal();
//}
//void GAMVisElement::SetRotation(D3DXVECTOR3 angles)
//{ 
//	vectorRotation = angles; 
//	D3DXMATRIX MatTemp;
//	D3DXMatrixIdentity(&MatTemp);
//	D3DXMatrixRotationX(&MatTemp, vectorRotation.x);
//	D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
//	D3DXMatrixRotationY(&MatTemp, vectorRotation.y);
//	D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
//	D3DXMatrixRotationZ(&MatTemp, vectorRotation.z);
//	D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
//	//D3DXMatrixMultiply(&matrixLocalTransform, &matrixLocalTransform, &MatTemp);
//	RecalcMatrixGlobalOnly();
//}
