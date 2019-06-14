#pragma once

class CGameObj;

class CGameObjController : public CFSM//FSM 상속
{
protected:
	CAniObj* m_pGameObj;//gameobj와 enemy 생성
	CGameObj* m_pEnemy;

	D3DXVECTOR2 m_vPath;	// 가야할길

protected:
	list< CNode* > m_ListNode; // 찾은경로

public:
	void FindNode();	// 노드 찾기

	D3DXVECTOR2 FollowPath();   // 노드 따라가기      

public:
	CGameObjController(CAniObj* pGameObj);
	virtual ~CGameObjController(void);

	void SetEnemy(CGameObj* pGameObj) {
		m_pEnemy = pGameObj;
	}

	CGameObj* GetEnemy() {
		return m_pEnemy;
	}

	virtual void OnFrameMove(float fElpasedTime) {}

	virtual void OnEndAni(int iAniCategory) {}
	virtual void OnChangeAni(int iAniCategory) {}

	CAniObj* GetGameObj() { return m_pGameObj; }
};

