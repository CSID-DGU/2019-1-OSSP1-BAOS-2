#include "DXUT.h"
#include "Home.h"

extern CMouse* g_pMouse;
extern CGameObjPool* g_pGameObjPool;
extern CUIMgr* g_pUIMgr;

CUI::CUI(void):
m_bUse( false ),
	m_bAni( false ),
	m_iUIType( -1 ),
	m_pObj( NULL )
{
}


CUI::~CUI(void)
{
}

void CUI::Load( wstring wFile )		
{
	if( m_bAni )
	{
		__super::Load( wFile );			// CAniObj의 Load 함수를 의미한다. __super = 부모 클래스

		OnChangeAni( AT_NORMAL );		// NORMAL Animation type임을 명시해준다.
		
	}
	else
	{
		if( m_pRender != NULL )
			return ;
										// 오브젝트 정보를 받아서 ObjData에 저장한다
		const SObjData* pObjData = g_pGameObjPool->GetObjData( wFile );
		if( pObjData == NULL )
			return ;
	
		m_pRender = new CUIImgRender( this );
		m_pRender->Load( pObjData->m_wFile );
	}
}

void CUI::OnFrameMove( float fElapsedTime )
{
	__super::OnFrameMove( fElapsedTime );

	if( CUtil::UIObject_Mouse_Collision( this, g_pMouse->GetOneLMousePos() ) )
		g_pUIMgr->WorkUIMessage( m_iUIType );

	g_pUIMgr->AutoMessage( m_iUIType, this );
}