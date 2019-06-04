#pragma once

class CCreatureAI : public CGameObjController//게임 오브젝트 컨트롤러 상속
{
private:
	static void OnUpdateNormal(DWORD dwObj, float fElapsedTime);//상태 설정
	static void OnUpdateMove(DWORD dwObj, float fElapsedTime);
	static void OnUpdateAttack(DWORD dwObj, float fElapsedTime);
	static void OnBeginDie(DWORD dwObj);

public:
	CCreatureAI(CAniObj* pGameObj);
	virtual ~CCreatureAI(void);

	void OnPriorityEnemy();

	virtual void OnFrameMove(float fElapsedTime);
	virtual void OnEndAni(int iAniCategory);
	virtual void OnChangeAni(int iAniCategory);
};
