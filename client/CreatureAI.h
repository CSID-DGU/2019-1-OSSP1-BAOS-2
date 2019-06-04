#pragma once

class CCreatureAI : public CGameObjController
{
private:
	static void OnUpdateNormal( DWORD dwObj, float fElapsedTime );
	static void OnUpdateMove( DWORD dwObj, float fElapsedTime );
	static void OnUpdateAttack( DWORD dwObj, float fElapsedTime );
	static void OnBeginDie( DWORD dwObj );

public:
	CCreatureAI( CAniObj* pGameObj );
	virtual ~CCreatureAI(void);

	void OnPriorityEnemy();

	virtual void OnFrameMove( float fElapsedTime );
	virtual void OnEndAni( int iAniCategory );
	virtual void OnChangeAni( int iAniCategory );
};

