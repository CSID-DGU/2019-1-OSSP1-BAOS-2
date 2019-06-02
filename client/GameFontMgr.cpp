#include "DXUT.h"
#include "Home.h"

void SStaticData::AddStatic( int iDrawType, const WCHAR* strText, int iFormat, int iX, int iY, int iWidth, int iHeight, D3DXCOLOR pColor )
{
	m_iDrawType = iDrawType;//폰트 구조체에서 정보 저장하기
	m_wStatic = strText;
	m_iFormat = iFormat;
	m_pColor = pColor;

	RECT rcRange = { iX, iY, iWidth, iHeight };//폰트의 사이즈 설정
	m_rcRange = rcRange;
}

CGameFontMgr::CGameFontMgr(void)
{
}


CGameFontMgr::~CGameFontMgr(void)
{
	Destroy();
}

void CGameFontMgr::Destroy()//쓰지 않는 게임 폰트들을 놓아주게 함
{
	for each( map< int, LPD3DXFONT >::const_reference mr in m_mapFont )
		mr.second->Release();

	for each( map< int, SStaticData* >::const_reference mr in m_mapStatic )
		delete mr.second;

	m_mapStatic.clear();
}

void CGameFontMgr::OnFrameRender()//프레임을 계속 갱신시켜준다.
{
	map< int, SStaticData* >::iterator mit = m_mapStatic.begin();
	for( mit; mit != m_mapStatic.end(); ++mit )
	{
		map< int, LPD3DXFONT >::iterator mitFont = m_mapFont.find( mit->second->m_iDrawType );
		if( mitFont == m_mapFont.end() )//프레임을 못찾았을 경우 
			continue ;

		mitFont->second->DrawText( NULL, mit->second->m_wStatic.c_str(), -1, &mit->second->m_rcRange, mit->second->m_iFormat, mit->second->m_pColor );
	}
}

void CGameFontMgr::SetFont(int iID, const WCHAR* strFontType, int iHeight )//폰트 설정
{
	map<int, LPD3DXFONT>::iterator mit = m_mapFont.find( iID );
	if( mit != m_mapFont.end() )
		return ;

	LPD3DXFONT pFont;

	if( FAILED( D3DXCreateFont( DXUTGetD3D9Device(),//폰트 설정이 실패할 경우 리턴
			iHeight,
			0,
			FW_BOLD,
			1,
			FALSE,
			HANGUL_CHARSET,
			OUT_DEFAULT_PRECIS,
			ANTIALIASED_QUALITY,
			FF_DONTCARE,
			strFontType,
			&pFont ) ) )
	{
		return ;
	}
	m_mapFont.insert( make_pair( iID, pFont ) );
}

void CGameFontMgr::AddStatic(int iID, int iDrawType, const WCHAR* strText, int iFormat, int iX, int iY, int iWidth, int iHeight, D3DXCOLOR Color)
{
	map<int, SStaticData*>::iterator mit = m_mapStatic.find( iID );
	if( mit != m_mapStatic.end() )//중복 제거 위해 먼저 폰트 값이 들어있는지 찾아줌
		return ;

	map<int, LPD3DXFONT>::iterator mitFont = m_mapFont.find( iDrawType );
	if( mitFont == m_mapFont.end() )
		return ;

	SStaticData* pData = new SStaticData;//폰트가 없을 경우 데이터 생성 및 동적할당
	pData->AddStatic( iDrawType,  strText, iFormat, iX, iY, iWidth, iHeight, Color );

	m_mapStatic.insert( make_pair( iID, pData ) );//폰트 추가
}

void CGameFontMgr::ChangeFontType( int iID, int iDrawType )//폰트 id의 형태 바꾸기
{
	map<int, SStaticData*>::iterator mit = m_mapStatic.find( iID );
	if( mit == m_mapStatic.end() )//못찾앗을 경우 리턴
		return ;

	map<int, LPD3DXFONT>::iterator mitFont = m_mapFont.find( iDrawType );
	if( mitFont == m_mapFont.end() )
		return ;

	mit->second->m_iDrawType = iDrawType;//찾았을 경우 형태 바꿔주기
}

void CGameFontMgr::ChangeStatic(int iID, const WCHAR* strText)//static 바꿔주기
{
	map<int, SStaticData*>::iterator mit = m_mapStatic.find( iID );
	if( mit == m_mapStatic.end() )
		return ;

	mit->second->m_wStatic = strText;
}

void CGameFontMgr::ChangeStatic(int iID, int iText)
{
	map<int, SStaticData*>::iterator mit = m_mapStatic.find( iID );
	if( mit == m_mapStatic.end() )
		return ;

	wstringstream strApp;
	strApp<<iText;

	mit->second->m_wStatic = strApp.str();
}

void CGameFontMgr::SetColor(int iID, D3DXCOLOR Color)//색깔 설정
{
	map<int, SStaticData*>::iterator mit = m_mapStatic.find( iID );
	if( mit == m_mapStatic.end() )
		return ;

	mit->second->m_pColor = Color;
}

void CGameFontMgr::RemoveStatic( int iID )//iTD 삭제 
{
	map<int, SStaticData*>::iterator mit = m_mapStatic.find( iID );
	if( mit == m_mapStatic.end() )
		return ;

	SAFE_DELETE( mit->second );
	m_mapStatic.erase( mit );
}