#include "DXUT.h"
#include "Home.h"

extern CCamera* g_pCamera;

CMouse::CMouse(void)://cmouse 생성 및 초기화
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
{//실시간으로 마우스의 위치를 갱신해준다.
	SetMousePos();
	SetWorldMousePos();
	SetLMousePos( fElapsedTime );
	SetRMousePos( fElapsedTime );
}

void CMouse::SetMousePos()//마우스 위치 설정
{
	POINT ptMouse;
	GetCursorPos( &ptMouse );
	ScreenToClient( DXUTGetHWND(), &ptMouse );

	m_vMousePos = D3DXVECTOR2( (float)ptMouse.x, (float)ptMouse.y );
}

void CMouse::SetWorldMousePos()//월드 마우스 위치설정
{
	m_vWorldMousePos = m_vMousePos;	
	//월드 마우스의 x좌표와 y좌표를 카메라의 좌표만큼 변경
	//사실상 카메라의 위치
	m_vWorldMousePos.x += ( g_pCamera->GetCameraPos().x  - (  g_pCamera->GetWidth() * 0.5f ) );
	m_vWorldMousePos.y += ( g_pCamera->GetCameraPos().y  - (  g_pCamera->GetHeight() * 0.5f ) );
}


void CMouse::SetRMousePos( float fElapsedTime )//오른족 마우스위치 설정
{
	m_vOneRMousePos = NULLVECTOR2;				//마우스 좌표 초기화
	m_bOneRClick = false;						//클릭했는지 검사를 위한 bool자료형

	m_fLMouseTime += fElapsedTime;

	if( m_fRMouseTime > 4 * fElapsedTime  )		//클릭 시간이 설정한 시간보다 길 경우
	{
		//마우스 초기화
		m_bRClick = false;
		m_vRMousePos = NULLVECTOR2;
		m_fRMouseTime = 0;
	}

	if( KEYDOWN( VK_RBUTTON ) )			// 가상 키 코드 - 클릭이 성공한경우
	{
		m_vRMousePos = m_vWorldMousePos;// 마우스 위치를 월드마우스위치로 설정
		m_fRMouseTime = 0;
		m_bRClick = true;				// 클릭한 상황
	}

	if( KEYDOWN( VK_RBUTTON ) == false )// 가상 키 코드 - 클릭이 실패한경우
	{
		if( m_bRClick == true )			// 클릭한 경우
		{
			m_bRClick = false;			
			m_bOneRClick = true;

			m_vOneRMousePos = m_vRMousePos;
		}
	}
}

void CMouse::SetLMousePos( float fElapsedTime )//위 코드와 마찬가지로 왼쪽 마우스 위치 설정
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