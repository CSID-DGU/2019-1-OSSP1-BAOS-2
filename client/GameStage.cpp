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
	CGameStage* pGameStage = (CGameStage*)dwObj;	// 변수 선언
	pGameStage->m_iCurMap = 0;			// 맵 커서 초기화
	
	// TODO - ini 파일명과 경로는 추후 달라질 수 있다는 점 명심!

	g_pGameObjPool->LoadObj( L"Tile", L"Data/Tile.ini" );
	g_pGameObjPool->LoadObj( L"Start", L"Data/UI/Menu/Start.ini" );
	g_pGameObjPool->LoadObj( L"End", L"Data/UI/Menu/End.ini" );
	g_pGameObjPool->LoadObj( L"Continue", L"Data/UI/Menu/Continue.ini" );
	g_pGameObjPool->LoadObj( L"Option", L"Data/UI/Menu/Option.ini" );
	g_pGameObjPool->LoadObj( L"GameName", L"Data/UI/Menu/GameName.ini" );
	g_pGameObjPool->LoadObj( L"GameImage", L"Data/UI/Menu/GameImage.ini" );
	g_pGameObjPool->LoadObj( L"MenuBackGround1", L"Data/UI/Menu/MenuBackGround1.ini" );
	g_pGameObjPool->LoadObj( L"Loading", L"Data/UI/Loading/Loading.ini" );

}

void CGameStage::OnEndMenu( DWORD dwObj )
{

}	

void CGameStage::OnBeginNeos( DWORD dwObj )
{

}
