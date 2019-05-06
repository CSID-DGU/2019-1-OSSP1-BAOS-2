#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;
extern CGameFontMgr * g_pGameFontMgr;

CDebug::CDebug(void)
{
	g_pGameFontMgr->SetFont( TYPE_DEBUG, L"³ª´®°íµñ", 20);
	g_pGameFontMgr->AddStatic( FONT_DEBUG, FONT_DEBUG, L"", FONT_DEBUG, 10, 10, 500, 300, D3DXCOLOR( 255,255, 255, 100 ) ); 
}


CDebug::~CDebug(void)
{
}

void CDebug::OnFrameMove( float fElapsedTime )
{
	wstringstream os;

	D3DXVECTOR2 vMouse = g_pMouse->GetWorldMousePos();
	D3DXVECTOR2 vOneRMousePos = g_pMouse->GetOneRMousePos();
	D3DXVECTOR2 vOneLMousePos = g_pMouse->GetOneLMousePos();
	//D3DXVECTOR2 vCenterIndex = g_pGameTileMgr->FindIndexCenter( vMouse );
	int m_iType = 0;

	os << L"MouseX : " << vMouse.x << "  " << L"MouseY : " << vMouse.y;
	os << L"\n" << L"RMouseX : " << vOneRMousePos.x << " " << L"RMouseY : " << vOneRMousePos.y;
	os << L"\n" << L"LMouseX : " << vOneLMousePos.x << " " << L"LMouseY : " << vOneLMousePos.y;
	os << L"\n" << L"FPS : " << fElapsedTime * 1000;

	g_pGameFontMgr->ChangeStatic( FONT_DEBUG, os.str().c_str() );
}