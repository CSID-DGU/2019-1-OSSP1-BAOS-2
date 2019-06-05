#include "DXUT.h"
#include "Home.h"

extern CGameTileMgr* g_pGameTileMgr;

CPathFinder::CPathFinder() :
	bCanGoal(true)
{
}


CPathFinder::~CPathFinder(void)
{
	this->m_MasterNodeList.clear();
}

void CPathFinder::InitPathFinder()//경로 탐색 초기화
{
	this->m_MasterNodeList.clear();

	while (this->m_OpenList.IsEmpty() == false)//전부 pop시켜줌
		this->m_OpenList.Pop();
}

D3DXVECTOR2 CPathFinder::FindPath(D3DXVECTOR2 vStart, D3DXVECTOR2 vGoal)
{
	//시작지점부터 목표지점까지의 경로 조사, 노드리스트에 노드 저장함으로서 
	//시점지점부터 목표지점까지 최단경로를 알 수 있다.

	InitPathFinder(); //  길찾기 노드 베열 초기화 마스트 노드까지 초기화

	CNode* StartNode = GetNode(vStart); // 시작노드 생성
	StartNode->m_Parent = NULL;	// 부모노드는 없음
	StartNode->m_Cost = 0;	// 패널티
	StartNode->m_Total = StartNode->m_Cost + CalculateHeuristic(vStart, vGoal); // 시작 에서 끝까지 의 노드 + Start노드의 패널티

	list< D3DXVECTOR2 > NeighborNodes;//이웃노드 리스트

	this->GetNeightborNodes(StartNode->m_TilePos, NeighborNodes, vGoal);	// 이웃노드 검색
	list< D3DXVECTOR2 >::iterator it = NeighborNodes.begin();
	while (it != NeighborNodes.end())
	{
		CNode *NewNode = new CNode; // New 노드
		NewNode->m_TilePos = (*it); /// New 노드는 이웃노드 

		//리스트 탐색
		if (StartNode->m_Parent == NULL || StartNode->m_Parent->m_TilePos != NewNode->m_TilePos)
		{
			NewNode->m_Parent = StartNode;
			NewNode->m_Cost = StartNode->m_Cost + CostFromNodeToNode(NewNode, StartNode);
			NewNode->m_Total = NewNode->m_Cost + CalculateHeuristic(NewNode->m_TilePos, vGoal);

			this->m_OpenList.Push(NewNode);
		}

		++it;
		m_OpenList.UpdateNode(NewNode);//노드 업데이트
	}

	if (this->m_OpenList.IsEmpty() == true)
		return NULLVECTOR2;

	CNode* BestNode = this->m_OpenList.Pop();
	return BestNode->m_TilePos;
}


float CPathFinder::CalculateHeuristic(D3DXVECTOR2 vCurrent, D3DXVECTOR2 vGoal)//heuristic 계산
{
	float fDist = CUtil::CalcDist(&vCurrent, &vGoal);//현재벡터와 목표벡터 거리계산

	return fDist;
}

float CPathFinder::CostFromNodeToNode(CNode* pNode1, CNode* pNode2) // 타일이동간의 패널티
{
	return 1;
}

CNode* CPathFinder::GetNode(D3DXVECTOR2 vTilePos)//노드 불러오기
{
	PNodeHashTable::iterator it = this->m_MasterNodeList.find(TilePosToHashKey(vTilePos));	// 마스트 노드에서 찾는다.
	if (it != this->m_MasterNodeList.end())	// 마스트 노드 에 값이있다.
		return ((*it).second);	// 그대로 반환

	CNode* pNewNode = new CNode;
	pNewNode->m_TilePos = vTilePos;

	this->m_MasterNodeList.insert(PNodeHashTable::value_type(TilePosToHashKey(pNewNode->m_TilePos), pNewNode)); // Hash 테이블에 넣음

	return pNewNode;// 새노드 반환
}

bool CPathFinder::AtGoal(CNode* pNode, D3DXVECTOR2 vGoal)//목표까지 도달했는지 검사
{
	if (pNode->m_TilePos == vGoal)
		return true;

	return false;
}

void CPathFinder::GetNeightborNodes(D3DXVECTOR2 &vTilePos, list< D3DXVECTOR2 > &NodeList, D3DXVECTOR2 vGoal)
{
	//이웃 노드 설정
	D3DXVECTOR2 vNeighborNode;

	NodeList.clear();

	for (int Row = (int)vTilePos.x - 1; Row <= vTilePos.x + 1; Row++)
		for (int Col = (int)vTilePos.y - 1; Col <= vTilePos.y + 1; Col++)
		{
			vNeighborNode = D3DXVECTOR2((float)Row, (float)Col);
			STileData* pData = g_pGameTileMgr->GetTileData(vNeighborNode);
			STileData* pGoalData = g_pGameTileMgr->GetTileData(vGoal);

			if (pData == NULL)
				continue;

			if (vTilePos == vNeighborNode)
				continue;

			if (vNeighborNode == vGoal && pGoalData->m_iTileType == 0)
				bCanGoal = false;

			if (pData->m_iTileType == 0)
				continue;

			NodeList.push_back(vNeighborNode);
		}
}

wstring CPathFinder::TilePosToHashKey(const D3DXVECTOR2 &vTilePos)//해시키 리턴
{
	wstringstream os;
	os << vTilePos.x << L'_' << vTilePos.y;
	return os.str();
}

CNode* CPriorityQueue::Pop()//우선순위 큐에서 pop
{
	CNode* Node = this->heap.front();
	pop_heap(this->heap.begin(), this->heap.end(), NodeTotalGreater());
	this->heap.pop_back();//heap 자료구조에서 맨 앞의 데이터 pop 시킨다.

	return Node;
}

void CPriorityQueue::Push(CNode* pNode)//우선순위 큐에서 데이터 push
{
	this->heap.push_back(pNode);
	push_heap(this->heap.begin(), this->heap.end(), NodeTotalGreater());
}

void CPriorityQueue::UpdateNode(CNode* pNode)//노드 업데이트
{
	vector< CNode* >::iterator it;
	for (it = this->heap.begin(); it != this->heap.end(); it++)
	{
		if ((*it)->m_TilePos.x == pNode->m_TilePos.x && (*it)->m_TilePos.y == pNode->m_TilePos.y)
		{
			push_heap(this->heap.begin(), it + 1, NodeTotalGreater());
			return;
		}
	}
}

bool CPriorityQueue::IsEmpty()//우선순위 큐 비었는지 검사
{
	if (this->heap.empty())
		return true;

	return false;
}

