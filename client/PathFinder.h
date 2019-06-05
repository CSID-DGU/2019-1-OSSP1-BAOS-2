#pragma once

class CNode//노드 클래스
{
public:
	D3DXVECTOR2 m_TilePos;//타일위치
	CNode* m_Parent;//부모노드

	float m_Cost;//비용
	float m_Total;//전체비용
};

typedef map< wstring, CNode* > PNodeHashTable;

class CPriorityQueue//우선순위큐
{
private:
	vector< CNode* > heap;//힙

public://우선순위 큐 클래스의 연산 : pop, push, 노드 업데이트, 비어있는지 계산
	CNode* Pop();
	void Push( CNode* pNode );
	void UpdateNode( CNode* pNode );
	bool IsEmpty();
};


class CPathFinder//경로 찾기 클래스
{
private:
	list< CNode* > m_FindList;//노드리스트
	
public:
	CPathFinder( void );
	virtual ~CPathFinder(void);

	bool bCanGoal;
	D3DXVECTOR2 m_vVirtualHuddleIndex;

public:
	CNode* GetNode( D3DXVECTOR2 TilePos );//노드 불러오기
	D3DXVECTOR2 FindPath( D3DXVECTOR2 vStart, D3DXVECTOR2 vGoal );

	void InitPathFinder();

	bool AtGoal( CNode* pNode, D3DXVECTOR2 vGoal );
	float CalculateHeuristic( D3DXVECTOR2 vCurrent, D3DXVECTOR2 vGoal );

	void GetNeightborNodes( D3DXVECTOR2& vTilePos, list< D3DXVECTOR2 >& NodeList, D3DXVECTOR2 vGoal );
	float CostFromNodeToNode( CNode* pNode1, CNode* pNode2 );

	wstring TilePosToHashKey( const D3DXVECTOR2 &vTilePos );// Hash  키 만들기

	list< CNode* >& GetFindList() { return m_FindList; }

	PNodeHashTable m_MasterNodeList;
	CPriorityQueue m_OpenList;
};

class NodeTotalGreater//노드 중 더 큰 녀석 리턴하게끔 체크하게 하는 bool형
{
public:
	bool operator() ( CNode* pFirst, CNode* pSecond ) const{
		return ( pFirst->m_Total > pSecond->m_Total ); }
};