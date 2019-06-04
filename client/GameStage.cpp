#include "DXUT.h"
#include "Home.h"

extern GameDataMgr* g_pGameDataMgr;
extern CGameObjMgr* g_pGameObjMgr;
extern CGameTileMgr* g_pGameTileMgr;
extern CTexture* g_pTexture;

CGameStage::CGameStage(void)://gameStage 생성자 및 초기화 부분
	m_pGameArea( NULL )
{
	AddState( EMAP_MENU, SFSMState((DWORD)this, OnBeginMenu, NULL, OnEndMenu ));// 메뉴 맵 상태 추가
	AddState( EMAP_NEOS, SFSMState( (DWORD)this,  OnBeginNeos, NULL, NULL ));	// neos 맵 상태 추가
}


CGameStage::~CGameStage(void)
{
}

void CGameStage::OnChangeArea( int iMap )//area 전환
{
	if( OnChangeState( iMap ) == false )
		return ;

	SAFE_DELETE( m_pGameArea );//현재 게임 area 제거
}

void CGameStage::Load()
{
	OnChangeArea( EMAP_MENU );//메뉴 load
}

void CGameStage::OnFrameMove( float fElapsedTime )//Frame 실시간 갱신
{
	OnUpdateState( fElapsedTime );//상태 업데이트

	OnChangeReserveState();

	if( m_pGameArea != NULL )
		m_pGameArea->OnFrameMove( fElapsedTime );
}

void CGameStage::OnBeginMenu( DWORD dwObj )//시작시 메뉴 설정
{
	CGameStage* pGameStage = (CGameStage*)dwObj;
	pGameStage->m_iCurMap = 0;

	//시작시 필요한 메뉴 오브젝트 전부 로드 
	g_pGameDataMgr->LoadObj( L"Tile", L"Data/Tile.ini" );
	g_pGameDataMgr->LoadObj( L"Start", L"Data/UI/Menu/Start.ini" );
	g_pGameDataMgr->LoadObj( L"End", L"Data/UI/Menu/End.ini" );
	g_pGameDataMgr->LoadObj( L"Continue", L"Data/UI/Menu/Continue.ini" );
	g_pGameDataMgr->LoadObj( L"Option", L"Data/UI/Menu/Option.ini" );
	g_pGameDataMgr->LoadObj( L"GameName", L"Data/UI/Menu/GameName.ini" );
	g_pGameDataMgr->LoadObj( L"GameImage", L"Data/UI/Menu/GameImage.ini" );
	g_pGameDataMgr->LoadObj( L"MenuBackGround1", L"Data/UI/Menu/MenuBackGround1.ini" );
	g_pGameDataMgr->LoadObj( L"MenuBackGround2", L"Data/UI/Menu/MenuBackGround2.ini" );
	g_pGameDataMgr->LoadObj( L"Loading", L"Data/UI/Loading/Loading.ini" );


	g_pGameObjMgr->UILoad( UI_NULL, L"GameName", L"UIMenu", D3DXVECTOR2( 12, 12 ), false, true );
	g_pGameObjMgr->UILoad( UI_NULL, L"GameImage", L"UIMenu", D3DXVECTOR2( 12, 152 ), false, true );
	g_pGameObjMgr->UILoad( UI_NULL, L"MenuBackGround1", L"UIMenu", D3DXVECTOR2( 580, 12 ), false, true );
	g_pGameObjMgr->UILoad( UI_NULL, L"MenuBackGround2", L"UIMenu", D3DXVECTOR2( 580, 556 ), false, true );
	g_pGameObjMgr->UILoad( UI_START, L"Start", L"UIMenu", D3DXVECTOR2( 596, 92 ), false, true );
	//g_pGameObjMgr->UILoad( 0, L"Continue", L"UIMenu", D3DXVECTOR2( 596, 236 ), false, true );
	//g_pGameObjMgr->UILoad( 0, L"Option", L"UIMenu", D3DXVECTOR2( 1270, 550 ), false, true );
	//g_pGameObjMgr->UILoad( UI_EXIT, L"End", L"UIMenu", D3DXVECTOR2( 1270, 852 ), false, true );
	
	g_pGameDataMgr->LoadAniObj( L"Mouse", L"Data/UI/Mouse/Mouse.ini" );
	g_pGameObjMgr->UILoad( UI_MOUSE, L"Mouse", L"Mouse", D3DXVECTOR2( 0, 0 ), true, true );


}

void CGameStage::OnEndMenu( DWORD dwObj )//메뉴 상태가 끝났을 경우
{
	g_pGameObjMgr->Destroy( EGAMEOBJ_UI, L"UIMenu" );//게임 오브젝트 ui메뉴 제거
	g_pTexture->Release();//데이터 놓아줌
}

void CGameStage::OnBeginNeos( DWORD dwObj )//본 게임 맵 시작
{
	CGameStage* pGameStage = (CGameStage*)dwObj;//본 게임 스테이지 동적할당
	pGameStage->m_pGameArea = new CNeos_Area( pGameStage );

	pGameStage->m_pGameArea->Load();
	pGameStage->m_iCurMap = EMAP_NEOS;//게임스테이지 현재상태에 NEOS_MAP load
}