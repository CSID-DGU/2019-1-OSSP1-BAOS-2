#include "DXUT.h"
#include "Home.h"

CSprite::CSprite(void):
m_pSprite( NULL )
{
}


CSprite::~CSprite(void)
{
	SAFE_DELETE( m_pSprite );
}

void CSprite::OnResetDevice()
{
	D3DXCreateSprite( DXUTGetD3D9Device(), &m_pSprite );
}

void CSprite::OnLostDevice()
{
	SAFE_RELEASE( m_pSprite );
}

void CSprite::OnBegin()
{
	if( m_pSprite == NULL )
		return ;

	m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );
}

void CSprite::OnEnd()
{
	if( m_pSprite == NULL )
		return ;

	m_pSprite->End();
}

void CSprite::SetTransform( D3DXMATRIX *pmatTrans )
{
	if( m_pSprite == NULL )
		return ;

	m_pSprite->SetTransform( pmatTrans );
}

void CSprite::OnDraw( LPDIRECT3DTEXTURE9 pTexture
	, const RECT * pRect
	, float fX
	, float fY )
{
	D3DXVECTOR3 vPos( fX, fY, 0.0f );
	m_pSprite->Draw( pTexture, pRect, &vPos, NULL, 0xffffffff );
}