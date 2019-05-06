#pragma once

struct SStaticData
{
	int m_iDrawType;
	int m_iFormat;

	wstring m_wStatic;
	D3DXCOLOR m_pColor;
	RECT m_rcRange;

	SStaticData():
		m_iDrawType( -1 ),
		m_iFormat( -1 )
	{
	}

	void AddStatic( int iDrawType, const WCHAR * strText, int iFormat, int iX, int iY, int iWidth, int iHeight, D3DXCOLOR pColor );
	void SetColor( D3DXCOLOR pColor ) { m_pColor = pColor; }
};

class CGameFontMgr
{
protected:
	map< int, LPD3DXFONT > m_mapFont;
	map< int, SStaticData* > m_mapStatic;

public:
	CGameFontMgr(void);
	virtual ~CGameFontMgr(void);

	void Destroy();

	void SetFont( int iID, const WCHAR* strText, int iHeight );
	void AddStatic( int iID, int iDrawType, const WCHAR* strText, int iFormat, int iX, int iY, int iWidth, int iHeight, D3DXCOLOR pColor ); 

	void ChangeFontType( int iID, int iDrawType );

	void ChangeStatic( int iID, const WCHAR* strText );
	void ChangeStatic( int iID, int iText );

	void SetColor( int iID, D3DXCOLOR pColor );
	void RemoveStatic( int iID );
	
	virtual void OnFrameRender();
};

