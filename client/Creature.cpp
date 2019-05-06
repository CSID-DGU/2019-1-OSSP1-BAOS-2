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

void CCreature::Load( wstring wFile )
{
	__super::Load( wFile );

	//m_pController = new CCreatureAI( this );

	//CGameObj* pHealth = g_pGameObjMgr->Load( EGAMEOBJ_HEALTH, ETEAM_NENUTAL, L"Creature_Health", L"Health", D3DXVECTOR2( 0, 0 ), 0, ERENDER_NORMAL, true );
	//((CHealth*)pHealth)->SetPlayer( this );

	//CUI* pMiniDot = NULL;

	//if( m_iTeam == ETEAM_FRIEND )
	//	pMiniDot = g_pGameObjMgr->UILoad( UI_MINIDOT, L"GreenDot", L"GreenDot", D3DXVECTOR2( 0, 0 ), false, true );

	//if( m_iTeam == ETEAM_ENEMY )
	//	pMiniDot = g_pGameObjMgr->UILoad( UI_MINIDOT, L"RedDot", L"RedDot", D3DXVECTOR2( 0, 0 ), false, true );


	//if( pMiniDot != NULL )
	//	pMiniDot->SetObj( this );


	////SetPos( g_pGameTileMgr->FindCenterPos( m_vPos ) );
	//g_pGameObjMgr->Load( EGAMEOBJ_BEGINEFFECT, ETEAM_NENUTAL, L"Spawn", L"Spawn", m_vPos + D3DXVECTOR2( 0, 50 ), 0, ERENDER_NORMAL, true );

	//OnChangeAni( AT_NORMAL );
}

void CCreature::OnFrameMove( float fElapsedTime )
{
	__super::OnFrameMove( fElapsedTime );
}

void CCreature::OnDamage( int iDamage, CGameObj* pObj )
{
	m_iHealth -= iDamage;

	if( m_iHealth <= 0 )
	{
		if( m_iAniCategory != AT_DIE )
			OnChangeAni( AT_DIE );
	}

	if( pObj->IsDestroy() == false )
		m_pDamager = pObj;
}