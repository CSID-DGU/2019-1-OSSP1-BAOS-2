#include "DXUT.h"
#include "Home.h"

extern CTexture* g_pTexture;
extern CSprite* g_pSprite;
extern CCamera* g_pCamera;

CUIAniRender::CUIAniRender( CAniObj* pGameObj ):
CRender( pGameObj ),
m_fTrackTime( 0.0f ),
	m_fTrackSpeed( 0.0f ),
	m_iCurIndex( 0 ),
	m_bLoop( false )
{
}


CUIAniRender::~CUIAniRender(void)
{
	for( int i = 0; i >= (int)m_vecTexture.size(); ++i )
		g_pTexture->ReserveRelease( m_vecTexture[i] );
}

void CUIAniRender::Load( wstring wFile )
{
	m_bLoop = ( GetPrivateProfileInt( L"Data", L"Loop", 0, wFile.c_str() ) == 1 );						// ini파일에서 Loop 여부 받아오기.
	m_fTrackSpeed = (float)GetPrivateProfileInt( L"Data", L"TrackSpeed", 0, wFile.c_str() ) * 0.01f;	// ini파일에서 속도 정보 받아오기.
	int iImgCount = GetPrivateProfileInt( L"Data", L"ImgCount", 0, wFile.c_str() );						// 불러올 이미지 갯수 정보 받아오기.

	WCHAR wcFileName[MAX_PATH];
	WCHAR wcFileExit[MAX_PATH];

	GetPrivateProfileString( L"Data", L"ImgFileName", L"", wcFileName, MAX_PATH, wFile.c_str() );		// 불러올 이미지 파일명 정보 받아오기
	GetPrivateProfileString( L"Data", L"ImgFileExit", L"", wcFileExit, MAX_PATH, wFile.c_str() );

	for( int i = 0; i < iImgCount; ++i )
	{
		wstringstream os;
		os << wcFileName << i << wcFileExit;		// 이미지 파일명이랑 나가는 경로를 로그에 기록해준다.
													// 텍스쳐 벡터(맵)에 push_back해준다.
		m_vecTexture.push_back( g_pTexture->Load( os.str().c_str() ) );
	}
}

bool CUIAniRender::OnFrameMove( float fElapsedTime )
{
	UpdateWorld();
	SetImgSize();

	m_fTrackTime += fElapsedTime;

	bool bChange = m_fTrackTime > m_fTrackSpeed;

	if( bChange )
	{
		int iIndex = m_iCurIndex + 1;

		if( iIndex >= (int) m_vecTexture.size() )
		{
			if( m_bLoop )
				SetAniIndex( 0 );
			else
				return false;
		}
		else
			SetAniIndex( iIndex );
	}

	return true;
}

void CUIAniRender::UpdateWorld()
{
	D3DXMATRIX matRot;
	MakeRot( matRot );

	D3DXMATRIX matTrans;
	MakeTrans( matTrans );

	D3DXMATRIX matScale;
	MakeScale( matScale );

	m_matWorld = matRot * matScale * matTrans;
	m_matWorld._43 = 0.0f;
}

void CUIAniRender::SetImgSize()
{
	const STextureInfo* pTextureInfo = g_pTexture->GetTextureInfo(m_vecTexture[m_iCurIndex] );
	if( pTextureInfo == NULL )
		return ;
	
	m_pGameObj->SetImgSize( D3DXVECTOR2( (float)pTextureInfo->m_TextureInfo.Width, (float)pTextureInfo->m_TextureInfo.Height ));
}

void CUIAniRender::OnFrameRender()
{
	if( m_iCurIndex < 0 || m_iCurIndex >= (int)m_vecTexture.size() )	// 만일 이미지 장수가 텍스쳐 배열크기보다 많으면
		return ;														// 문제가 생긴 것이므로 return.

	D3DXMATRIX matView;
	D3DXMatrixIdentity( &matView );		

	if( m_pGameObj->GetObjName() == L"Mouse" )
		g_pCamera->GetTransform( &matView );

	D3DXMATRIX matWorld = m_matWorld * matView;
	matWorld._43 = 0.0f;

	g_pSprite->SetTransform( &matWorld );
	g_pSprite->OnDraw( g_pTexture->GetTexture( m_vecTexture[m_iCurIndex] ), NULL, 0.0f, 0.0f );
}


void CUIAniRender::SetAniIndex( int iIndex )
{
	m_iCurIndex = iIndex;
	m_fTrackTime = 0.0f;
}