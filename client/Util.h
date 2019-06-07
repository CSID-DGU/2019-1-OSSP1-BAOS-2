#pragma once

class CGameObj;

namespace CUtil
{
	float CalcDist(CGameObj* pObj1, CGameObj* pObj2);
	float CalcDist(CGameObj* pObj, const D3DXVECTOR2* vPos);
	float CalcDist(const D3DXVECTOR2* pPos1, const D3DXVECTOR2* pPos2);

	bool UIObject_Mouse_Collision(CGameObj* pObj, const D3DXVECTOR2 vPos);
	bool Object_Mouse_Collision(CGameObj* pObj, const D3DXVECTOR2 vPos);

	float GetDirection(D3DXVECTOR2* pPos1, D3DXVECTOR2 * pPos2);
	float GetDirection(const D3DXVECTOR2* pPos1, D3DXVECTOR2 * pPos2);

	D3DXVECTOR2 GetDirectionVector(const D3DXVECTOR2 * pPlayerPos, const D3DXVECTOR2* pTargetPos);
};
