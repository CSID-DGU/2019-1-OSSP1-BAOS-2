#include "DXUT.h"
#include "Home.h"

extern GameDataMgr * g_pGameDataMgr;
extern CGameObjMgr* g_pGameObjMgr;
extern CGameTileMgr* g_pGameTileMgr;

CTower::CTower(void)//건축물 클래스
{
}


CTower::~CTower(void)
{
}

void CTower::Load(wstring wFile)//wFile load
{
	__super::Load(wFile);

	m_pController = new CTowerAI(this);//건축물 제어하는 컨트롤러 생성

	//건축물 체력 설정
	CGameObj* pHealth = g_pGameObjMgr->Load(EGAMEOBJ_HEALTH, ETEAM_NENUTAL, L"Creature_Health", L"Health", D3DXVECTOR2(0, 0), 0, ERENDER_NORMAL, true);
	((CHealth*)pHealth)->SetPlayer(this);

	CUI* pMiniDot = NULL;//미니맵에 구현할 미니Dot 생성

	if (m_iTeam == ETEAM_FRIEND)//팀이 아군일 경우
		pMiniDot = g_pGameObjMgr->UILoad(UI_MINIDOT, L"GreenDot", L"GreenDot", D3DXVECTOR2(0, 0), false, true);//Dot를 초록색으로 설정

	if (m_iTeam == ETEAM_ENEMY)//팀이 적군일 경우
		pMiniDot = g_pGameObjMgr->UILoad(UI_MINIDOT, L"RedDot", L"RedDot", D3DXVECTOR2(0, 0), false, true);//Dot를 빨간색으로 설정


	if (pMiniDot != NULL)//미니Dot가 있을 경우
	{
		pMiniDot->SetObj(this);//오브젝트 설정
		pMiniDot->SetScl(D3DXVECTOR2(-2, -2));//오브젝트 스케일 설정
	}

	OnChangeAni(AT_NORMAL);

	for (int Row = (int)m_vPos.x - 1; Row <= m_vPos.x + 1; Row++)//건축물 주위 칸만큼 반복
		for (int Col = (int)m_vPos.y - 1; Col <= m_vPos.y; Col++)//
		{
			D3DXVECTOR2 vNeighborNode = D3DXVECTOR2((float)Row, (float)Col);
			STileData* pData = g_pGameTileMgr->GetTileData(vNeighborNode);//주위의 타일 Data 설정
			if (pData == nullptr)
				continue;

			pData->m_iTileType = 0;//TileType 설정
		}

	SetPos(g_pGameTileMgr->FindCenterPos(m_vPos));
}

void CTower::OnDamage(int iDamage, CGameObj* pGameObj)//데미지를 입었을 때
{
	m_iHealth -= iDamage;//체력에서 데미지 차감

	if (m_iHealth <= 0)//체력이 0일 경우
	{
		if (m_iAniCategory != AT_DIE)//상태 Die로 변경
			OnChangeAni(AT_DIE);
	}
}

void CTower::OnFrameMove(float fElapsedTime)//Frame 갱신
{
	__super::OnFrameMove(fElapsedTime);
}