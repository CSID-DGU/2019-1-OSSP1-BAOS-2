#include "DXUT.h"
#include "Home.h"

extern CGameObjPool * g_pGameObjPool;
extern CGameObjMgr* g_pGameObjMgr;
extern CGameTileMgr* g_pGameTileMgr;

CTower::CTower(void)
{
}


CTower::~CTower(void)
{
}

void CTower::Load( wstring wFile )
{
	/*__super::Load( wFile );

	m_pController = new CTowerAI( this );

	CGameObj* pHealth = g_pGameObjMgr->Load( EGAMEOBJ_HEALTH, ETEAM_NENUTAL, L"Creature_Health", L"Health", D3DXVECTOR2( 0, 0 ), 0, ERENDER_NORMAL, true );
	((CHealth*)pHealth)->SetPlayer( this );

	CUI* pMiniDot = NULL;// 구현안함

	if( m_iTeam == ETEAM_FRIEND )
		pMiniDot = g_pGameObjMgr->UILoad( UI_MINIDOT, L"GreenDot", L"GreenDot", D3DXVECTOR2( 0, 0 ), false, true );

	if( m_iTeam == ETEAM_ENEMY )
		pMiniDot = g_pGameObjMgr->UILoad( UI_MINIDOT, L"RedDot", L"RedDot", D3DXVECTOR2( 0, 0 ), false, true );


	if( pMiniDot != NULL )
	{
		pMiniDot->SetObj(this );
		pMiniDot->SetScl( D3DXVECTOR2( -2, -2 ));
	}

	OnChangeAni( AT_NORMAL );

	for( int Row = (int)m_vPos.x -1; Row <= m_vPos.x + 1; Row++ )
		for( int Col = (int)m_vPos.y - 1; Col <= m_vPos.y; Col++ )
		{
			D3DXVECTOR2 vNeighborNode = D3DXVECTOR2( (float)Row, (float)Col );
			STileData* pData = g_pGameTileMgr->GetTileData( vNeighborNode );

			pData->m_iTileType = 0;
		}

	SetPos( g_pGameTileMgr->FindCenterPos( m_vPos ) );*/

}

void CTower::OnDamage( int iDamage)
{
	m_iHealth -= iDamage;

	if( m_iHealth <= 0 )
	{
		if( m_iAniCategory != AT_DIE )
			OnChangeAni( AT_DIE );
	}
}

void CTower::OnFrameMove( float fElapsedTime )
{
	__super::OnFrameMove( fElapsedTime );
}