#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;
extern CGameTileMgr* g_pGameTileMgr;
extern CGameObjMgr* g_pGameObjMgr;


CCreatureAI::CCreatureAI(CAniObj* pGameObj) :
	CGameObjController(pGameObj)
{
	AddState(AT_NORMAL, SFSMState((DWORD)this, NULL, OnUpdateNormal, NULL));
	AddState(AT_MOVE, SFSMState((DWORD)this, NULL, OnUpdateMove, NULL));
	AddState(AT_ATTACK, SFSMState((DWORD)this, NULL, OnUpdateAttack, NULL));
	AddState(AT_DIE, SFSMState((DWORD)this, OnBeginDie, NULL, NULL));
}


CCreatureAI::~CCreatureAI(void)
{
}

void CCreatureAI::OnFrameMove(float fElapsedTime)
{
	OnPriorityEnemy();
	OnUpdateState(fElapsedTime);
	OnChangeReserveState();
}

void CCreatureAI::OnEndAni(int iAniCategory)
{
	if (iAniCategory == AT_DIE)
	{
		m_pGameObj->Destroy();
		return;
	}

	pGameObj()->OnChangeAni(AT_NORMAL);
}

void CCreatureAI::OnChangeAni(int iAniCategory)
{
	OnChangeState(iAniCategory);
}

void CCreatureAI::OnPriorityEnemy()
{
	SetEnemy(g_pGameObjMgr->OnFindTarget(pGameObj(), g_pGameObjMgr->m_setPlayObj, AI_SCOPE));
	if (m_pEnemy == NULL)
	{
		//pEnemy = m_pGameObj->GetDamager();
	}
}

void CCreatureAI::OnUpdateNormal(DWORD dwObj, float fElapsedTime)
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;
	CAniObj* pObj = pController->pGameObj();

	D3DXVECTOR2 vTargetPos = g_pGameTileMgr->FindIndexCenter(*pObj->GetGoalPos());
	D3DXVECTOR2 vPlayerPos = *pObj->GetPos();

	STileData *pData = g_pGameTileMgr->GetTileData(g_pGameTileMgr->FindTileIndex(vPlayerPos));
	if (pData != NULL)
		pData->m_iTileType = 0;

	if (pObj->GetTeam() == ETEAM_FRIEND)
		pObj->SetGoalPos(*g_pGameObjMgr->pEnemyTower->GetPos());
	else
		pObj->SetGoalPos(*g_pGameObjMgr->pFriendTower->GetPos());

	pController->m_vPath = NULLVECTOR2;

	if (CUtil::CalcDist(&vPlayerPos, &vTargetPos) > 5 && *pObj->GetGoalPos() != NULLVECTOR2)
	{
		pObj->OnChangeAni(AT_MOVE);
		pData->m_iTileType = 1;
	}
}

void CCreatureAI::OnUpdateMove(DWORD dwObj, float fElapsedTime)
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;
	CAniObj* pObj = pController->pGameObj();

	D3DXVECTOR2 vTargetPos = g_pGameTileMgr->FindIndexCenter(*pObj->GetGoalPos());
	D3DXVECTOR2 vPlayerPos = *pObj->GetPos();

	D3DXVECTOR2 vPathPos = g_pGameTileMgr->FindCenterPos(pController->m_vPath);

	if (pController->GetEnemy() != NULL)
	{
		if (CUtil::CalcDist(pObj, pController->GetEnemy()) < pObj->GetScope())
			pObj->OnChangeAni(AT_ATTACK);
		else
			pObj->SetGoalPos(*pController->GetEnemy()->GetPos());
	}

	if (pController->m_vPath == NULLVECTOR2 || CUtil::CalcDist(&vPlayerPos, &vPathPos) < 5)
		pController->FindNode();
	else
	{
		pObj->SetDirectionVector(pController->FollowPath());
		D3DXVECTOR2 vPos = *pObj->GetPos();

		D3DXVECTOR2 vMoveVel = *pObj->GetDirectionVector() * (pObj->GetSpeed() * fElapsedTime);

		vPos += vMoveVel;
		pObj->SetPos(vPos);
	}


	if (CUtil::CalcDist(&vPlayerPos, &vTargetPos) < 5 || *pObj->GetGoalPos() == NULLVECTOR2)
	{
		pObj->OnChangeAni(AT_NORMAL);
	}
}

void CCreatureAI::OnUpdateAttack(DWORD dwObj, float fElapsedTime)
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;
	CAniObj* pObj = pController->pGameObj();

	if (pController->GetEnemy() == NULL)
	{
		pController->OnChangeAni(AT_NORMAL);
		return;
	}

	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex(*pObj->GetPos());
	D3DXVECTOR2 vTargetIndex = g_pGameTileMgr->FindTileIndex(*pController->GetEnemy()->GetPos());

	STileData *pData = g_pGameTileMgr->GetTileData(vPlayerIndex);
	pData->m_iTileType = 0;

	pController->m_vPath = NULLVECTOR2;

	if (vTargetIndex != vPlayerIndex)
	{
		int iAngle = (int)(CUtil::GetDirection(&vPlayerIndex, &vTargetIndex));
		pObj->SetDirection((int)(iAngle / 45));
	}

	if (CUtil::CalcDist(pObj, pController->GetEnemy()) > pObj->GetScope())
	{
		pObj->OnChangeAni(AT_NORMAL);
		pData->m_iTileType = 1;
	}
}


void CCreatureAI::OnBeginDie(DWORD dwObj)
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;
	CAniObj* pObj = pController->pGameObj();

	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex(*pObj->GetPos());

	STileData *pData = g_pGameTileMgr->GetTileData(vPlayerIndex);
	pData->m_iTileType = 1;
}