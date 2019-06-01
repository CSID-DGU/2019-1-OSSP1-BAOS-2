#include "DXUT.h"
#include "Home.h"


CTexture::CTexture(void):
	m_iTexture( -1 )
{
}


CTexture::~CTexture(void)//소멸자
{
	ReleaesAll();//모두 놓아준다
}

int CTexture::Load( wstring wFile )//wFile Load
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wFile ); //map 자료구조의 wFile을 가리키는 iterator mit 생성
	if( mit != m_mapRefInfo.end() )//iterator mit를 찾았을 경우
	{
		++mit->second->m_iRefCount; //m_iRefCount에 1 증가시킨다.

		return mit->second->m_iTexture;//
	}

	D3DXIMAGE_INFO TextureInfo;	//이미지 정보 저장 구조체
	LPDIRECT3DTEXTURE9 pTexture;//directx 인터페이스

	//파일명에 해당되는 텍스쳐를 불러온다. 만일 S_OK 플래그가 맞지 않다면 로드 오류이므로 비정상 호출
	if( D3DXCreateTextureFromFileEx( DXUTGetD3D9Device()
		, wFile.c_str()
		, D3DX_DEFAULT
		, D3DX_DEFAULT
		, 1
		, 0
		, D3DFMT_A8R8G8B8
		, D3DPOOL_MANAGED
		, D3DX_FILTER_NONE
		, D3DX_FILTER_NONE
		, 0
		, &TextureInfo
		, NULL
		, & pTexture ) != S_OK )
		return - 1;

	++m_iTexture;	//텍스쳐 개수 증감

	STextureInfo* pTextureInfo = new STextureInfo;	//텍스쳐 정보 객체 동적할당 및 초기화
	pTextureInfo->m_iTexture  = m_iTexture;
	pTextureInfo->m_wFile = wFile;
	pTextureInfo->m_pTexture = pTexture;
	pTextureInfo->m_TextureInfo = TextureInfo;

	//텍스쳐에 이미지를 삽입
	m_mapTexture.insert( make_pair( m_iTexture, pTextureInfo ));
	m_mapRefInfo.insert( make_pair( wFile, pTextureInfo ));

	return m_iTexture;
}

const STextureInfo* CTexture::GetTextureInfo( int iTexture )//인수와 알맞은 텍스쳐 정보 가져오기
{
	map< int, STextureInfo* >::iterator mit = m_mapTexture.find( iTexture );
	if( mit == m_mapTexture.end() )//찾아오지 못했을 경우 NULL return
		return NULL;

	return mit->second;
}

const STextureInfo* CTexture::GetTextureInfo( wstring wFile )//인수와 알맞은 텍스쳐 정보 가져오기
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wFile );
	if( mit == m_mapRefInfo.end() )//찾아오지 못했을 경우 NULL return
		return NULL;

	return mit->second;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture( int iTexture )//인수와 알맞은 텍스쳐 정보 가져오기
{
	map< int, STextureInfo* >::iterator mit = m_mapTexture.find( iTexture );
	if( mit == m_mapTexture.end() )//찾아오지 못했을 경우 NULL return
		return NULL;

	return mit->second->m_pTexture;
}

LPDIRECT3DTEXTURE9 CTexture::GetTexture( wstring wFile )//인수와 알맞은 텍스쳐 정보 가져오기
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wFile );
	if( mit == m_mapRefInfo.end() )//찾아오지 못했을 경우 NULL return
		return NULL;

	return mit->second->m_pTexture;
}

void CTexture::ReserveRelease( int iTexture )
{
	map< int, STextureInfo* >::iterator mit = m_mapTexture.find( iTexture );
	if( mit == m_mapTexture.end() )//찾아오지 못했을 경우 NULL return
		return ;

	m_vecTextureID.push_back( iTexture );//textureID에 저장
}

DWORD* CTexture::GetImgColorBits( int iTexture )//ImgColorBits 가져오기
{
	map< int, STextureInfo* >::iterator mit = m_mapTexture.find( iTexture );
	if( mit == m_mapTexture.end() )
		return NULL;

	D3DLOCKED_RECT* pRect = new D3DLOCKED_RECT;		//사각형 구조체 생성
	mit->second->m_pTexture->LockRect( 0, pRect, NULL, 0 );

	D3DSURFACE_DESC drst;
	mit->second->m_pTexture->GetLevelDesc( 0, &drst );
	mit->second->m_ImgDesc = drst;

	if( mit->second->m_pColor == NULL )				//색깔이 없는경우
	{
		//색깔을 동적생성하고
		//사각형 구조체의 가로*세로만큼의 사이즈의 바이트를 color에 복사
		mit->second->m_pColor = new DWORD[ drst.Width * drst.Height ];
		memcpy( mit->second->m_pColor, pRect->pBits, drst.Width * drst.Height * sizeof( DWORD ) );
	}

	DWORD* pColor = (DWORD*)pRect->pBits;//칼라에 사각형의 Bits를 저장
	SAFE_DELETE( pRect );//사각형의 동적할당을 해제해준다

	mit->second->m_pTexture->UnlockRect( 0 );
	return pColor;
}

DWORD* CTexture::GetImgColorBits( wstring wFile )
{
	map< wstring, STextureInfo* >::iterator mit = m_mapRefInfo.find( wFile );
	if( mit == m_mapRefInfo.end() )
		return NULL;

	D3DLOCKED_RECT* pRect = new D3DLOCKED_RECT;
	mit->second->m_pTexture->LockRect( 0, pRect, NULL, 0 );

	D3DSURFACE_DESC drst;
	mit->second->m_pTexture->GetLevelDesc( 0, &drst );
	mit->second->m_ImgDesc = drst;

	if( mit->second->m_pColor == NULL )
	{
		mit->second->m_pColor = new DWORD[ drst.Width * drst.Height ];
		memcpy( mit->second->m_pColor, pRect->pBits, drst.Width * drst.Height * sizeof( DWORD ) );
	}

	DWORD* pColor = (DWORD*)pRect->pBits;
	SAFE_DELETE( pRect );

	mit->second->m_pTexture->UnlockRect( 0 );
	return pColor;
}

void CTexture::Release()//놓아주기
{
	for( int i = 0; i < (int)m_vecTextureID.size(); ++i )//텍스쳥ID의 개수만큼 데이터 제거
	{
		map< int, STextureInfo* >::iterator mit = m_mapTexture.find( m_vecTextureID[i] );
		if( mit == m_mapTexture.end() )//데이터가 없는 경우 return
			return ;

		--mit->second->m_iRefCount;

		if( mit->second->m_iRefCount > 0 )
			return ;

		map< wstring, STextureInfo* >::iterator mitRef = m_mapRefInfo.find( mit->second->m_wFile );
		if( mitRef != m_mapRefInfo.end() )//m_mapRefInfo의 찾는 데이터가 있는 경우 지워준다.
			m_mapRefInfo.erase( mitRef );

		SAFE_DELETE( mit->second );
		m_mapTexture.erase( mit );
	}
}

void CTexture::ReleaesAll()//전부 놓아주기
{
	map< int, STextureInfo* >::iterator mit = m_mapTexture.begin();
	while( mit != m_mapTexture.end() )//찾았을 경우
	{
		SAFE_DELETE( mit->second );//정보 삭제

		++mit;
	}

	m_mapTexture.clear();
	m_mapRefInfo.clear();
}

