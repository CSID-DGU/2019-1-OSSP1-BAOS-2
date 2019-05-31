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

	if( KEYDOWN( VK_SHIFT ))		//Ű������ shiftŰ�� ���ȴ��� Ȯ��
		m_vPos = *m_pObj->GetPos(); //ī�޶������Ʈ�� ��ġ�� �޾� ī�޶� ����.
	else
		OnUpdateScreen( fElapsedTime );//ȭ�� �ǽð����� ����

	m_vPos.x = max( m_vPos.x, m_iWidth * 0.5f );	//0.5�� ���ؼ� ���� �߽� ����
	m_vPos.y = max( m_vPos.y, m_iHeight* 0.5f );	//���������� ���� �߽� ����

	m_vPos.x = min( m_vPos.x, 2048.f - ( m_iWidth * 0.5f ) );
	m_vPos.y = min( m_vPos.y, 2048.f - ( m_iHeight * 0.5f ) );
}

void CCamera::OnUpdateScreen( float fElapsedTime )
{
	D3DXVECTOR2 vMouse = g_pMouse->GetMousePos();//���콺 ��ġ�� �޾ƿ�
	
	//������ ���콺�� ȭ�� ���� ����ų ��� ī�޶� �̵���Ŵ
	if( vMouse.x <= m_iWidth * 0.01 )	//����
		m_vPos.x -= 800 * fElapsedTime;

	if( vMouse.y <= m_iHeight * 0.01 )	//����
		m_vPos.y -= 800 * fElapsedTime;

	if( vMouse.x >= m_iWidth * 0.99 )	//������
		m_vPos.x += 800 * fElapsedTime;

	if( vMouse.y >= m_iHeight *0.99 )	//�Ʒ���
		m_vPos.y += 800 * fElapsedTime;
}

void CCamera::GetTransform( D3DXMATRIX * pmatTrans )//ī�޶� ��ȯ
{
	//������ ���콺�� ȭ�� ���� ����ų ��� ī�޶� �̵���Ų��.
	pmatTrans->_41 = (float)m_iWidth * 0.5f  - m_vPos.x;	//0.5�� ���ؼ� ���� �߽� ����
	pmatTrans->_42 = (float)m_iHeight * 0.5f - m_vPos.y;	//0.5�� ���ؼ� ���� �߽� ����
	pmatTrans->_43 = 0.0f;
}