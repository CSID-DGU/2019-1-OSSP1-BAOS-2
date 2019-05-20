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
		__super::Load( wFile );			// CAniObj�� Load �Լ��� �ǹ��Ѵ�. __super = �θ� Ŭ����

		OnChangeAni( AT_NORMAL );		// NORMAL Animation type���� ������ش�.
		
	}
	else
	{
		if( m_pRender != NULL )
			return ;
										// ������Ʈ ������ �޾Ƽ� ObjData�� �����Ѵ�
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