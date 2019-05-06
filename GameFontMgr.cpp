#include "DXUT.h"
#include "Home.h"

void SStaticData::AddStatic( int iDrawType, const WCHAR* strText, int iFormat, int iX, int iY, int iWidth, int iHeight, D3DXCOLOR pColor )
{
	m_iDrawType = iDrawType;
	m_wStatic = strText;
	m_iFormat = iFormat;
	m_pColor = pColor;

	RECT rcRange = { iX, iY, iWidth, iHeight };
	m_rcRange = rcRange;
}

CGameFontMgr::CGameFontMgr(void)
{
}


CGameFontMgr::~CGameFontMgr(void)
{
	Destroy();
}

void CGameFontMgr::Destroy()
{
	for each( map< int, LPD3DXFONT >::const_reference mr in m_mapFont )
		mr.second->Release();

	for each( map< int, SStaticData* >::const_reference mr in m_mapStatic )
		delete mr.second;

	m_mapStatic.clear();
}

void CGameFontMgr::OnFrameRender()
{
	map< int, SStaticData* >::iterator mit = m_mapStatic.begin();
	for( mit; mit != m_mapStatic.end(); ++mit )
	{
		map< int, LPD3DXFONT >::iterator mitFont = m_mapFont.find( mit->second->m_iDrawType );
		if( mitFont == m_mapFont.end() )
			continue ;

		mitFont->second->DrawText( NULL, mit->second->m_wStatic.c_str(), -1, &mit->second->m_rcRange, mit->second->m_iFormat, mit->second->m_pColor );
	}
}

void CGameFontMgr::SetFont(int iID, const WCHAR* strFontType, int iHeight )
{
	map<int, LPD3DXFONT>::iterator mit = m_mapFont.find( iID );
	if( mit != m_mapFont.end() )
		return ;

	LPD3DXFONT pFont;

	if( FAILED( D3DXCreateFont( DXUTGetD3D9Device(),
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
	if( mit != m_mapStatic.end() )
		return ;

	map<int, LPD3DXFONT>::iterator mitFont = m_mapFont.find( iDrawType );
	if( mitFont == m_mapFont.end() )
		return ;

	SStaticData* pData = new SStaticData;
	pData->AddStatic( iDrawType,  strText, iFormat, iX, iY, iWidth, iHeight, Color );

	m_mapStatic.insert( make_pair( iID, pData ) );
}

void CGameFontMgr::ChangeFontType( int iID, int iDrawType )
{
	map<int, SStaticData*>::iterator mit = m_mapStatic.find( iID );
	if( mit == m_mapStatic.end() )
		return ;

	map<int, LPD3DXFONT>::iterator mitFont = m_mapFont.find( iDrawType );
	if( mitFont == m_mapFont.end() )
		return ;

	mit->second->m_iDrawType = iDrawType;
}

void CGameFontMgr::ChangeStatic(int iID, const WCHAR* strText)
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

void CGameFontMgr::SetColor(int iID, D3DXCOLOR Color)
{
	map<int, SStaticData*>::iterator mit = m_mapStatic.find( iID );
	if( mit == m_mapStatic.end() )
		return ;

	mit->second->m_pColor = Color;
}

void CGameFontMgr::RemoveStatic( int iID )
{
	map<int, SStaticData*>::iterator mit = m_mapStatic.find( iID );
	if( mit == m_mapStatic.end() )
		return ;

	SAFE_DELETE( mit->second );
	m_mapStatic.erase( mit );
}