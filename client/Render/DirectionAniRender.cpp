#include "DXUT.h"
#include "../Home.h"

extern CTexture* g_pTexture;
extern CSprite* g_pSprite;
extern CCamera* g_pCamera;

CDirectionAniRender::CDirectionAniRender( CAniObj* pGameObj )://render함수와 오브젝트 초기화
	CRender( pGameObj ),
	pAniObj( pGameObj ),
	m_fTrackTime( 0.0f ),
	m_fTrackSpeed( 0.0f ),
	m_iCurIndex( 0 ),
	m_bLoop( false )
{
}


CDirectionAniRender::~CDirectionAniRender(void)//소멸자
{
	map< int, vector< int >>::iterator mit = m_mapAniDirection.begin();
	for( mit; mit != m_mapAniDirection.end(); ++mit )//Map에 저장된 aniDirection 전부 반복
	{
		for( int i = 0; i < (int)mit->second.size(); ++i )//텍스쳐 Release
			g_pTexture->ReserveRelease( mit->second[i] );
	}
}

void CDirectionAniRender::Load( wstring wFile )//wFile load
{
	m_bLoop = ( GetPrivateProfileInt( L"Data", L"Loop", 0, wFile.c_str() ) == 1);
	m_fTrackSpeed = (float)GetPrivateProfileInt( L"Data", L"TrackSpeed", 0, wFile.c_str() ) * 0.01f;
	int iImgCount = GetPrivateProfileInt( L"Data", L"ImgCount", 0, wFile.c_str() );

	WCHAR wcFileName[MAX_PATH];
	WCHAR wcFileExit[MAX_PATH];

	GetPrivateProfileString( L"Data", L"ImgFileName", L"", wcFileName, MAX_PATH, wFile.c_str() );
	GetPrivateProfileString( L"Data", L"ImgFileExit", L"", wcFileExit, MAX_PATH, wFile.c_str() );

	for( int j = 0; j < 5; ++j )
	{
		for( int i = 0; i < iImgCount; ++i )
		{
			wstringstream os;
			os << wcFileName << j << " (" << i << wcFileExit;

			m_mapAniDirection[j].push_back( g_pTexture->Load( os.str().c_str() ));//AniDirection map에 텍스쳐 정보 저장
		}
	}
	 
	m_mapAniDirection[5] = m_mapAniDirection[3];
	m_mapAniDirection[6] = m_mapAniDirection[2];
	m_mapAniDirection[7] = m_mapAniDirection[1];

	m_AniEvent.Load( wFile );
};

bool CDirectionAniRender::OnFrameMove( float fElapsedTime )//프레임 갱신
{
	UpdateWorld();//월드 업데이트
	
	m_fTrackTime += fElapsedTime;//TrackTime 갱신

	bool bChange = m_fTrackTime > m_fTrackSpeed;//Tracktime이 TrackSpeed보다 큰지 확인

	if( bChange )//만약 크다면 
	{
		int iIndex = m_iCurIndex + 1;
		m_AniEvent.OnEvent( (CAniObj*)m_pGameObj, m_iCurIndex );
		
		if( iIndex >= (int)m_mapAniDirection[pAniObj->GetDirection()].size() )
		{
				if( m_bLoop )
					SetAniIndex( 0 );
				else
					return false;
		}
		else
		{
			SetAniIndex( iIndex );
		}
	}
	return true;
}

void CDirectionAniRender::UpdateWorld()//DirectionAniRender update
{
	D3DXMATRIX matLocal;
	MakeLocal( matLocal );

	D3DXMATRIX matRot;
	MakeRot( matRot );

	D3DXMATRIX matTrans;
	MakeTrans( matTrans );

	D3DXMATRIX matScale;
	MakeScale( matScale );

	m_matWorld = matLocal * matRot * matScale * matTrans;
	m_matWorld._43 = 0.0f;
} 

void CDirectionAniRender::OnFrameRender()//Frame Rendering
{
	if( m_pGameObj == NULL )
		return ;

	if( m_iCurIndex < 0 || m_iCurIndex >= (int)m_mapAniDirection[pAniObj->GetDirection()].size() )
		return ;

	D3DXMATRIX matView;
	D3DXMatrixIdentity( &matView );
	g_pCamera->GetTransform( &matView );

	D3DXMATRIX matWorld = m_matWorld * matView;

	g_pSprite->SetTransform( &matWorld );
	g_pSprite->OnDraw( g_pTexture->GetTexture( (int)m_mapAniDirection[pAniObj->GetDirection()][ m_iCurIndex ] ), NULL, 0.0f, 0.0f );
}

void CDirectionAniRender::MakeLocal( D3DXMATRIX &matTrans )//local 설정
{
	D3DXMatrixIdentity( &matTrans );

	if( m_iCurIndex < 0 || m_iCurIndex >= (int)m_mapAniDirection[pAniObj->GetDirection()].size() )
		return ;

	const STextureInfo* pTextureInfo = g_pTexture->GetTextureInfo( (int)m_mapAniDirection[pAniObj->GetDirection()][ m_iCurIndex ]  );
	if( pTextureInfo == NULL )
		return ;

	matTrans._41 -= ( pTextureInfo->m_TextureInfo.Width * 0.5f );
	matTrans._42 -= ( pTextureInfo->m_TextureInfo.Height * 1.0f );

	m_pGameObj->SetImgSize(
	D3DXVECTOR2( 	
	(float)pTextureInfo->m_TextureInfo.Width
		,(float)pTextureInfo->m_TextureInfo.Height ));
}

void CDirectionAniRender::SetAniIndex( int iIndex )//Ani index 설정
{
	m_iCurIndex = iIndex;
	m_fTrackTime = 0.0f;
}