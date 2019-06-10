#include "DXUT.h"
#include "../Home.h"

extern CTexture * g_pTexture;
extern CSprite * g_pSprite;
extern CCamera * g_pCamera;

CAniRender::CAniRender( CAniObj * pGameObj )://AniRender 생성 및 초기화
CRender( pGameObj ),
m_fTrackTime( 0.0f ),
m_fTrackSpeed( 0.0f ),
m_iCurIndex( 0 ),
m_bLoop( false )
{
}

CAniRender::~CAniRender(void)
{
	for( int i = 0; i < (int)m_vecTexture.size(); ++i )	// 배열돌면서 제거 
		g_pTexture->ReserveRelease( m_vecTexture[i] );	// 차래대로 제거 
}


void CAniRender::Load( wstring wFile )
{
	m_bLoop = ( GetPrivateProfileInt( L"Data", L"Loop", 0, wFile.c_str() )  == 1 );     // 반복
	m_fTrackSpeed = (float)GetPrivateProfileInt( L"Data", L"TrackSpeed", 0, wFile.c_str() ) * 0.01f;	// 재생속도
	int iImgCount = GetPrivateProfileInt( L"Data", L"ImgCount", 0, wFile.c_str() );				// 이미지 장수

	WCHAR wcFileName[MAX_PATH]; // 이미지 이름
	WCHAR wcFileExit[MAX_PATH];	// 이미지 마지막

	GetPrivateProfileString( L"Data", L"ImgFileName", L"", wcFileName, MAX_PATH, wFile.c_str() );
	GetPrivateProfileString( L"Data", L"ImgFileExit", L"", wcFileExit, MAX_PATH, wFile.c_str() );

	for( int i = 0; i < iImgCount; ++i )
	{
		wstringstream os;
		os<< wcFileName << i << wcFileExit;

		m_vecTexture.push_back( g_pTexture->Load( os.str().c_str() ) );//벡터에 텍스쳐 정보 저장
	}

	m_AniEvent.Load( wFile );
};

bool CAniRender::OnFrameMove( float fElapsedTime )
{
	UpdateWorld();	// 행렬 업데이트
	
	m_fTrackTime += fElapsedTime;	// 시간더하기

	bool bChange = m_fTrackTime > m_fTrackSpeed; // 이미지 재생시간이랑 시간 비교 

	if( bChange )
	{
		m_AniEvent.OnEvent( (CAniObj*)m_pGameObj, m_iCurIndex );

		int iIndex = m_iCurIndex + 1;	// 이미지 장수 추가

		if( iIndex >= (int)m_vecTexture.size() )	// 장수와 텍스쳐 크기 비교
		{
			if( m_bLoop )	// 반복할것인가?
				SetAniIndex( 0 );
			else
				return false; 
		}
		else
			SetAniIndex( iIndex ); // 인덱스 번호 
	}
	return true;
}


void CAniRender::UpdateWorld()
{
	D3DXMATRIX matLocal;
	MakeLocal( matLocal );

	D3DXMATRIX matRot;
	MakeRot( matRot );

	D3DXMATRIX matTrans;
	MakeTrans( matTrans );	// 행렬 

	D3DXMATRIX matScale;
	MakeScale( matScale );

	m_matWorld = matLocal * matRot * matScale * matTrans;
	m_matWorld._43 = 0.0f;
}

void CAniRender::OnFrameRender()//Frame Render 
{
	if( m_iCurIndex < 0 || m_iCurIndex >= (int)m_vecTexture.size() )	// 이미지 장수와 텍스쳐 배열크기 비교
		return ;

	D3DXMATRIX matView;
	D3DXMatrixIdentity( &matView );		// 카메라 
	g_pCamera->GetTransform( &matView );//카메라 위치 받아옴

	D3DXMATRIX matWorld = m_matWorld * matView;
	matWorld._43 = 0.0f;

	g_pSprite->SetTransform( &matWorld );//스프라이트의 변환 위치 matWorld로 설정
	g_pSprite->OnDraw( g_pTexture->GetTexture( m_vecTexture[m_iCurIndex] ), NULL, 0.0f, 0.0f );
}


void CAniRender::MakeLocal( D3DXMATRIX &matTrans )	// 에니메이션 행렬 
{
	D3DXMatrixIdentity( &matTrans );	// 위치

	if( m_iCurIndex < 0 || m_iCurIndex >= (int)m_vecTexture.size() )	// 이미지 장수와 배열크기 비교
		return ;

	const STextureInfo* pTextureInfo = g_pTexture->GetTextureInfo( m_vecTexture[m_iCurIndex] );	// 텍스쳐 정보 불러오기
	if( pTextureInfo == NULL )
		return ;

	matTrans._41 -= ( pTextureInfo->m_TextureInfo.Width * 0.5f );	// 위치 행렬 
	matTrans._42 -= ( pTextureInfo->m_TextureInfo.Height * 1.0f );	// 위치 행렬
}

void CAniRender::SetAniIndex( int iIndex )	// 이미지 장수 반환
{
	m_iCurIndex = iIndex;
	m_fTrackTime = 0.0f;
}
