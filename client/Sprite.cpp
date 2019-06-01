#include "DXUT.h"
#include "Home.h"


CSprite::CSprite(void)://스프라이트 생성
m_pSprite( NULL )
{
}


CSprite::~CSprite(void)
{
	SAFE_DELETE( m_pSprite );//스프라이트 소멸
}

void CSprite::OnResetDevice()
{
	D3DXCreateSprite( DXUTGetD3D9Device(), &m_pSprite );//directx 스프라이트 다시 생성
}

void CSprite::OnLostDevice()
{
	SAFE_RELEASE( m_pSprite );//스프라이트를 놓아준다.
}

void CSprite::OnBegin()
{
	if( m_pSprite == NULL )//스프라이트가 NULL일때 그냥 리턴
		return ;

	m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );//directx sprite지원
}

void CSprite::OnEnd()
{
	if( m_pSprite == NULL )//스프라이트가 NULL일 때 return
		return ;

	m_pSprite->End();//directx 스프라이트 종료
}

void CSprite::SetTransform( D3DXMATRIX *pmatTrans )
{
	if( m_pSprite == NULL )//스프라이트가 NULL일 때 return
		return ;

	m_pSprite->SetTransform( pmatTrans ); //pmatTrans로 스프라이트 전환 
	//프로그램의 종료로 스프라이트가 사라질 때까지 무한루프
}

void CSprite::OnDraw( LPDIRECT3DTEXTURE9 pTexture // 스프라이트 그려주기
	, const RECT * pRect						  //텍스처와 그 영역을 받아준다.
	, float fX
	, float fY )
{
	D3DXVECTOR3 vPos( fX, fY, 0.0f );//vpos 위치 설정
	m_pSprite->Draw( pTexture, pRect, &vPos, NULL, 0xffffffff );
	//vpos위치에 텍스쳐를 그려준다.
}