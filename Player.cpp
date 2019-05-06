#include "DXUT.h"
#include "Home.h"

extern CCamera* g_pCamera;
extern CMouse* g_pMouse;
extern CGameTileMgr* g_pGameTileMgr;
extern CGameObjMgr* g_pGameObjMgr;

CPlayer::CPlayer(void):
m_fTime( 0 )
{
	g_pCamera->SetCameraObj( this );
}


CPlayer::~CPlayer(void)
{
}

void CPlayer::Load( wstring wFile )
{
	__super::Load( wFile );

	//m_pController = new CEricController( this );

	SetPos( g_pGameTileMgr->FindCenterPos( m_vPos ) );


	OnChangeAni( AT_NORMAL );
}

void CPlayer::OnFrameMove ( float fElapsedTime )
{
	__super::OnFrameMove( fElapsedTime );
	
	D3DXVECTOR2 vRMousePos = g_pMouse->GetOneRMousePos() ;


	/*if( vRMousePos !=NULLVECTOR2 )
	{
		m_pController->pEnemy = NULL;
		m_vGoalPos = g_pGameTileMgr->FindCenterPos( g_pGameTileMgr->FindTileIndex( vRMousePos ) );
	}*/
}