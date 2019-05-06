#include "DXUT.h"
#include "Home.h"

extern CGameObjPool* g_pGameObjPool;


CTile::CTile(void)
{
}


CTile::~CTile(void)
{
}

void CTile::Load( wstring wFile )
{
	if( m_pRender != NULL )
		return ;

	const SObjData* pObjData = g_pGameObjPool->GetObjData( wFile );
	if( pObjData == NULL )
		return ;
	
	/*m_pRender = new CImgRender( this );
	m_pRender->Load( pObjData->m_wFile );*/
}