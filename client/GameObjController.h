#pragma once

class CGameObj;

class CGameObjController : public CFSM//FSM ���
{
protected:
	CAniObj* m_pGameObj;//gameobj�� enemy ����
	CGameObj* m_pEnemy;

	D3DXVECTOR2 m_vPath;	// �����ұ�

protected:
	list< CNode* > m_ListNode; // ã�����

public:
	void FindNode();	// ��� ã��

	D3DXVECTOR2 FollowPath();   // ��� ���󰡱�      

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

