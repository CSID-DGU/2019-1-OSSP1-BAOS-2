#pragma once

enum
{
	EGAMEOBJ_TILE,//바닥 타일 오브젝트
	EGAMEOBJ_BEGINEFFECT,//이펙트 시작 오브젝트 

	EGAMEOBJ_TOWER,//건축물 오브젝트
	EGAMEOBJ_PLAYER,//캐릭터 오브젝트
	EGAMEOBJ_CREATURE,//크리쳐 오브젝트




	EGAMEOBJ_EFFECT,//이펙트 오브젝트

	EGAMEOBJ_HEALTH,//체력 오브젝트
	EGAMEOBJ_DARK,//배경 오브젝트
	EGAMEOBJ_UI,//UI 오브젝트
	EGAMEOBJ_MINIDARK//미니맵 오브젝트
};

class CGameObjMgr : public CGameObjContainer//게임오브젝트 컨테이너로부터 상속
{
private:
	void OnFrameMove( const vector< CGameObj* >& vecObj, float fElapsedTime );//프레임무브 사용
	void OnFrameRender( const vector< CGameObj* >& vecObj );

protected:
	virtual CGameObj* Alloc( int iType );//게임오브젝트 할탕

public:
	CGameObj* pEnemyTower;//적군 타워 게임 오브젝트 생성
	CGameObj* pFriendTower;//아군 타워 게임 오브젝트 생성

public:
	CGameObjMgr(void);
	virtual ~CGameObjMgr(void);

	void OnFrameMove( float fElapsedTime );
	void OnFrameRender();
	void ListFrameRender();
};

