#include "DXUT.h"
#include "Home.h"

extern CTexture* g_pTexture;
extern CGameTileMgr* g_pGameTileMgr;

CGameObjContainer::CGameObjContainer(void)
{
	m_setPlayObj.insert( EGAMEOBJ_PLAYER ), m_setPlayObj.insert( EGAMEOBJ_CREATURE ), m_setPlayObj.insert( EGAMEOBJ_TOWER );
}


CGameObjContainer::~CGameObjContainer(void)
{
	for each( map< int, vector< CGameObj* >>::const_reference mr in m_mapObj )
		for each( vector<CGameObj*>::const_reference vr in mr.second )
				delete vr;

	m_mapObj.clear();
}

CUI* CGameObjContainer::UILoad( int iUIType, wstring wFile, wstring wName, D3DXVECTOR2 vPos, bool bAni, bool bWork  )
{
	CUI* pUIObj = new CUI;
	if( pUIObj == NULL )
		return NULL;

	pUIObj->SetPos( vPos );
	pUIObj->SetAni( bAni );
	pUIObj->SetRenderType( ERENDER_UI );
	pUIObj->Load( wFile );
	pUIObj->SetObjName( wName );
	pUIObj->SetType( iUIType );
	pUIObj->SetWork( bWork );

	m_mapReserveObj[ EGAMEOBJ_UI ].push_back( pUIObj );

	return pUIObj;
}

CGameObj* CGameObjContainer::Load( int iType, int iTeam, wstring wFile, wstring wName, D3DXVECTOR2 vPos, int iDirection, int iRenderType , bool bWork )
{
	CGameObj* pObj = Alloc( iType );
	if( pObj == NULL )
		return NULL;
	
	pObj->SetPos( vPos );
	pObj->SetRenderType( iRenderType );
	pObj->SetTeam( iTeam );
	pObj->SetObjName( wName );
	pObj->Load( wFile );
	pObj->SetDirection( iDirection );
	pObj->SetWork( bWork );


	if( pObj->IsWork() == false )
	{
		m_mapUnWorkObj[iType].push_back( pObj );
		return pObj;
	}

	m_mapReserveObj[ iType ].push_back( pObj );
	return pObj;
}

void CGameObjContainer::SetWork( int iType, wstring wName, bool bWork  )
{
	for each( vector< CGameObj* >::const_reference vr in m_mapUnWorkObj[iType] )
	{
		if( vr->GetObjName() == wName )
			vr->SetWork( bWork );
	}
}

void CGameObjContainer::Destroy( int iType, wstring wName )
{
	for each( vector< CGameObj* >::const_reference vr in m_mapObj[iType] )
	{
		if( vr->GetObjName() == wName )
			vr->Destroy();
	}
}


void CGameObjContainer::PostProcess()
{
	map< int, vector< CGameObj* >>::iterator mitWork = m_mapUnWorkObj.begin();
	while( mitWork != m_mapUnWorkObj.end() )
	{
		for( int i = (int)mitWork->second.size() -1; i >= 0; -- i )
		{
			if( mitWork->second[i]->IsWork() == false )
				continue ;

			m_mapReserveObj[mitWork->first].push_back( mitWork->second[i] );
			mitWork->second.erase( mitWork->second.begin()+i );
		}

		if( mitWork->second.empty() )
			mitWork = m_mapUnWorkObj.erase( mitWork );
		else
			++mitWork;
	}

	// 예약된것을을 m_mapObj에 등록한다.
	for each( map<int, vector<CGameObj*>>::const_reference mr in m_mapReserveObj )
	{
		vector<CGameObj*>& vecObj = m_mapObj[mr.first];
		vecObj.insert( vecObj.end(), mr.second.begin(), mr.second.end() );
	}

	m_mapReserveObj.clear();

	// 삭제될것을 처리
	map<int, vector<CGameObj*>>::iterator mit = m_mapObj.begin();
	while( mit != m_mapObj.end() )
	{
		for( int i = (int)mit->second.size()-1; i >= 0; --i )
		{
			if( mit->second[i]->IsDestroy() == false )
				continue;

			SAFE_DELETE( mit->second[i] );
			mit->second.erase( mit->second.begin()+i );


 
		}

		if( mit->second.empty() )
			mit = m_mapObj.erase( mit );
		else
			++mit;
	}
}

CGameObj* CGameObjContainer::OnFindTarget( CGameObj* pGameObj, set< int >& setType, int fLimitDist )
{
	CGameObj* pTarget = NULL;
	int fMinDist = fLimitDist;

	for each( map< int, vector< CGameObj* >>::const_reference mr in m_mapObj )
	{
		if( setType.find( mr.first ) == setType.end() )
			continue ;

		for each( vector< CGameObj* >::const_reference vr in mr.second )
		{
			if( vr == pGameObj || vr->GetTeam() == pGameObj->GetTeam() )
				continue ;

			if((( CAniObj* )vr)->GetDirection() == AT_DIE && vr->IsDestroy() )
				continue ;
	
			float fDist = CUtil::CalcDist( pGameObj, vr );

			if( fMinDist > fDist )
			{
				fMinDist = (int)fDist;
				pTarget = vr;
			}
		}

	}

	return pTarget;
}

void CGameObjContainer::NoneOverLap( CGameObj* pGameObj )
{

	for each( map< int, vector< CGameObj* >>::const_reference mr in m_mapObj )
	{
		if( m_setPlayObj.find( mr.first ) == m_setPlayObj.end() )
			continue ;


		for each( vector< CGameObj* >::const_reference vr in mr.second )
		{	
			if( vr->IsDestroy() || pGameObj->IsDestroy() )
				continue;

			if( vr == pGameObj )
				continue ;

			if( (( CAniObj* )pGameObj)->GetDirection() == AT_DIE )
				continue ;
			
	
			D3DXVECTOR2 vToObject = *pGameObj->GetPos() - *vr->GetPos();
			float fDist = CUtil::CalcDist( pGameObj, vr );

			float fRadiusGap = pGameObj->GetRadius() + vr->GetRadius() - fDist;


			if( fRadiusGap >= 0.0f )
			{
				if( ((CAniObj*)pGameObj)->GetAniCategory() != AT_ATTACK )
					((CAniObj*)pGameObj)->GetController()->pEnemy = NULL;
							
				if( ((CAniObj*)vr)->GetAniCategory() != AT_ATTACK )
					((CAniObj*)vr)->GetController()->pEnemy = NULL;

				if( ((CAniObj*)pGameObj)->GetAniCategory() == AT_ATTACK )
				{
					(( CAniObj* )pGameObj)->GetController()->FindNode();
					return ;
				}
				else
				{
					//pGameObj->SetGoalPos( NULLVECTOR2 );
					//(( CAniObj* )pGameObj)->GetController()->FindNode();
				}
				
				if( fDist != 0 && vToObject != 0 )
					pGameObj->SetPos( *pGameObj->GetPos() +  ( vToObject / fDist ) * fRadiusGap );			
			}
		}
	}
}

void CGameObjContainer::SetRenderList()
{
	m_setRenderList.clear();
	m_mapRenderObj.clear();
	m_vecViewObj.clear();

	for each( map< int, vector< CGameObj* >>::const_reference mr in m_mapObj )
	{
		if( m_setPlayObj.find( mr.first ) == m_setPlayObj.end() )
			continue ;

		for each( vector< CGameObj* >::const_reference vr in mr.second )
		{
			m_mapRenderObj.insert( make_pair( vr->GetPos()->y, vr ));
			m_setRenderList.insert( vr->GetPos()->y );
			m_vecViewObj.push_back( vr );
		}
	}
}

