#pragma once

class CTowerAI: public CGameObjController
{
private:
	static void OnUpdateNormal( DWORD dwObj, float fElapsedTime );
	static void OnUpdateAttack( DWORD dwObj, float fElapsedTime );
	static void OnBeginDie( DWORD dwObj );

public:
	CTowerAI( CAniObj* pGameObj );
	virtual ~CTowerAI(void);

	void OnPriorityEnemy();

	virtual void OnFrameMove( float fElapsedTime );
	virtual void OnEndAni( int iAniCategory );
	virtual void OnChangeAni( int iAniCategory );
};
