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

void CPathFinder::InitPathFinder()//��� Ž�� �ʱ�ȭ
{
	this->m_MasterNodeList.clear();

	while (this->m_OpenList.IsEmpty() == false)//���� pop������
		this->m_OpenList.Pop();
}

D3DXVECTOR2 CPathFinder::FindPath(D3DXVECTOR2 vStart, D3DXVECTOR2 vGoal)
{
	//������������ ��ǥ���������� ��� ����, ��帮��Ʈ�� ��� ���������μ� 
	//������������ ��ǥ�������� �ִܰ�θ� �� �� �ִ�.

	InitPathFinder(); //  ��ã�� ��� ���� �ʱ�ȭ ����Ʈ ������ �ʱ�ȭ

	CNode* StartNode = GetNode(vStart); // ���۳�� ����
	StartNode->m_Parent = NULL;	// �θ���� ����
	StartNode->m_Cost = 0;	// �г�Ƽ
	StartNode->m_Total = StartNode->m_Cost + CalculateHeuristic(vStart, vGoal); // ���� ���� ������ �� ��� + Start����� �г�Ƽ

	list< D3DXVECTOR2 > NeighborNodes;//�̿���� ����Ʈ

	this->GetNeightborNodes(StartNode->m_TilePos, NeighborNodes, vGoal);	// �̿���� �˻�
	list< D3DXVECTOR2 >::iterator it = NeighborNodes.begin();
	while (it != NeighborNodes.end())
	{
		CNode *NewNode = new CNode; // New ���
		NewNode->m_TilePos = (*it); /// New ���� �̿���� 

		//����Ʈ Ž��
		if (StartNode->m_Parent == NULL || StartNode->m_Parent->m_TilePos != NewNode->m_TilePos)
		{
			NewNode->m_Parent = StartNode;
			NewNode->m_Cost = StartNode->m_Cost + CostFromNodeToNode(NewNode, StartNode);
			NewNode->m_Total = NewNode->m_Cost + CalculateHeuristic(NewNode->m_TilePos, vGoal);

			this->m_OpenList.Push(NewNode);
		}

		++it;
		m_OpenList.UpdateNode(NewNode);//��� ������Ʈ
	}

	if (this->m_OpenList.IsEmpty() == true)
		return NULLVECTOR2;

	CNode* BestNode = this->m_OpenList.Pop();
	return BestNode->m_TilePos;
}


float CPathFinder::CalculateHeuristic(D3DXVECTOR2 vCurrent, D3DXVECTOR2 vGoal)//heuristic ���
{
	float fDist = CUtil::CalcDist(&vCurrent, &vGoal);//���纤�Ϳ� ��ǥ���� �Ÿ����

	return fDist;
}

float CPathFinder::CostFromNodeToNode(CNode* pNode1, CNode* pNode2) // Ÿ���̵����� �г�Ƽ
{
	return 1;
}

CNode* CPathFinder::GetNode(D3DXVECTOR2 vTilePos)//��� �ҷ�����
{
	PNodeHashTable::iterator it = this->m_MasterNodeList.find(TilePosToHashKey(vTilePos));	// ����Ʈ ��忡�� ã�´�.
	if (it != this->m_MasterNodeList.end())	// ����Ʈ ��� �� �����ִ�.
		return ((*it).second);	// �״�� ��ȯ

	CNode* pNewNode = new CNode;
	pNewNode->m_TilePos = vTilePos;

	this->m_MasterNodeList.insert(PNodeHashTable::value_type(TilePosToHashKey(pNewNode->m_TilePos), pNewNode)); // Hash ���̺� ����

	return pNewNode;// ����� ��ȯ
}

bool CPathFinder::AtGoal(CNode* pNode, D3DXVECTOR2 vGoal)//��ǥ���� �����ߴ��� �˻�
{
	if (pNode->m_TilePos == vGoal)
		return true;

	return false;
}

void CPathFinder::GetNeightborNodes(D3DXVECTOR2 &vTilePos, list< D3DXVECTOR2 > &NodeList, D3DXVECTOR2 vGoal)
{
	//�̿� ��� ����
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

wstring CPathFinder::TilePosToHashKey(const D3DXVECTOR2 &vTilePos)//�ؽ�Ű ����
{
	wstringstream os;
	os << vTilePos.x << L'_' << vTilePos.y;
	return os.str();
}

CNode* CPriorityQueue::Pop()//�켱���� ť���� pop
{
	CNode* Node = this->heap.front();
	pop_heap(this->heap.begin(), this->heap.end(), NodeTotalGreater());
	this->heap.pop_back();//heap �ڷᱸ������ �� ���� ������ pop ��Ų��.

	return Node;
}

void CPriorityQueue::Push(CNode* pNode)//�켱���� ť���� ������ push
{
	this->heap.push_back(pNode);
	push_heap(this->heap.begin(), this->heap.end(), NodeTotalGreater());
}

void CPriorityQueue::UpdateNode(CNode* pNode)//��� ������Ʈ
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

bool CPriorityQueue::IsEmpty()//�켱���� ť ������� �˻�
{
	if (this->heap.empty())
		return true;

	return false;
}

