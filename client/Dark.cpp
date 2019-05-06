#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;
extern CGameObjPool* g_pGameObjPool;
extern CTexture* g_pTexture;

CDark::CDark(void):
m_iViewID( 0 )
{
}


CDark::~CDark(void)
{
}

void CDark::Load( wstring wFile )
{
	if( m_pRender != NULL )
		return ;

	const SObjData* pObjData = g_pGameObjPool->GetObjData( wFile );
	if( pObjData == NULL )
		return ;

	/*if( m_wObjName == L"Dark" )
	{
		m_vScl = pObjData->m_vScale;
		m_pRender = new CImgRender( this );
	}

	if( m_wObjName == L"MiniDark" )
	{
		m_vPos += D3DXVECTOR2( 768, 512 );
		m_vScl = m_vScl * 2;
		m_pRender = new CUIImgRender( this );
	}


	m_pRender->Load( pObjData->m_wFile );

	
	m_iViewID = g_pTexture->Load( L"Image/UI/View/CreatureView (0).png" );*/
}

void CDark::OnFrameMove( float fElapsedTime )
{
	/*if( m_pRender != NULL )
		m_pRender->OnFrameMove( fElapsedTime );


	vector< CGameObj* > m_vecViewObj = g_pGameObjMgr->GetViewObj();

	if( m_vecViewObj.empty() == false )
	{
		for( int i = 0; i <= (int)m_vecViewObj.size() - 1; ++ i )
		{
			if( m_vecViewObj[i]->IsDestroy() == false )
			{
				D3DXVECTOR2 vViewPos = *m_vecViewObj[i]->GetPos() / 16;

				m_pRender->SetDarkMode( vViewPos , m_iViewID );
			}
		}
	}*/
}