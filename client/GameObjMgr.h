#pragma once

enum
{
	EGAMEOBJ_TILE,
	EGAMEOBJ_BEGINEFFECT,

	EGAMEOBJ_TOWER,
	EGAMEOBJ_PLAYER,
	EGAMEOBJ_CREATURE,


	EGAMEOBJ_EFFECT,

	EGAMEOBJ_HEALTH,
	EGAMEOBJ_DARK,
	EGAMEOBJ_UI,
	EGAMEOBJ_MINIDARK
};

class CGameObjMgr
{
private:
	void OnFrameMove( const vector< CGameObj* >& vecObj, float fElapsedTime );
	void OnFrameRender( const vector< CGameObj* >& vecObj );

protected:
	virtual CGameObj* Alloc( int iType );

public:
	CGameObj* pEnemyTower;
	CGameObj* pFriendTower;

	CGameObjMgr(void);
	virtual ~CGameObjMgr(void);

	void OnFrameMove( float fElapsedTime );
	void OnFrameRender();
	void ListFrameRender();
};

