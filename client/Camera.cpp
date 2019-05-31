#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;

CCamera::CCamera(void):
m_pObj( NULL ),
	m_iWidth( 0 ),
	m_iHeight( 0 ),
	m_bUse( false ),
	m_vPos( 0.0f, 0.0f )
{
}


CCamera::~CCamera(void)
{
}

void CCamera::InitSize( int iWidth, int iHeight )
{
	m_iWidth = iWidth;
	m_iHeight = iHeight;

	m_vPos.x = m_iWidth * 0.5f;
	m_vPos.y = m_iHeight* 0.5f;
}

void CCamera::OnFrameMove( float fElapsedTime )
{

	if( KEYDOWN( VK_SHIFT ))		//키보드의 shift키가 눌렸는지 확인
		m_vPos = *m_pObj->GetPos(); //카메라오브젝트의 위치를 받아 카메라에 저장.
	else
		OnUpdateScreen( fElapsedTime );//화면 실시간으로 갱신

	m_vPos.x = max( m_vPos.x, m_iWidth * 0.5f );	//0.5씩 곱해서 가로 중심 유지
	m_vPos.y = max( m_vPos.y, m_iHeight* 0.5f );	//마찬가지로 세로 중심 유지

	m_vPos.x = min( m_vPos.x, 2048.f - ( m_iWidth * 0.5f ) );
	m_vPos.y = min( m_vPos.y, 2048.f - ( m_iHeight * 0.5f ) );
}

void CCamera::OnUpdateScreen( float fElapsedTime )
{
	D3DXVECTOR2 vMouse = g_pMouse->GetMousePos();//마우스 위치를 받아옴
	
	//유저의 마우스가 화면 밖을 가리킬 경우 카메라를 이동시킴
	if( vMouse.x <= m_iWidth * 0.01 )	//왼쪽
		m_vPos.x -= 800 * fElapsedTime;

	if( vMouse.y <= m_iHeight * 0.01 )	//위쪽
		m_vPos.y -= 800 * fElapsedTime;

	if( vMouse.x >= m_iWidth * 0.99 )	//오른쪽
		m_vPos.x += 800 * fElapsedTime;

	if( vMouse.y >= m_iHeight *0.99 )	//아래쪽
		m_vPos.y += 800 * fElapsedTime;
}

void CCamera::GetTransform( D3DXMATRIX * pmatTrans )//카메라 전환
{
	//유저의 마우스가 화면 밖을 가리킬 경우 카메라를 이동시킨다.
	pmatTrans->_41 = (float)m_iWidth * 0.5f  - m_vPos.x;	//0.5를 곱해서 가로 중심 유지
	pmatTrans->_42 = (float)m_iHeight * 0.5f - m_vPos.y;	//0.5를 곱해서 세로 중심 유지
	pmatTrans->_43 = 0.0f;
}