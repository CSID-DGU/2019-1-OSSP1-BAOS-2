#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;
extern CGameTileMgr* g_pGameTileMgr;
extern CGameFontMgr * g_pGameFontMgr;

CDebug::CDebug(void)//디버그 생성
{
	//폰트 설정하고 타입이랑 사이즈 설정
	g_pGameFontMgr->SetFont( TYPE_DEBUG, L"나눔고딕", 15 );
	g_pGameFontMgr->AddStatic( FONT_DEBUG, FONT_DEBUG, L"", FONT_DEBUG, 10, 10, 500, 300, D3DXCOLOR( 255,255, 255, 100 ) ); 
}


CDebug::~CDebug(void)
{
}

void CDebug::OnFrameMove( float fElapsedTime )//현시간마다 프레임 갱신
{
	wstringstream os;

	D3DXVECTOR2 vMouse = g_pMouse->GetWorldMousePos();
	D3DXVECTOR2 vOneRMousePos = g_pMouse->GetOneRMousePos();
	D3DXVECTOR2 vOneLMousePos = g_pMouse->GetOneLMousePos();
	//D3DXVECTOR2 vCenterIndex = g_pGameTileMgr->FindIndexCenter( vMouse );
	int m_iType = 0;

	if( g_pGameTileMgr != NULL )//게임 타일매니저가 있을경우
	{
		//
		STileData* pData = g_pGameTileMgr->GetTileData( g_pGameTileMgr->FindTileIndex( vMouse ) );
		if( pData != NULL )
		m_iType = pData->m_iTileType;
	}

	D3DXVECTOR2 vTilePos;

	if( g_pGameTileMgr != NULL )
		vTilePos = g_pGameTileMgr->FindTileIndex( vMouse );
	else
		vTilePos = D3DXVECTOR2( 0.0f, 0.0f );


	//디버깅 상황 출력
	//마우스 위치와 왼쪽 마우스, 오른쪽 마우스, 타일 위치와 타일 타입 출력
	os << L"MouseX : " << vMouse.x << "  " << L"MouseY : " << vMouse.y;
	os << L"\n" << L"RMouseX : " << vOneRMousePos.x << " " << L"RMouseY : " << vOneRMousePos.y;
	os << L"\n" << L"LMouseX : " << vOneLMousePos.x << " " << L"LMouseY : " << vOneLMousePos.y;
	os << L"\n" << L"TileX : " << vTilePos.x << " " << L"TileY : " << vTilePos.y;
	os << L"\n" << L"TileType : " << m_iType;
	//os << L"\n" << L"CenterIndexX : " << vCenterIndex.x << L"CenterIndexY : " << vCenterIndex.y;
	os << L"\n" << L"FPS : " << fElapsedTime * 1000;

	g_pGameFontMgr->ChangeStatic( FONT_DEBUG, os.str().c_str() );
}