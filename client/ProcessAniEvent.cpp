#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;

void OnAniEvent(CAniObj* pAniObj, const SAniEventData& sData)//
{
	switch (sData.m_iType)//받아온 데이터의 상태에 따라 적절한 상태 불러옴
	{
	case eEvent_AttackEffect:
	{
		CGameObj* pEnemy = pAniObj->GetController()->GetEnemy();//적 오브젝트 불러옴
		CGameObj* pEffect = NULL;

		if (pEnemy == NULL)
			break;

		// 공격 이펙트 설정

		// 적 위치에 이펙트 생성
		if (sData.GetIntParam(0) == 0)
			pEffect = g_pGameObjMgr->Load(EGAMEOBJ_EFFECT, ETEAM_NENUTAL, sData.GetTextParam(0), L"AttackEffect", *pEnemy->GetPos(), 0, ERENDER_NORMAL, true);

		if (sData.GetIntParam(0) == 1)
			pEffect = g_pGameObjMgr->Load(EGAMEOBJ_BEGINEFFECT, ETEAM_NENUTAL, sData.GetTextParam(0), L"BeginAttackEffect", *pEnemy->GetPos(), 0, ERENDER_NORMAL, true);

		// 내 위치에 이펙트 생성
		if (sData.GetIntParam(0) == 2)
			pEffect = g_pGameObjMgr->Load(EGAMEOBJ_EFFECT, ETEAM_NENUTAL, sData.GetTextParam(0), L"BeginEffect", *pAniObj->GetPos(), 0, ERENDER_NORMAL, true);

		if (sData.GetIntParam(0) == 3)
			pEffect = g_pGameObjMgr->Load(EGAMEOBJ_BEGINEFFECT, ETEAM_NENUTAL, sData.GetTextParam(0), L"AffterEffect", *pAniObj->GetPos(), 0, ERENDER_NORMAL, true);

		// 데미지를 주는가 
		if (sData.GetIntParam(1) == 1)
			pEnemy->OnDamage(pAniObj->GetDamage(), pAniObj);


		// 적 위치에 고정되는가?
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