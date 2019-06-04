#include "DXUT.h"
#include "Home.h"

extern GameDataMgr * g_pGameDataMgr;

CAniObj::CAniObj(void)://게임 오브젝트 생성 및 초기화
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

void CAniObj::Load( wstring wFile )//wFile Load
{
	if( m_mapAniRender.empty() == false )//aniRender가 비어있을 경우 종료
		return ;

	const SAniObjData* pObjData = g_pGameDataMgr->GetAniObjData( wFile );
	if( pObjData == NULL )
		return ;


	SetScl( D3DXVECTOR2( pObjData->m_vScale ));//데이터 오브젝트의 스케일 설정

	//오브젝트 데이터의 최대체력, 체력, 데미지 상태, 스피드, 범위, 반지름 설정
	m_iMaxHealth = pObjData->m_iMaxHealth;
	m_iHealth = pObjData->m_iHealth;

	m_iDamage = pObjData->m_iDamage;
	m_fSpeed = pObjData->m_fSpeed;

	m_iScope = pObjData->m_iScope;
	m_iRadius = pObjData->m_iRadius;

	map< int, SAniData >::const_iterator mit = pObjData->m_mapAni.begin();//오브젝트 데이터 이터레이터 설정
	for( mit; mit != pObjData->m_mapAni.end(); ++mit )//오브젝트 데이트만큼 반복
	{
		if( mit->second.m_wFile.empty() )//비어있을 경우 지나감
			continue;

		CRender* pRender;

		switch( m_iRenderType )//타입에 따라 렌더링해줌 
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

void CAniObj::UnLoad()//로드 해제
{
	m_pRender = NULL;

	//Map에 저장되어 있는 AniRender들을 전부 안전하게 제거
	map< int, CRender* >::iterator mit = m_mapAniRender.begin();
	for( mit; mit != m_mapAniRender.end(); ++mit )
		SAFE_DELETE( mit->second );//안전하게 제거

	if( m_pController != NULL )//컨트롤러도 제거한다.
		SAFE_DELETE( m_pController );

	m_mapAniRender.clear();
}

void CAniObj::OnFrameMove( float fElapsedTime )//실시간으로 프레임 갱신
{
	if( m_pRender == NULL )
		return ;

	if( m_pController != NULL )
		m_pController->OnFrameMove( fElapsedTime );

	if( m_pRender->OnFrameMove( fElapsedTime ) == false )
		OnEndAni();

	if( m_bChangeNextAni )//다음 애니메이션으로 전환
	{
		if( (( CDirectionAniRender* ) m_pRender )->GetAniIndex() >= m_iChangeIndex )
			OnChangeAni( m_iNextAniCategory );
	}
}

void CAniObj::OnEndAni()//Ani 종료
{
	if( m_pController != NULL )
		m_pController->OnEndAni( m_iAniCategory );
}

void CAniObj::OnFrameRender()//Frame Rendering
{
	if( m_pRender == NULL )
		return ;

	m_pRender->OnFrameRender();//프레임 렌더링
}

void CAniObj::OnChangeAni( int iAni )//Ani 전환
{
	map< int, CRender* >::iterator mit = m_mapAniRender.find( iAni );//iAni에 찾아서 iterator 설정
	if( mit == m_mapAniRender.end() )//찾지 못했을 경우
	{
		Destroy();
		return ;
	}

	//애니 전환 준비과정, 초기화
	m_iInputIndex = -1;
	m_iChangeIndex = -1;
	m_iNextAniCategory = -1;

	//애니 카테코리 재설정
	m_iAniCategory = iAni;

	m_pRender = mit->second;
	((CDirectionAniRender*)m_pRender)->SetAniIndex( 0 );

	m_pRender->UpdateWorld();//게임 다시 갱신

	if( m_pController != NULL )//컨트롤러 애니 전환
		m_pController->OnChangeAni( iAni );

}

void CAniObj::SetNextAni( int iInputIndex, int iChangeIndex, int iAniCategory )//다음 애니 설정
{
	//받아온 인수들로 index와 카테코리 설정
	m_iInputIndex = iInputIndex;
	m_iChangeIndex = iChangeIndex;
	m_iAniCategory = iAniCategory;
}

void CAniObj::TryNextAni()//다음 애니메이션으로 전환시도
{
	if( m_iNextAniCategory == NULL )//다음 애니 카테고리가 없을경우 종료
		return ;

	if( ((CDirectionAniRender*)m_pRender)->GetAniIndex() < m_iInputIndex )//받은 index가 가지고 있는 애니 인덱스보다 클경우
		return ;

	m_bChangeNextAni = true;//전환성공확인용 bool 자료형
}