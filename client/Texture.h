#pragma once

struct STextureInfo//텍스쳐의 정보 저장 구조체
{
	int m_iTexture;
	int m_iRefCount;
	wstring m_wFile;

	D3DXIMAGE_INFO m_TextureInfo; //텍스쳐 이미지 정보 객체
	LPDIRECT3DTEXTURE9 m_pTexture;//텍스쳐 객체

	DWORD * m_pColor;			 
	D3DSURFACE_DESC m_ImgDesc;

	STextureInfo()://텍스쳐의 정보 초기화
		m_iTexture( -1 ),
		m_iRefCount( 1 ),
		m_pTexture( NULL ),
		m_pColor( NULL )
	{
	}

	~STextureInfo()
	{
		SAFE_RELEASE( m_pTexture );//텍스쳐를 놓아주고 색깔을 제거한다.
		SAFE_DELETE( m_pColor );
	}
};

class CTexture
{
private:
	int m_iTexture;
	map< int, STextureInfo* > m_mapTexture;//map 자료구조를 이용해서 텍스쳐의 정보 저장
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

