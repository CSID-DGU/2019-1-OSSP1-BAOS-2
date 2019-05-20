#include "DXUT.h"
#include "Home.h"

extern CGameTileMgr* g_pGameTileMgr;

CPathFinder::CPathFinder():
	bCanGoal( true )
{
}


CPathFinder::~CPathFinder(void)
{
	this->m_MasterNodeList.clear();
}

void CPathFinder::InitPathFinder()
{
	this->m_MasterNodeList.clear();

	while( this->m_OpenList.IsEmpty() == false )
		this->m_OpenList.Pop();
}

D3DXVECTOR2 CPathFinder::FindPath( D3DXVECTOR2 vStart, D3DXVECTOR2 vGoal )
{
	InitPathFinder();						//  ��ã�� ��� ������ �ʱ�ȭ�Ѵ�. ������ ������ �ʱ�ȭ!

	CNode* StartNode = GetNode( vStart );	// ���۳�� ����
	StartNode->m_Parent = NULL;				// �θ���� ����
	StartNode->m_Cost = 0;					// �г�Ƽ = 0
	StartNode->m_Total = StartNode->m_Cost + CalculateHeuristic( vStart, vGoal ); 
											// ���ۿ��� �������� �޸���ƽ ������ + Start����� �г�Ƽ
	
	list< D3DXVECTOR2 > NeighborNodes; 

	this->GetNeightborNodes( StartNode->m_TilePos, NeighborNodes, vGoal );	// �̿���� �˻�
	list< D3DXVECTOR2 >::iterator it = NeighborNodes.begin();
	while( it != NeighborNodes.end() )
	{
		CNode *NewNode = new CNode;				// New ���
		NewNode->m_TilePos = (*it );			// �̿���尡 ���ο� ��尡 �ǰ���?
		
		if( StartNode->m_Parent == NULL || StartNode->m_Parent->m_TilePos != NewNode->m_TilePos ) 
		{	// ���� ����̰ų� ������ ��尡 �ƴ϶��,
			NewNode->m_Parent = StartNode;		// ����Ʈ�� �̾��ش� (�ڷᱸ�� �״��)
			NewNode->m_Cost = StartNode->m_Cost + CostFromNodeToNode( NewNode, StartNode );			// �г�Ƽ ����
			NewNode->m_Total = NewNode->m_Cost + CalculateHeuristic( NewNode->m_TilePos, vGoal );	// �� �ڽ�Ʈ�� ��� ����Ѵ�.

			this->m_OpenList.Push( NewNode );	// OpenList �켱���� ť�� push ���ش�.
		}
		++it;									// ���� ���� �̵��Ѵ�.
		m_OpenList.UpdateNode( NewNode );		// ���ο� ��带 ������Ʈ ���ش�. (������ ������ ��� �ݺ�!)
	}

	CNode* BestNode = this->m_OpenList.Pop();

	//if( bCanGoal == false )
	//	return NULLVECTOR2;

	return BestNode->m_TilePos;					// ����: �ڽ�Ʈ�� �ּҰ� �Ǵ� ������ �켱 Ž���ϴ� ���̴�.
}


float CPathFinder::CalculateHeuristic( D3DXVECTOR2 vCurrent, D3DXVECTOR2 vGoal )
{											// �޸���ƽ �������� ����ϴ� �Լ�
	D3DXVECTOR2 vLen = vCurrent - vGoal;	// f(x) = h(x) + g(x)
	float fDist = D3DXVec2Length(&vLen);	// ��߳��κ��� ������������ ��� ����ġ
											// - ���n���κ��� ��ǥ���(goal)���� ������� ����ġ, �� ���������� ���� �̵� ���
	return fDist;
}

float CPathFinder::CostFromNodeToNode( CNode* pNode1, CNode* pNode2 ) // Ÿ���̵����� �г�Ƽ
{
	return 1;
}

CNode* CPathFinder::GetNode( D3DXVECTOR2 vTilePos )
{
	PNodeHashTable::iterator it = this->m_MasterNodeList.find( TilePosToHashKey( vTilePos ));	// ������ ��忡�� ã�´�.
	if( it != this->m_MasterNodeList.end() )	// ������ ��忡 �����ִٸ�,
		return ((*it).second );					// �״�� ��ȯ

	CNode* pNewNode = new CNode;
	pNewNode->m_TilePos = vTilePos; 

	this->m_MasterNodeList.insert( PNodeHashTable::value_type( TilePosToHashKey( pNewNode->m_TilePos ), pNewNode )); // Hash ���̺� ����

	return pNewNode;							// ����� ��ȯ
}

bool CPathFinder::AtGoal( CNode* pNode, D3DXVECTOR2 vGoal )
{
	if( pNode->m_TilePos == vGoal )				// ��ǥ ������ �����ߴٸ� ����
		return true;

	return false;								// �ƴϸ� ��� Ž�� ����
}

void CPathFinder::GetNeightborNodes( D3DXVECTOR2 &vTilePos, list< D3DXVECTOR2 > &NodeList, D3DXVECTOR2 vGoal )
{
	D3DXVECTOR2 vNeighborNode;

	NodeList.clear();

	for( int Row = (int)vTilePos.x -1; Row <= vTilePos.x + 1; Row++ )
		for( int Col = (int)vTilePos.y - 1; Col <= vTilePos.y + 1; Col++ )
		{
			vNeighborNode = D3DXVECTOR2( (float)Row, (float)Col );
			STileData* pData = g_pGameTileMgr->GetTileData( vNeighborNode );
			STileData* pGoalData = g_pGameTileMgr->GetTileData( vGoal );

			if( pData == NULL )					//	[����1] ��尡 ������ continue
				continue;

			if( vTilePos == vNeighborNode )		//	[����2] ���� ������ �̿� ����� ��ġ�� ������ continue
				continue;		
		
			if( vNeighborNode == vGoal && pGoalData->m_iTileType == 0 )
				bCanGoal = false;				//	[����3] ��ǥ ������ �� ���� �����̸� false, Ž�� ����

			if( pData->m_iTileType == 0)		//  [����4] �� ���� �����̸� continue
				continue;

			NodeList.push_back( vNeighborNode );// ��� ����ߴٸ� �̿� ��带 push_back���༭ update ���ش�.
		}
}

wstring CPathFinder::TilePosToHashKey( const D3DXVECTOR2 &vTilePos )
{
	wstringstream os;
	os << vTilePos.x << L'_' << vTilePos.y;		// hashŰ ����Ѵ�
	return os.str();
}

CNode* CPriorityQueue::Pop()
{
	CNode* Node = this->heap.front();
	pop_heap(this->heap.begin(), this->heap.end(), NodeTotalGreater());
	this->heap.pop_back();

	return Node;
}

void CPriorityQueue::Push( CNode* pNode )
{
	this->heap.push_back( pNode );
	push_heap( this->heap.begin(), this->heap.end(), NodeTotalGreater() );
}

void CPriorityQueue::UpdateNode( CNode* pNode )
{
	vector< CNode* >::iterator it;
	for( it = this->heap.begin(); it != this->heap.end(); it++ )
	{
		if( (*it)->m_TilePos.x == pNode->m_TilePos.x && (*it)->m_TilePos.y == pNode->m_TilePos.y )
		{
			push_heap( this->heap.begin(), it + 1, NodeTotalGreater() );
			return ;
		}
	}
}

bool CPriorityQueue::IsEmpty()
{
	if( this->heap.empty() )
		return true;

	return false;
}

