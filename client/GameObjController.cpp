#include "DXUT.h"
#include "Home.h"

extern CGameObjMgr* g_pGameObjMgr;
extern CGameTileMgr* g_pGameTileMgr;

CGameObjController::CGameObjController( CAniObj* pGameObj ):
	m_pGameObj( pGameObj ),//���ӿ�����Ʈ ���� �����ϸ� ����
	m_pEnemy( NULL ),
	m_vPath( NULLVECTOR2 )
{
}


CGameObjController::~CGameObjController(void)
{
}

void CGameObjController::FindNode()//��� ã��
{	
	D3DXVECTOR2 vTargetIndex =  g_pGameTileMgr->FindTileIndex( *m_pGameObj->GetGoalPos() );	// Ÿ�� Ű��
	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex(  *m_pGameObj->GetPos() );	// �ʷ��̾� Ű��

	m_vPath = NULLVECTOR2; // �ʱ�ȭ

	CPathFinder* pPathFinder = new CPathFinder;	// ��ã�� ����
	m_vPath = pPathFinder->FindPath( vPlayerIndex, vTargetIndex );	// ��ã��

	if( pPathFinder->bCanGoal == false )//���� ã�� ������ ���
	{
		m_pGameObj->SetGoalPos( *m_pGameObj->GetPos() );//��ǥ ��ġ ����
		m_vPath = vPlayerIndex;
	}

	if( vPlayerIndex == vTargetIndex )//�÷��̾�� Ÿ���� ���� ���
		m_vPath = NULLVECTOR2;//��� ����

	m_ListNode.clear();//��� ����Ʈ clear
	SAFE_DELETE( pPathFinder );       //��ã�� ����
}

D3DXVECTOR2 CGameObjController::FollowPath()//�� ���� ����
{
	STileData* pData = g_pGameTileMgr->GetTileData( m_vPath );

	D3DXVECTOR2 vCenterPos  = pData->m_vIndexCenter;//���� ��ġ �޾ƿ�
	D3DXVECTOR2 vPlayerPos = *m_pGameObj->GetPos();//���ӿ�����Ʈ�� ��ġ �޾ƿ�

	D3DXVECTOR2 vCenterIndex  = g_pGameTileMgr->FindTileIndex( pData->m_vPos );
	D3DXVECTOR2 vPlayerIndex = g_pGameTileMgr->FindTileIndex( *m_pGameObj->GetPos());

	if( vCenterIndex != vPlayerIndex )
	{
		int iAngle =  (int)( CUtil::GetDirection( &vPlayerIndex, &vCenterIndex ) ); // �����ұ�� �÷��̾� ��ġ�� ������ �������� �����ʴ´�.
		m_pGameObj->SetDirection( (int)( iAngle / 45 ) );
	}

	return CUtil::GetDirectionVector( &vPlayerPos, &vCenterPos ); // �����ұ�� �÷��̾��� ������͸� ���Ѵ�.
}
