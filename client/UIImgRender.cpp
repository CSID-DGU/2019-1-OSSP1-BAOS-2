#include "DXUT.h"
#include "Home.h"

extern CTexture * g_pTexture;
extern CSprite * g_pSprite;

CUIImgRender::CUIImgRender( CGameObj * pGameObj ):		// 부모 클래스(CRander)를 통해 생성자 initialization
CRender( pGameObj ),
	m_pGameObj( pGameObj ),
m_iTexture( -1 )
{
}


CUIImgRender::~CUIImgRender(void)
{
	g_pTexture->ReserveRelease( m_iTexture );			// Release용 벡터에 추가
}

void CUIImgRender::Load( wstring wFile )
{
	m_iTexture = g_pTexture->Load( wFile );	
	// UI 오브젝트 명(e.g. MenuBackGround(1) etc…)에 해당하는 파일을 로드한다.
}

bool CUIImgRender::OnFrameMove( float fElapsedTime )
{
	UpdateWorld();

	m_pGameObj->SetImgSize(								// UI 오브젝트 사이즈를 측정해서 세팅한다.
		D3DXVECTOR2( 									// UI 오브젝트는 2차원이니까 당연히 가로, 세로
		(float)g_pTexture->GetTextureInfo(  (int)m_iTexture )->m_TextureInfo.Width
		,	(float)g_pTexture->GetTextureInfo(  (int)m_iTexture )->m_TextureInfo.Height ));

	return false;
}

void CUIImgRender::UpdateWorld()
{
	D3DXMATRIX matRot;
	MakeRot( matRot );			// 방향이 4 이상이면 좌우 반전하고 정상이면 매트릭스 생성한다.

	D3DXMATRIX matTrans;
	MakeTrans( matTrans );		// 만들어진 매트릭스에 좌표를 삽입한다.

	D3DXMATRIX matScale;
	MakeScale( matScale );		// 만들어진 매트릭스에 UI 오브젝트의 크기정보를 삽입한다.

	m_matWorld = matRot * matScale * matTrans;
	m_matWorld._43 = 0.0f;		// 공간 생성
}

void CUIImgRender::OnFrameRender()
{
	if( m_pGameObj == NULL )	// 불러온게 없다면 OUT
		return ;
								// 불러온게 있다면 UI 스파라이트를 뿌린다.
	g_pSprite->SetTransform( &m_matWorld );
	g_pSprite->OnDraw( g_pTexture->GetTexture( m_iTexture ), NULL, 0.0f, 0.0f );
}
