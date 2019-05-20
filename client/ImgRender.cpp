#include "DXUT.h"
#include "Home.h"

extern CTexture * g_pTexture;
extern CSprite * g_pSprite;
extern CCamera* g_pCamera;

CImgRender::CImgRender( CGameObj * pGameObj ):
CRender( pGameObj ),
m_iTexture( -1 )
{
}


CImgRender::~CImgRender(void)
{
	g_pTexture->ReserveRelease( m_iTexture );
}

void CImgRender::Load( wstring wFile )
{
	m_iTexture = g_pTexture->Load( wFile );
}

bool CImgRender::OnFrameMove( float fElapsedTime )
{
	UpdateWorld();

	return false;
}

void CImgRender::UpdateWorld()
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

void CImgRender::OnFrameRender()
{
	if( m_pGameObj == NULL )
		return ;

	D3DXMATRIX matView;
	D3DXMatrixIdentity( &matView );
	g_pCamera->GetTransform( &matView );

	D3DXMATRIX matWorld = m_matWorld * matView;
	matWorld._43 = 0.0f;

	g_pSprite->SetTransform( &matWorld );
	g_pSprite->OnDraw( g_pTexture->GetTexture( m_iTexture ), NULL, 0.0f, 0.0f );
}

void CImgRender::SetDarkMode( D3DXVECTOR2 vPos, int iTexture )
{
	const STextureInfo * SViewInfo = g_pTexture->GetTextureInfo( iTexture );	
	const STextureInfo* SDarkInfo = g_pTexture->GetTextureInfo( m_iTexture );

	DWORD* pViewColor = g_pTexture->GetImgColorBits( iTexture);
	DWORD* pDarkColor = g_pTexture->GetImgColorBits( m_iTexture );

	MakeAlpha( pDarkColor, pViewColor, vPos, SDarkInfo, SViewInfo );
}