#include "DXUT.h"
#include "Home.h"

extern CGameObjPool* g_pGameObjPool;

CHealth::CHealth(void)
{
}


CHealth::~CHealth(void)
{
}

void CHealth::Load( wstring wFile )
{
	if( m_pRender != NULL )
		return ;

	const SObjData* pObjData = g_pGameObjPool->GetObjData( wFile );
	if( pObjData == NULL )
		return ;
	
	/*m_pRender = new CImgRender( this );
	m_pRender->Load( pObjData->m_wFile );*/
}

void CHealth::OnFrameMove( float fElapsedTime )
{
	__super::OnFrameMove( fElapsedTime );

	if( m_pPlayer != NULL )
	{

		if( m_pPlayer->IsDestroy() )
		{
			Destroy();
			m_vScl.x = 0.0f;
			return ;
		}

		m_vPos = *m_pPlayer->GetPos();
		m_vPos -= D3DXVECTOR2( 22.5, 0 );

		
		if( m_pPlayer->GetHealth() == m_pPlayer->GetMaxHealth() )
			return ;

		if( m_pPlayer->GetHealth() <= 0 )
		{
			m_vScl.x = 0.0f;
			return ;
		}

		m_vScl.x = 1.0f - ( ( m_pPlayer->GetMaxHealth() / m_pPlayer->GetHealth() ) * 0.1f );
	}
}