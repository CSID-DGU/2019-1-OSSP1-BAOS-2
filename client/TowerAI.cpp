#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;
extern CGameTileMgr* g_pGameTileMgr;
extern CGameObjMgr* g_pGameObjMgr;

CTowerAI::CTowerAI(CAniObj* pGameObj ):
	CGameObjController( pGameObj )
{
	AddState( AT_NORMAL, SFSMState(( DWORD )this, NULL, OnUpdateNormal, NULL ));
	AddState( AT_ATTACK, SFSMState(( DWORD )this, NULL, OnUpdateAttack, NULL ));
	AddState( AT_DIE, SFSMState(( DWORD )this, OnBeginDie, NULL, NULL ));
}


CTowerAI::~CTowerAI(void)
{
}

void CTowerAI::OnFrameMove( float fElapsedTime )
{
	m_pEnemy = g_pGameObjMgr->OnFindTarget( pGameObj(), g_pGameObjMgr->m_setPlayObj, m_pGameObj->GetScope() );
	OnUpdateState( fElapsedTime );
	OnChangeReserveState();
}

void CTowerAI::OnEndAni( int iAniCategory )
{
	if( iAniCategory == AT_DIE )
	{
		m_pGameObj->Destroy();
		return ;
	}

	pGameObj()->OnChangeAni( AT_NORMAL );
}

void CTowerAI::OnChangeAni( int iAniCategory )
{
	OnChangeState( iAniCategory );
} 

void CTowerAI::OnUpdateNormal( DWORD dwObj, float fElapsedTime )
{
	CTowerAI* pController = ( CTowerAI* )dwObj;
	CAniObj* pObj = pController->pGameObj();

	if( pController->GetEnemy() != NULL )
	{
		if( CUtil::CalcDist( pObj, pController->GetEnemy() ) < pObj->GetScope() )
			pObj->OnChangeAni( AT_ATTACK );
	}
}

void CTowerAI::OnUpdateAttack( DWORD dwObj, float fElapsedTime )
{
	CTowerAI* pController = ( CTowerAI* )dwObj;
	CAniObj* pObj = pController->pGameObj();
		
	if( pController->GetEnemy() == NULL )
	{
		pController->OnChangeAni( AT_NORMAL );
		return ;
	}
}

void CTowerAI::OnBeginDie( DWORD dwObj )
{
	CTowerAI* pController = ( CTowerAI* )dwObj;
	CAniObj* pObj = pController->pGameObj();

	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex( *pObj->GetPos() );

	for( int Row = (int)vPlayerIndex.x -1; Row <= vPlayerIndex.x + 1; Row++ )
		for( int Col = (int)vPlayerIndex.y - 1; Col <= vPlayerIndex.y; Col++ )
		{
			D3DXVECTOR2 vNeighborNode = D3DXVECTOR2( (float)Row, (float)Col );
			STileData* pData = g_pGameTileMgr->GetTileData( vNeighborNode );

			pData->m_iTileType = 1;
		}
}