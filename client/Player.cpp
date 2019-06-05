#include "DXUT.h"
#include "Home.h"

extern CCamera* g_pCamera;
extern CMouse* g_pMouse;
extern CGameTileMgr* g_pGameTileMgr;
extern CGameObjMgr* g_pGameObjMgr;

CPlayer::CPlayer(void) :
	m_fTime(0)//플레이어 생성
{
	g_pCamera->SetCameraObj(this);//카메라 오브젝트 플레이어로 설정
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::Load(wstring wFile)
{
	__super::Load(wFile);//상속한 클래스 로드

	m_pController = new CEricController(this);//플레이어 컨트롤러 생성

	SetPos(g_pGameTileMgr->FindCenterPos(m_vPos));//타일매니저로부터 위치 받아와 위치 설정
	g_pCamera->SetCameraPos(*this->GetPos());//카메라 위치 설정

	OnChangeAni(AT_NORMAL);//애니 상태 변경

	//헬스 오브젝트 설정
	CGameObj* pHealth = g_pGameObjMgr->Load(EGAMEOBJ_HEALTH, ETEAM_NENUTAL, L"Creature_Health", L"Health", D3DXVECTOR2(0, 0), 0, ERENDER_NORMAL, true);
	((CHealth*)pHealth)->SetPlayer(this);

	CUI* pMiniDot = NULL;//플레이어가 미니맵에 보이게 Dot 생성

	if (m_iTeam == ETEAM_FRIEND)//아군 팀이면 초록색으로 설정
		pMiniDot = g_pGameObjMgr->UILoad(UI_MINIDOT, L"GreenDot", L"GreenDot", D3DXVECTOR2(0, 0), false, true);

	if (pMiniDot != NULL)//Dot의 오브젝트랑 스케일 설정해줌
	{
		pMiniDot->SetObj(this);
		pMiniDot->SetScl(D3DXVECTOR2(-2, -2));
	}
}

void CPlayer::OnFrameMove(float fElapsedTime)//실시간 프레임 갱신
{
	__super::OnFrameMove(fElapsedTime);

	D3DXVECTOR2 vRMousePos = g_pMouse->GetOneRMousePos();//오른쪽 마우스의 위치를 받아오고

	if (vRMousePos != NULLVECTOR2)//클릭했을 경우 클릭한 마우스의 위치로 목표 재설정
	{
		m_vGoalPos = g_pGameTileMgr->FindCenterPos(g_pGameTileMgr->FindTileIndex(vRMousePos));
	}
}

void CPlayer::OnDamage(int iDamage, CGameObj* pGameObj)//플레이어가 데미지를 입었을 경우
{
	m_iHealth -= iDamage;//체력에서 데미지만큼 감소시킴

	if (m_iHealth <= 0)//체력이 0인경우 상태변환
	{
		if (m_iAniCategory != AT_DIE)
			OnChangeAni(AT_DIE);
	}
}