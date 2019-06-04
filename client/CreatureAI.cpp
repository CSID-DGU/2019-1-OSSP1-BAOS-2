#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;
extern CGameTileMgr* g_pGameTileMgr;
extern CGameObjMgr* g_pGameObjMgr;


CCreatureAI::CCreatureAI(CAniObj* pGameObj) ://크리쳐 생성자 선언 및 초기화
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

void CCreatureAI::OnFrameMove(float fElapsedTime)//프레임 갱신
{
	OnPriorityEnemy();					//우선순위 적 설정
	OnUpdateState(fElapsedTime);		//상태 업데이트
	OnChangeReserveState();				//예약된 상태로 전환
}

void CCreatureAI::OnEndAni(int iAniCategory)//애니 종료
{
	if (iAniCategory == AT_DIE)//죽은 상태일 경우
	{
		m_pGameObj->Destroy();//오브젝트 제거
		return;
	}

	pGameObj()->OnChangeAni(AT_NORMAL);//게임 오브젝트에서 NORMAL사앹로 애니 전환
}

void CCreatureAI::OnChangeAni(int iAniCategory)//애니 전환
{
	OnChangeState(iAniCategory);
}

void CCreatureAI::OnPriorityEnemy()//우선순위 적 설정
{
	//범위 내에 있는적으로 타겟을 잡고 적을 설정한다.
	SetEnemy(g_pGameObjMgr->OnFindTarget(pGameObj(), g_pGameObjMgr->m_setPlayObj, AI_SCOPE));
	if (m_pEnemy == NULL)
	{
		//pEnemy = m_pGameObj->GetDamager();
	}
}

void CCreatureAI::OnUpdateNormal(DWORD dwObj, float fElapsedTime)
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;//컨트롤러 AI
	CAniObj* pObj = pController->pGameObj();

	D3DXVECTOR2 vTargetPos = g_pGameTileMgr->FindIndexCenter(*pObj->GetGoalPos());//목표 위치를 받아와서 타겟 위치 받아옴
	D3DXVECTOR2 vPlayerPos = *pObj->GetPos();//플레이어 위치 받아옴

	//플레이어 위치의 타일 index의 데이터를 가져온다.
	STileData* pData = g_pGameTileMgr->GetTileData(g_pGameTileMgr->FindTileIndex(vPlayerPos));
	if (pData != NULL)//데이터가 있을경우
		pData->m_iTileType = 0;//타일 타입 0으로

	if (pObj->GetTeam() == ETEAM_FRIEND)//아군 팀일 경우
		pObj->SetGoalPos(*g_pGameObjMgr->pEnemyTower->GetPos());//적타워 위치로 목표 위치 설정
	else                                //적군 팀일 경우
		pObj->SetGoalPos(*g_pGameObjMgr->pFriendTower->GetPos());//아군 타워 위치로 목표 설정

	pController->m_vPath = NULLVECTOR2;

	//타겟 위치와 플레이어 위치 계산, 일정 거리(5)이상인 경우
	if (CUtil::CalcDist(&vPlayerPos, &vTargetPos) > 5 && *pObj->GetGoalPos() != NULLVECTOR2)
	{
		pObj->OnChangeAni(AT_MOVE);//Ani 상태를 MOVE로 설정
		pData->m_iTileType = 1;//타일타입 1로 지정
	}
}

void CCreatureAI::OnUpdateMove(DWORD dwObj, float fElapsedTime)//실시간으로 이동 업데이트
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;
	CAniObj* pObj = pController->pGameObj();

	D3DXVECTOR2 vTargetPos = g_pGameTileMgr->FindIndexCenter(*pObj->GetGoalPos());//타겟 위치 
	D3DXVECTOR2 vPlayerPos = *pObj->GetPos();//플레이어 위치

	D3DXVECTOR2 vPathPos = g_pGameTileMgr->FindCenterPos(pController->m_vPath);//경로 벡터

	if (pController->GetEnemy() != NULL)//적이 있는 경우
	{
		if (CUtil::CalcDist(pObj, pController->GetEnemy()) < pObj->GetScope())//오브젝트와 적의 위치가 범위 내에 있는경우
			pObj->OnChangeAni(AT_ATTACK);//공격 상태로 전환
		else
			pObj->SetGoalPos(*pController->GetEnemy()->GetPos());//목표 위치 재설정
	}

	//컨트롤러의 경로벡터가 없고 플레이어 위치와 경로 위치가 기준 이하일 경우, 
	if (pController->m_vPath == NULLVECTOR2 || CUtil::CalcDist(&vPlayerPos, &vPathPos) < 5)
		pController->FindNode();//컨트롤러 
	else
	{
		pObj->SetDirectionVector(pController->FollowPath());//방향벡터 설정
		D3DXVECTOR2 vPos = *pObj->GetPos();//위치 받아오기

		D3DXVECTOR2 vMoveVel = *pObj->GetDirectionVector() * (pObj->GetSpeed() * fElapsedTime);//이동속도

		vPos += vMoveVel;//위치에서 이동속도 더해주고
		pObj->SetPos(vPos);//위치 재설정
	}


	if (CUtil::CalcDist(&vPlayerPos, &vTargetPos) < 5 || *pObj->GetGoalPos() == NULLVECTOR2)
	{
		pObj->OnChangeAni(AT_NORMAL);
	}
}

void CCreatureAI::OnUpdateAttack(DWORD dwObj, float fElapsedTime)//공격상태 업데이트
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;
	CAniObj* pObj = pController->pGameObj();

	if (pController->GetEnemy() == NULL)//불러올 적이 없는 경우
	{
		pController->OnChangeAni(AT_NORMAL);//NORMAL 상태로 전환
		return;
	}

	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex(*pObj->GetPos());//타일매니저에서 타일 위치 가져와 player index 설정
	D3DXVECTOR2 vTargetIndex = g_pGameTileMgr->FindTileIndex(*pController->GetEnemy()->GetPos());//타일매니저에서 적의 위치 받아와 target index 설정

	STileData* pData = g_pGameTileMgr->GetTileData(vPlayerIndex);//플레이어의 타일 데이터 설정
	pData->m_iTileType = 0;

	pController->m_vPath = NULLVECTOR2;

	if (vTargetIndex != vPlayerIndex)//플레이어와 타겟이 다를경우
	{
		int iAngle = (int)(CUtil::GetDirection(&vPlayerIndex, &vTargetIndex));//플레이어 위치와 타겟 위치로 방향 불러옴
		pObj->SetDirection((int)(iAngle / 45));//방향 설정
	}

	if (CUtil::CalcDist(pObj, pController->GetEnemy()) > pObj->GetScope())
	{
		//오브젝트와 적의 거리가 기준범위보다 클경우
		pObj->OnChangeAni(AT_NORMAL);//상태 NORMAL로 변경
		pData->m_iTileType = 1;
	}
}


void CCreatureAI::OnBeginDie(DWORD dwObj)//상태가 죽었을 경우
{
	CCreatureAI* pController = (CCreatureAI*)dwObj;//dwObj크리처 정보로 할당
	CAniObj* pObj = pController->pGameObj();

	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex(*pObj->GetPos());

	STileData* pData = g_pGameTileMgr->GetTileData(vPlayerIndex);
	pData->m_iTileType = 1;
}