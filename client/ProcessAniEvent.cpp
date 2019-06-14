#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;

void OnAniEvent(CAniObj* pAniObj, const SAniEventData& sData)//
{
	switch (sData.m_iType)//�޾ƿ� �������� ���¿� ���� ������ ���� �ҷ���
	{
	case eEvent_AttackEffect:
	{
		CGameObj* pEnemy = pAniObj->GetController()->GetEnemy();//�� ������Ʈ �ҷ���
		CGameObj* pEffect = NULL;

		if (pEnemy == NULL)
			break;

		// ���� ����Ʈ ����

		// �� ��ġ�� ����Ʈ ����
		if (sData.GetIntParam(0) == 0)
			pEffect = g_pGameObjMgr->Load(EGAMEOBJ_EFFECT, ETEAM_NENUTAL, sData.GetTextParam(0), L"AttackEffect", *pEnemy->GetPos(), 0, ERENDER_NORMAL, true);

		if (sData.GetIntParam(0) == 1)
			pEffect = g_pGameObjMgr->Load(EGAMEOBJ_BEGINEFFECT, ETEAM_NENUTAL, sData.GetTextParam(0), L"BeginAttackEffect", *pEnemy->GetPos(), 0, ERENDER_NORMAL, true);

		// �� ��ġ�� ����Ʈ ����
		if (sData.GetIntParam(0) == 2)
			pEffect = g_pGameObjMgr->Load(EGAMEOBJ_EFFECT, ETEAM_NENUTAL, sData.GetTextParam(0), L"BeginEffect", *pAniObj->GetPos(), 0, ERENDER_NORMAL, true);

		if (sData.GetIntParam(0) == 3)
			pEffect = g_pGameObjMgr->Load(EGAMEOBJ_BEGINEFFECT, ETEAM_NENUTAL, sData.GetTextParam(0), L"AffterEffect", *pAniObj->GetPos(), 0, ERENDER_NORMAL, true);

		// �������� �ִ°� 
		if (sData.GetIntParam(1) == 1)
			pEnemy->OnDamage(pAniObj->GetDamage(), pAniObj);


		// �� ��ġ�� �����Ǵ°�?
		if (sData.GetIntParam(2) == 1)
			((CEffect*)pEffect)->SetTarget(pEnemy);
	}
	break;

	case eEvent_ChangeState:
	{

	}
	case eEvent_Die:
	{

	}

	}
}