#include "DXUT.h"
#include "Home.h"

//	���� ���� ������Ʈ ������ �Ÿ� ��� �Լ� 
float CUtil::CalcDist(CGameObj* pObj1, CGameObj* pObj2)
{
	D3DXVECTOR2 vLen = *pObj2->GetPos() - *pObj1->GetPos();

	return D3DXVec2Length(&vLen);
}
//	������Ʈ�� �������� �� �Ǵ� Ÿ�� ������Ʈ ��ǥ���� �Ÿ� ��� �Լ� (D3DXVECTOR2 ���)
float CUtil::CalcDist(CGameObj* pObj, const D3DXVECTOR2* pPos)
{
	D3DXVECTOR2 vLen = *pObj->GetPos() - *pPos;
	return D3DXVec2Length(&vLen);
}
//	�� �Ǵ� Ÿ�� ������Ʈ ������ �Ÿ� ��� �Լ� (D3DXVECTOR2 ���)
float CUtil::CalcDist(const D3DXVECTOR2* pPos1, const D3DXVECTOR2* pPos2)
{
	D3DXVECTOR2 vLen = *pPos1 - *pPos2;
	return D3DXVec2Length(&vLen);
}

bool CUtil::UIObject_Mouse_Collision(CGameObj* pObj, const D3DXVECTOR2 vPos)
{	// windef.h�� �ִ� RECT ����ü 3���� �����Ѵ�
	RECT intersect_rc, Rect1, Rect2;

	Rect1.left = (int)pObj->GetPos()->x;						// ���� �ϴ� ������
	Rect1.top = (int)pObj->GetPos()->y;							// ���� ��� ������
	Rect1.right = (int)Rect1.left + (int)pObj->GetImgSize()->x; // ���� �ϴ� ����
	Rect1.bottom = (int)pObj->GetPos()->y + (int)pObj->GetImgSize()->y; // ���� ��� ����

	Rect2.left = (int)vPos.x;						// ���� �ϴ� ������
	Rect2.top = (int)vPos.y;						// ���� ��� ������
	Rect2.right = (int)Rect2.left + 1;				// ���� �ϴ� ����
	Rect2.bottom = (int)Rect2.top + 1;				// ���� ��� ����
													
	if (int i = IntersectRect(&intersect_rc, &Rect1, &Rect2))	// ���� �밢�� ���̰� valid�ϴٸ�
		return true;
	else
		return false;
}

bool CUtil::Object_Mouse_Collision(CGameObj* pObj, const D3DXVECTOR2 vPos)
{	// windef.h�� �ִ� RECT ����ü 3���� �����Ѵ�
	RECT intersect_rc, Rect1, Rect2;

	Rect1.left = (int)pObj->GetPos()->x - (int)pObj->GetImgSize()->x * 0.5;
	Rect1.top = (int)pObj->GetPos()->y - (int)pObj->GetImgSize()->y * 1.0;
	Rect1.right = pObj->GetPos()->x + pObj->GetImgSize()->x * 0.5f;
	Rect1.bottom = (int)pObj->GetPos()->y;

	Rect2.left = (int)vPos.x;
	Rect2.top = (int)vPos.y;
	Rect2.right = (int)Rect2.left + 1;
	Rect2.bottom = (int)Rect2.top + 1;

	if (int i = IntersectRect(&intersect_rc, &Rect1, &Rect2))
		return true;
	else
		return false;
}

float CUtil::GetDirection(D3DXVECTOR2 *pPos1, D3DXVECTOR2 *pPos2)
{
	float fAngle = -D3DXToDegree(atan2(pPos1->x - pPos2->x, pPos1->y - pPos2->y));

	if (fAngle < 0)
		fAngle += 360;

	return  fAngle;
}

float CUtil::GetDirection(const D3DXVECTOR2 *pPos1, D3DXVECTOR2 *pPos2)
{
	float fAngle = -D3DXToDegree(atan2(pPos1->x - pPos2->x, pPos1->y - pPos2->y));

	if (fAngle < 0)
		fAngle += 360;

	return  fAngle;
}

D3DXVECTOR2 CUtil::GetDirectionVector(const D3DXVECTOR2* pPlayerPos, const D3DXVECTOR2* pTargetPos)
{
	D3DXVECTOR2 vNormalize;

	D3DXVECTOR2 vLen = *pTargetPos - *pPlayerPos;
	D3DXVec2Normalize(&vNormalize, &vLen);

	return vNormalize;
}