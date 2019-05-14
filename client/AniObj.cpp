#include "DXUT.h"
#include "Home.h"

extern CGameObjPool * g_pGameObjPool;

CAniObj::CAniObj(void):
	m_iAniCategory( -1 ),
	m_iInputIndex( -1 ),
	m_iChangeIndex( -1 ),
	m_iNextAniCategory( -1 ),
	m_pController( NULL ),
	m_bChangeNextAni( false )
{
}


CAniObj::~CAniObj(void)
{
	UnLoad();
}

void CAniObj::Load( wstring wFile )
{
	if( m_mapAniRender.empty() == false )
		return ;

	// GameObjPool에서 애니메이션 관련 데이터를 wfile에서 받아온다.
	// 값을 변경하지 않을 예정이므로 const 처리 해주는 것 잊지말기.
	const SAniObjData* pObjData = g_pGameObjPool->GetAniObjData( wFile );	
	if( pObjData == NULL )
		return ;

	SetScl( D3DXVECTOR2( pObjData->m_vScale ));	
	// ini파일에 저장되어있는 애니메이션 정보들을 모두 읽어 초기화한다.
	m_iMaxHealth = pObjData->m_iMaxHealth;	// 최대 체력을 받아온다.
	m_iHealth = pObjData->m_iHealth;		// 현재 체력을 받아온다.

	m_iDamage = pObjData->m_iDamage;		// 데미지를 받아온다.
	m_fSpeed = pObjData->m_fSpeed;			// 이동속도를 받아온다

	m_iScope = pObjData->m_iScope;			// 공격범위를 받아온다.	
	m_iRadius = pObjData->m_iRadius;

	map< int, SAniData >::const_iterator mit = pObjData->m_mapAni.begin();
	for( mit; mit != pObjData->m_mapAni.end(); ++mit )
	{
		if( mit->second.m_wFile.empty() )
			continue;

		CRender* pRender;

		switch( m_iRenderType )				// 애니메이션 타입에 맞게 Rendering 해준다.
		{
		case ERENDER_NORMAL:
			{
				pRender =new CAniRender( this );
				break; 
			}
		case ERENDER_DIRECTION: 
			{
				pRender = new CDirectionAniRender( this );
				break;
			}
		case ERENDER_UI:
			{
				pRender = new CUIAniRender( this );
				break ;
			}
		}

		pRender->Load( mit->second.m_wFile );
		m_mapAniRender.insert( make_pair( mit->first, pRender ));
	}
}

void CAniObj::UnLoad()
{
	m_pRender = NULL;

	map< int, CRender* >::iterator mit = m_mapAniRender.begin();
	for( mit; mit != m_mapAniRender.end(); ++mit )
		SAFE_DELETE( mit->second );

	if( m_pController != NULL )
		SAFE_DELETE( m_pController );

	m_mapAniRender.clear();
}

void CAniObj::OnFrameMove( float fElapsedTime )
{
	if( m_pRender == NULL )
		return ;

	if( m_pController != NULL )
		m_pController->OnFrameMove( fElapsedTime );

	if( m_pRender->OnFrameMove( fElapsedTime ) == false )
		OnEndAni();

	if( m_bChangeNextAni )
	{
		if( (( CDirectionAniRender* ) m_pRender )->GetAniIndex() >= m_iChangeIndex )
			OnChangeAni( m_iNextAniCategory );
	}
}

void CAniObj::OnEndAni()
{
	if( m_pController != NULL )
		m_pController->OnEndAni( m_iAniCategory );
}

void CAniObj::OnFrameRender()
{
	if( m_pRender == NULL )
		return ;

	m_pRender->OnFrameRender();
}

void CAniObj::OnChangeAni( int iAni )
{
	map< int, CRender* >::iterator mit = m_mapAniRender.find( iAni );
	if( mit == m_mapAniRender.end() )
	{
		Destroy();
		return ;
	}

	m_iInputIndex = -1;
	m_iChangeIndex = -1;
	m_iNextAniCategory = -1;

	m_iAniCategory = iAni;

	m_pRender = mit->second;
	((CDirectionAniRender*)m_pRender)->SetAniIndex( 0 );

	m_pRender->UpdateWorld();

	if( m_pController != NULL )
		m_pController->OnChangeAni( iAni );

}

void CAniObj::SetNextAni( int iInputIndex, int iChangeIndex, int iAniCategory )
{
	m_iInputIndex = iInputIndex;
	m_iChangeIndex = iChangeIndex;
	m_iAniCategory = iAniCategory;
}

void CAniObj::TryNextAni()
{
	if( m_iNextAniCategory == NULL )
		return ;

	if( ((CDirectionAniRender*)m_pRender)->GetAniIndex() < m_iInputIndex )
		return ;

	m_bChangeNextAni = true;
}