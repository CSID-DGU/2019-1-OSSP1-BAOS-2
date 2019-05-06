#pragma once

struct STextureInfo
{
	int m_iTexture;
	int m_iRefCount;
	wstring m_wFile;

	D3DXIMAGE_INFO m_TextureInfo;
	LPDIRECT3DTEXTURE9 m_pTexture;

	DWORD * m_pColor;
	D3DSURFACE_DESC m_ImgDesc;

	STextureInfo():
		m_iTexture( -1 ),
		m_iRefCount( 1 ),
		m_pTexture( NULL ),
		m_pColor( NULL )
	{
	}

	~STextureInfo()
	{
		SAFE_RELEASE( m_pTexture );
		SAFE_DELETE( m_pColor );
	}
};

class CTexture
{
private:
	int m_iTexture;
	map< int, STextureInfo* > m_mapTexture;
	map< wstring, STextureInfo* > m_mapRefInfo;

	vector< int > m_vecTextureID;

public:
	CTexture(void);
	virtual ~CTexture(void);

	int Load( const wstring wFile );

	const STextureInfo* GetTextureInfo( int iTexture );
	const STextureInfo* GetTextureInfo( wstring wFile );

	LPDIRECT3DTEXTURE9 GetTexture( int iTexture );
	LPDIRECT3DTEXTURE9 GetTexture( wstring wFile );

	DWORD* GetImgColorBits( int iTexture );
	DWORD* GetImgColorBits( wstring wFile );

	void ReserveRelease( int iTexture );

	void Release();
	void ReleaesAll();
};

