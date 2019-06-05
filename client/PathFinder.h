#pragma once

class CNode//��� Ŭ����
{
public:
	D3DXVECTOR2 m_TilePos;//Ÿ����ġ
	CNode* m_Parent;//�θ���

	float m_Cost;//���
	float m_Total;//��ü���
};

typedef map< wstring, CNode* > PNodeHashTable;

class CPriorityQueue//�켱����ť
{
private:
	vector< CNode* > heap;//��

public://�켱���� ť Ŭ������ ���� : pop, push, ��� ������Ʈ, ����ִ��� ���
	CNode* Pop();
	void Push( CNode* pNode );
	void UpdateNode( CNode* pNode );
	bool IsEmpty();
};


class CPathFinder//��� ã�� Ŭ����
{
private:
	list< CNode* > m_FindList;//��帮��Ʈ
	
public:
	CPathFinder( void );
	virtual ~CPathFinder(void);

	bool bCanGoal;
	D3DXVECTOR2 m_vVirtualHuddleIndex;

public:
	CNode* GetNode( D3DXVECTOR2 TilePos );//��� �ҷ�����
	D3DXVECTOR2 FindPath( D3DXVECTOR2 vStart, D3DXVECTOR2 vGoal );

	void InitPathFinder();

	bool AtGoal( CNode* pNode, D3DXVECTOR2 vGoal );
	float CalculateHeuristic( D3DXVECTOR2 vCurrent, D3DXVECTOR2 vGoal );

	void GetNeightborNodes( D3DXVECTOR2& vTilePos, list< D3DXVECTOR2 >& NodeList, D3DXVECTOR2 vGoal );
	float CostFromNodeToNode( CNode* pNode1, CNode* pNode2 );

	wstring TilePosToHashKey( const D3DXVECTOR2 &vTilePos );// Hash  Ű �����

	list< CNode* >& GetFindList() { return m_FindList; }

	PNodeHashTable m_MasterNodeList;
	CPriorityQueue m_OpenList;
};

class NodeTotalGreater//��� �� �� ū �༮ �����ϰԲ� üũ�ϰ� �ϴ� bool��
{
public:
	bool operator() ( CNode* pFirst, CNode* pSecond ) const{
		return ( pFirst->m_Total > pSecond->m_Total ); }
};