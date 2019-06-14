#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;
extern CGameTileMgr* g_pGameTileMgr;

CGameObjController::CGameObjController( CAniObj* pGameObj ):
	m_pGameObj( pGameObj ),//게임오브젝트 내용 저장하며 생성
	m_pEnemy( NULL ),
	m_vPath( NULLVECTOR2 )
{
}


CGameObjController::~CGameObjController(void)
{
}

void CGameObjController::FindNode()//노드 찾기
{	
	D3DXVECTOR2 vTargetIndex =  g_pGameTileMgr->FindTileIndex( *m_pGameObj->GetGoalPos() );	// 타겟 키값
	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex(  *m_pGameObj->GetPos() );	// 필레이어 키값

	m_vPath = NULLVECTOR2; // 초기화

	CPathFinder* pPathFinder = new CPathFinder;	// 길찾기 생성
	m_vPath = pPathFinder->FindPath( vPlayerIndex, vTargetIndex );	// 길찾기

	if( pPathFinder->bCanGoal == false )//길을 찾지 못했을 경우
	{
		m_pGameObj->SetGoalPos( *m_pGameObj->GetPos() );//목표 위치 설정
		m_vPath = vPlayerIndex;
	}

	if( vPlayerIndex == vTargetIndex )//플레이어와 타겟이 같은 경우
		m_vPath = NULLVECTOR2;//경로 없음

	m_ListNode.clear();//노드 리스트 clear
	SAFE_DELETE( pPathFinder );       //길찾기 제거
}

D3DXVECTOR2 CGameObjController::FollowPath()//길 따라 가기
{
	STileData* pData = g_pGameTileMgr->GetTileData( m_vPath );

	D3DXVECTOR2 vCenterPos  = pData->m_vIndexCenter;//센터 위치 받아옴
	D3DXVECTOR2 vPlayerPos = *m_pGameObj->GetPos();//게임오브젝트의 위치 받아옴

	D3DXVECTOR2 vCenterIndex  = g_pGameTileMgr->FindTileIndex( pData->m_vPos );
	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex( *m_pGameObj->GetPos());

	if( vCenterIndex != vPlayerIndex )
	{
		int iAngle =  (int)( CUtil::GetDirection( &vPlayerIndex, &vCenterIndex ) ); // 가야할길과 플레이어 위치가 같가면 방향계산을 하지않는다.
		m_pGameObj->SetDirection( (int)( iAngle / 45 ) );
	}

	return CUtil::GetDirectionVector( &vPlayerPos, &vCenterPos ); // 가야할길과 플레이어의 방향백터를 구한다.
}
