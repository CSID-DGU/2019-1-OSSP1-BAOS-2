#include "DXUT.h"
#include "Home.h"

extern GameDataMgr* g_pGameDataMgr;


CTile::CTile(void)
{
}


CTile::~CTile(void)
{
}

void CTile::Load( wstring wFile )//wFile ·Îµå
{
	if( m_pRender != NULL )
		return ;

	const SObjData* pObjData = g_pGameDataMgr->GetObjData( wFile );
	if( pObjData == NULL )
		return ;
	
	m_pRender = new CImgRender( this );
	m_pRender->Load( pObjData->m_wFile );
}