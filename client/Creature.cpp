#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;
extern CGameTileMgr* g_pGameTileMgr;

CCreature::CCreature(void)
{
}


CCreature::~CCreature(void)
{
}

void CCreature::Load( wstring wFile )//wFile 크리쳐 로드
{
	__super::Load( wFile );

	m_pController = new CCreatureAI( this );//크리쳐 ai생성

	//게임 오브젝트 매너저에서 체력 오브젝트 로드
	CGameObj* pHealth = g_pGameObjMgr->Load( EGAMEOBJ_HEALTH, ETEAM_NENUTAL, L"Creature_Health", L"Health", D3DXVECTOR2( 0, 0 ), 0, ERENDER_NORMAL, true );
	((CHealth*)pHealth)->SetPlayer( this );

	CUI* pMiniDot = NULL;//ui minidot 생성 미니맵에서 보여줄 작은 Dot들 의미

	if( m_iTeam == ETEAM_FRIEND )//팀이 아군 팀일 경우 초록색으로 Dot 설정
		pMiniDot = g_pGameObjMgr->UILoad( UI_MINIDOT, L"GreenDot", L"GreenDot", D3DXVECTOR2( 0, 0 ), false, true );

	if( m_iTeam == ETEAM_ENEMY )//팀이 적군 팀일 경우 빨간색으로 Dot 설정
		pMiniDot = g_pGameObjMgr->UILoad( UI_MINIDOT, L"RedDot", L"RedDot", D3DXVECTOR2( 0, 0 ), false, true );


	if( pMiniDot != NULL )//생성된 경우
		pMiniDot->SetObj( this );//오브젝트 설정


	SetPos( g_pGameTileMgr->FindCenterPos( m_vPos ) );//위치 설정
	g_pGameObjMgr->Load( EGAMEOBJ_BEGINEFFECT, ETEAM_NENUTAL, L"Spawn", L"Spawn", m_vPos + D3DXVECTOR2( 0, 50 ), 0, ERENDER_NORMAL, true );

	OnChangeAni( AT_NORMAL );//NORMAL 상태로 애니 전환
}

void CCreature::OnFrameMove( float fElapsedTime )//프레임 갱신
{
	__super::OnFrameMove( fElapsedTime );
}

void CCreature::OnDamage( int iDamage, CGameObj* pObj )//데미지 설정
{
	m_iHealth -= iDamage;//현재 체력에서 데미지만큼 빼주어 체력 갱신

	if( m_iHealth <= 0 )//데미지가 0이하가 되면 죽은 상태
	{
		if( m_iAniCategory != AT_DIE )//죽은 상태가 아니라면 
			OnChangeAni( AT_DIE );//죽은 상태로 애니 전환
	}

	if( pObj->IsDestroy() == false )//제거되지 않았다면
		m_pDamager = pObj;//제거함
}