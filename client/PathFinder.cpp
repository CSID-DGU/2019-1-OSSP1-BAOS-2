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
	InitPathFinder();						//  길찾기 노드 베열을 초기화한다. 마스터 노드까지 초기화!

	CNode* StartNode = GetNode( vStart );	// 시작노드 생성
	StartNode->m_Parent = NULL;				// 부모노드는 없음
	StartNode->m_Cost = 0;					// 패널티 = 0
	StartNode->m_Total = StartNode->m_Cost + CalculateHeuristic( vStart, vGoal ); 
											// 시작에서 끝까지의 휴리스틱 추정값 + Start노드의 패널티
	
	list< D3DXVECTOR2 > NeighborNodes; 

	this->GetNeightborNodes( StartNode->m_TilePos, NeighborNodes, vGoal );	// 이웃노드 검색
	list< D3DXVECTOR2 >::iterator it = NeighborNodes.begin();
	while( it != NeighborNodes.end() )
	{
		CNode *NewNode = new CNode;				// New 노드
		NewNode->m_TilePos = (*it );			// 이웃노드가 새로운 노드가 되겠지?
		
		if( StartNode->m_Parent == NULL || StartNode->m_Parent->m_TilePos != NewNode->m_TilePos ) 
		{	// 시작 노드이거나 마스터 노드가 아니라면,
			NewNode->m_Parent = StartNode;		// 리스트를 이어준다 (자료구조 그대로)
			NewNode->m_Cost = StartNode->m_Cost + CostFromNodeToNode( NewNode, StartNode );			// 패널티 증가
			NewNode->m_Total = NewNode->m_Cost + CalculateHeuristic( NewNode->m_TilePos, vGoal );	// 총 코스트를 계속 계산한다.

			this->m_OpenList.Push( NewNode );	// OpenList 우선순위 큐에 push 해준다.
		}
		++it;									// 다음 노드로 이동한다.
		m_OpenList.UpdateNode( NewNode );		// 새로운 노드를 업데이트 해준다. (마지막 노드까지 계속 반복!)
	}

	CNode* BestNode = this->m_OpenList.Pop();

	//if( bCanGoal == false )
	//	return NULLVECTOR2;

	return BestNode->m_TilePos;					// 목적: 코스트가 최소가 되는 지점을 우선 탐색하는 것이다.
}


float CPathFinder::CalculateHeuristic( D3DXVECTOR2 vCurrent, D3DXVECTOR2 vGoal )
{											// 휴리스틱 추정값을 계산하는 함수
	D3DXVECTOR2 vLen = vCurrent - vGoal;	// f(x) = h(x) + g(x)
	float fDist = D3DXVec2Length(&vLen);	// 출발노드로부터 도착노드까지의 경로 가중치
											// - 노드n으로부터 목표노드(goal)까지 추정경로 가중치, 즉 도착노드까지 예상 이동 비용
	return fDist;
}

float CPathFinder::CostFromNodeToNode( CNode* pNode1, CNode* pNode2 ) // 타일이동간의 패널티
{
	return 1;
}

CNode* CPathFinder::GetNode( D3DXVECTOR2 vTilePos )
{
	PNodeHashTable::iterator it = this->m_MasterNodeList.find( TilePosToHashKey( vTilePos ));	// 마스터 노드에서 찾는다.
	if( it != this->m_MasterNodeList.end() )	// 마스터 노드에 값이있다면,
		return ((*it).second );					// 그대로 반환

	CNode* pNewNode = new CNode;
	pNewNode->m_TilePos = vTilePos; 

	this->m_MasterNodeList.insert( PNodeHashTable::value_type( TilePosToHashKey( pNewNode->m_TilePos ), pNewNode )); // Hash 테이블에 넣음

	return pNewNode;							// 새노드 반환
}

bool CPathFinder::AtGoal( CNode* pNode, D3DXVECTOR2 vGoal )
{
	if( pNode->m_TilePos == vGoal )				// 목표 지점에 도착했다면 종료
		return true;

	return false;								// 아니면 계속 탐색 진행
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

			if( pData == NULL )					//	[예외1] 노드가 없으면 continue
				continue;

			if( vTilePos == vNeighborNode )		//	[예외2] 시작 지점과 이웃 노드의 위치가 같으면 continue
				continue;		
		
			if( vNeighborNode == vGoal && pGoalData->m_iTileType == 0 )
				bCanGoal = false;				//	[예외3] 목표 지점이 못 가는 지역이면 false, 탐색 종료

			if( pData->m_iTileType == 0)		//  [예외4] 못 가는 지역이면 continue
				continue;

			NodeList.push_back( vNeighborNode );// 모두 통과했다면 이웃 노드를 push_back해줘서 update 해준다.
		}
}

wstring CPathFinder::TilePosToHashKey( const D3DXVECTOR2 &vTilePos )
{
	wstringstream os;
	os << vTilePos.x << L'_' << vTilePos.y;		// hash키 출력한다
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

