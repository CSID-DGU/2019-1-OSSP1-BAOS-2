#include "DXUT.h"
#include "Home.h"

extern CCamera* g_pCamera;

CMouse::CMouse(void):
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
{
	SetMousePos();
	SetWorldMousePos();
	SetLMousePos( fElapsedTime );
	SetRMousePos( fElapsedTime );
}

void CMouse::SetMousePos()
{
	POINT ptMouse;
	GetCursorPos( &ptMouse );
	ScreenToClient( DXUTGetHWND(), &ptMouse );

	m_vMousePos = D3DXVECTOR2( (float)ptMouse.x, (float)ptMouse.y );
}

void CMouse::SetWorldMousePos()
{
	m_vWorldMousePos = m_vMousePos;
	m_vWorldMousePos.x += ( g_pCamera->GetCameraPos().x  - (  g_pCamera->GetWidth() * 0.5f ) );
	m_vWorldMousePos.y += ( g_pCamera->GetCameraPos().y  - (  g_pCamera->GetHeight() * 0.5f ) );
}


void CMouse::SetRMousePos( float fElapsedTime )
{
	m_vOneRMousePos = NULLVECTOR2;
	m_bOneRClick = false;

	m_fLMouseTime += fElapsedTime;

	if( m_fRMouseTime > 4 * fElapsedTime  )
	{
			m_bRClick = false;
			m_vRMousePos = NULLVECTOR2;
			m_fRMouseTime = 0;
	}

	if( KEYDOWN( VK_RBUTTON ) )
	{
		m_vRMousePos = m_vWorldMousePos;
		m_fRMouseTime = 0;
		m_bRClick = true;
	}

	if( KEYDOWN( VK_RBUTTON ) == false )
	{
		if( m_bRClick == true )
		{
			m_bRClick = false;
			m_bOneRClick = true;

			m_vOneRMousePos = m_vRMousePos;
		}
	}
}

void CMouse::SetLMousePos( float fElapsedTime )
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