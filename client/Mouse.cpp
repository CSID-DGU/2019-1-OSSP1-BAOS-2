#include "DXUT.h"
#include "Home.h"

extern CCamera* g_pCamera;

CMouse::CMouse(void)://cmouse ���� �� �ʱ�ȭ
	m_vRMousePos( NULLVECTOR2),
	m_vLMousePos( NULLVECTOR2),
	m_vOneRMousePos( NULLVECTOR2 ),
	m_vOneLMousePos( NULLVECTOR2 ),
	m_vMousePos( 0.0f, 0.0f ),
	m_vWorldMousePos( NULLVECTOR2),
	m_fLMouseTime( 0.0f ),
	m_fRMouseTime( 0.0f ),
	m_bRClick( false ),
	m_bLClick( false ),
	m_bOneRClick( false ),
	m_bOneLClick( false )
{
}


CMouse::~CMouse(void)
{
}

void CMouse::OnFrameMove( float fElapsedTime )
{//�ǽð����� ���콺�� ��ġ�� �������ش�.
	SetMousePos();
	SetWorldMousePos();
	SetLMousePos( fElapsedTime );
	SetRMousePos( fElapsedTime );
}

void CMouse::SetMousePos()//���콺 ��ġ ����
{
	POINT ptMouse;
	GetCursorPos( &ptMouse );
	ScreenToClient( DXUTGetHWND(), &ptMouse );

	m_vMousePos = D3DXVECTOR2( (float)ptMouse.x, (float)ptMouse.y );
}

void CMouse::SetWorldMousePos()//���� ���콺 ��ġ����
{
	m_vWorldMousePos = m_vMousePos;	
	//���� ���콺�� x��ǥ�� y��ǥ�� ī�޶��� ��ǥ��ŭ ����
	//��ǻ� ī�޶��� ��ġ
	m_vWorldMousePos.x += ( g_pCamera->GetCameraPos().x  - (  g_pCamera->GetWidth() * 0.5f ) );
	m_vWorldMousePos.y += ( g_pCamera->GetCameraPos().y  - (  g_pCamera->GetHeight() * 0.5f ) );
}


void CMouse::SetRMousePos( float fElapsedTime )//������ ���콺��ġ ����
{
	m_vOneRMousePos = NULLVECTOR2;				//���콺 ��ǥ �ʱ�ȭ
	m_bOneRClick = false;						//Ŭ���ߴ��� �˻縦 ���� bool�ڷ���

	m_fLMouseTime += fElapsedTime;

	if( m_fRMouseTime > 4 * fElapsedTime  )		//Ŭ�� �ð��� ������ �ð����� �� ���
	{
		//���콺 �ʱ�ȭ
		m_bRClick = false;
		m_vRMousePos = NULLVECTOR2;
		m_fRMouseTime = 0;
	}

	if( KEYDOWN( VK_RBUTTON ) )			// ���� Ű �ڵ� - Ŭ���� �����Ѱ��
	{
		m_vRMousePos = m_vWorldMousePos;// ���콺 ��ġ�� ���帶�콺��ġ�� ����
		m_fRMouseTime = 0;
		m_bRClick = true;				// Ŭ���� ��Ȳ
	}

	if( KEYDOWN( VK_RBUTTON ) == false )// ���� Ű �ڵ� - Ŭ���� �����Ѱ��
	{
		if( m_bRClick == true )			// Ŭ���� ���
		{
			m_bRClick = false;			
			m_bOneRClick = true;

			m_vOneRMousePos = m_vRMousePos;
		}
	}
}

void CMouse::SetLMousePos( float fElapsedTime )//�� �ڵ�� ���������� ���� ���콺 ��ġ ����
{
	m_vOneLMousePos = NULLVECTOR2;
	m_bOneLClick = false;

	m_fLMouseTime += fElapsedTime;

	if( m_fLMouseTime > 4 * fElapsedTime )
	{
			m_bLClick = false;
			m_vLMousePos = NULLVECTOR2;
			m_fLMouseTime = 0;
	}

	if( KEYDOWN( VK_LBUTTON ) )
	{
		m_vLMousePos = m_vWorldMousePos;
		m_fLMouseTime = 0;
		m_bLClick = true;
	}

	if( KEYDOWN( VK_LBUTTON ) == false )
	{
		if( m_bLClick == true )
		{
			m_bLClick = false;
			m_bOneLClick = true;

			m_vOneLMousePos = m_vLMousePos;
		}
	}
}