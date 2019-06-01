#include "DXUT.h"
#include "Home.h"


CSprite::CSprite(void)://��������Ʈ ����
m_pSprite( NULL )
{
}


CSprite::~CSprite(void)
{
	SAFE_DELETE( m_pSprite );//��������Ʈ �Ҹ�
}

void CSprite::OnResetDevice()
{
	D3DXCreateSprite( DXUTGetD3D9Device(), &m_pSprite );//directx ��������Ʈ �ٽ� ����
}

void CSprite::OnLostDevice()
{
	SAFE_RELEASE( m_pSprite );//��������Ʈ�� �����ش�.
}

void CSprite::OnBegin()
{
	if( m_pSprite == NULL )//��������Ʈ�� NULL�϶� �׳� ����
		return ;

	m_pSprite->Begin( D3DXSPRITE_ALPHABLEND );//directx sprite����
}

void CSprite::OnEnd()
{
	if( m_pSprite == NULL )//��������Ʈ�� NULL�� �� return
		return ;

	m_pSprite->End();//directx ��������Ʈ ����
}

void CSprite::SetTransform( D3DXMATRIX *pmatTrans )
{
	if( m_pSprite == NULL )//��������Ʈ�� NULL�� �� return
		return ;

	m_pSprite->SetTransform( pmatTrans ); //pmatTrans�� ��������Ʈ ��ȯ 
	//���α׷��� ����� ��������Ʈ�� ����� ������ ���ѷ���
}

void CSprite::OnDraw( LPDIRECT3DTEXTURE9 pTexture // ��������Ʈ �׷��ֱ�
	, const RECT * pRect						  //�ؽ�ó�� �� ������ �޾��ش�.
	, float fX
	, float fY )
{
	D3DXVECTOR3 vPos( fX, fY, 0.0f );//vpos ��ġ ����
	m_pSprite->Draw( pTexture, pRect, &vPos, NULL, 0xffffffff );
	//vpos��ġ�� �ؽ��ĸ� �׷��ش�.
}