#include "DXUT.h"
#include "Home.h"

extern CGameObjPool* g_pGameObjPool;
extern CGameObjMgr* g_pGameObjMgr;
extern CGameTileMgr* g_pGameTileMgr;
extern CTexture* g_pTexture;

CGameStage::CGameStage(void):
	m_pGameArea( NULL )
{
	AddState( EMAP_MENU, SFSMState((DWORD)this, OnBeginMenu, NULL, OnEndMenu ));
	AddState( EMAP_NEOS, SFSMState( (DWORD)this,  OnBeginNeos, NULL, NULL ));
}

CGameStage::~CGameStage(void)
{
}

void CGameStage::OnChangeArea( int iMap )
{
	if( OnChangeState( iMap ) == false )
		return ;

	SAFE_DELETE( m_pGameArea );
}

void CGameStage::Load()
{
	OnChangeArea( EMAP_MENU );
}

void CGameStage::OnFrameMove( float fElapsedTime )
{
	OnUpdateState( fElapsedTime );

	OnChangeReserveState();

	if( m_pGameArea != NULL )
		m_pGameArea->OnFrameMove( fElapsedTime );
}

void CGameArea::OnFrameMove(float fElapsedTime) {
	

}

void CGameStage::OnBeginMenu( DWORD dwObj )
{
	CGameStage* pGameStage = (CGameStage*)dwObj;
	pGameStage->m_iCurMap = 0;

	g_pGameObjPool->LoadObj( L"Tile", L"Data/Tile.ini" );
	g_pGameObjPool->LoadObj( L"Start", L"Data/UI/Menu/Start.ini" );
	g_pGameObjPool->LoadObj( L"End", L"Data/UI/Menu/End.ini" );
	g_pGameObjPool->LoadObj( L"Continue", L"Data/UI/Menu/Continue.ini" );
	g_pGameObjPool->LoadObj( L"Option", L"Data/UI/Menu/Option.ini" );
	g_pGameObjPool->LoadObj( L"GameName", L"Data/UI/Menu/GameName.ini" );
	g_pGameObjPool->LoadObj( L"GameImage", L"Data/UI/Menu/GameImage.ini" );
	g_pGameObjPool->LoadObj( L"MenuBackGround1", L"Data/UI/Menu/MenuBackGround1.ini" );
	g_pGameObjPool->LoadObj( L"MenuBackGround2", L"Data/UI/Menu/MenuBackGround2.ini" );
	g_pGameObjPool->LoadObj( L"Loading", L"Data/UI/Loading/Loading.ini" );


	//g_pGameObjMgr->UILoad( UI_NULL, L"GameName", L"UIMenu", D3DXVECTOR2( 12, 12 ), false, true );
	//g_pGameObjMgr->UILoad( UI_NULL, L"GameImage", L"UIMenu", D3DXVECTOR2( 12, 152 ), false, true );
	//g_pGameObjMgr->UILoad( UI_NULL, L"MenuBackGround1", L"UIMenu", D3DXVECTOR2( 580, 12 ), false, true );
	//g_pGameObjMgr->UILoad( UI_NULL, L"MenuBackGround2", L"UIMenu", D3DXVECTOR2( 580, 556 ), false, true );
	//g_pGameObjMgr->UILoad( UI_START, L"Start", L"UIMenu", D3DXVECTOR2( 596, 92 ), false, true );
	////g_pGameObjMgr->UILoad( 0, L"Continue", L"UIMenu", D3DXVECTOR2( 596, 236 ), false, true );
	////g_pGameObjMgr->UILoad( 0, L"Option", L"UIMenu", D3DXVECTOR2( 1270, 550 ), false, true );
	////g_pGameObjMgr->UILoad( UI_EXIT, L"End", L"UIMenu", D3DXVECTOR2( 1270, 852 ), false, true );
	//
	//g_pGameObjPool->LoadAniObj( L"Mouse", L"Data/UI/Mouse/Mouse.ini" );
	//g_pGameObjMgr->UILoad( UI_MOUSE, L"Mouse", L"Mouse", D3DXVECTOR2( 0, 0 ), true, true );

}

void CGameStage::OnEndMenu( DWORD dwObj )
{
	/*g_pGameObjMgr->Destroy( EGAMEOBJ_UI, L"UIMenu" );
	g_pTexture->Release();*/
}	

void CGameStage::OnBeginNeos( DWORD dwObj )
{
	/*CGameStage* pGameStage = (CGameStage*)dwObj;
	pGameStage->m_pGameArea = new CNeos_Area( pGameStage );

	pGameStage->m_pGameArea->Load();
	pGameStage->m_iCurMap = EMAP_NEOS;*/
}