#include "DXUT.h"
#include "Home.h"

extern CTexture * g_pTexture;
extern CSprite * g_pSprite;

CUIImgRender::CUIImgRender( CGameObj * pGameObj ):		// �θ� Ŭ����(CRander)�� ���� ������ initialization
CRender( pGameObj ),
	m_pGameObj( pGameObj ),
m_iTexture( -1 )
{
}


CUIImgRender::~CUIImgRender(void)
{
	g_pTexture->ReserveRelease( m_iTexture );			// Release�� ���Ϳ� �߰�
}

void CUIImgRender::Load( wstring wFile )
{
	m_iTexture = g_pTexture->Load( wFile );	
	// UI ������Ʈ ��(e.g. MenuBackGround(1) etc��)�� �ش��ϴ� ������ �ε��Ѵ�.
}

bool CUIImgRender::OnFrameMove( float fElapsedTime )
{
	UpdateWorld();

	m_pGameObj->SetImgSize(								// UI ������Ʈ ����� �����ؼ� �����Ѵ�.
		D3DXVECTOR2( 									// UI ������Ʈ�� 2�����̴ϱ� �翬�� ����, ����
		(float)g_pTexture->GetTextureInfo(  (int)m_iTexture )->m_TextureInfo.Width
		,	(float)g_pTexture->GetTextureInfo(  (int)m_iTexture )->m_TextureInfo.Height ));

	return false;
}

void CUIImgRender::UpdateWorld()
{
	D3DXMATRIX matRot;
	MakeRot( matRot );			// ������ 4 �̻��̸� �¿� �����ϰ� �����̸� ��Ʈ���� �����Ѵ�.

	D3DXMATRIX matTrans;
	MakeTrans( matTrans );		// ������� ��Ʈ������ ��ǥ�� �����Ѵ�.

	D3DXMATRIX matScale;
	MakeScale( matScale );		// ������� ��Ʈ������ UI ������Ʈ�� ũ�������� �����Ѵ�.

	m_matWorld = matRot * matScale * matTrans;
	m_matWorld._43 = 0.0f;		// ���� ����
}

void CUIImgRender::OnFrameRender()
{
	if( m_pGameObj == NULL )	// �ҷ��°� ���ٸ� OUT
		return ;
								// �ҷ��°� �ִٸ� UI ���Ķ���Ʈ�� �Ѹ���.
	g_pSprite->SetTransform( &m_matWorld );
	g_pSprite->OnDraw( g_pTexture->GetTexture( m_iTexture ), NULL, 0.0f, 0.0f );
}
