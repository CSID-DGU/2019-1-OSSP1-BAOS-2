#pragma once

enum
{
	EGAMEOBJ_TILE,//�ٴ� Ÿ�� ������Ʈ
	EGAMEOBJ_BEGINEFFECT,//����Ʈ ���� ������Ʈ 

	EGAMEOBJ_TOWER,//���๰ ������Ʈ
	EGAMEOBJ_PLAYER,//ĳ���� ������Ʈ
	EGAMEOBJ_CREATURE,//ũ���� ������Ʈ




	EGAMEOBJ_EFFECT,//����Ʈ ������Ʈ

	EGAMEOBJ_HEALTH,//ü�� ������Ʈ
	EGAMEOBJ_DARK,//��� ������Ʈ
	EGAMEOBJ_UI,//UI ������Ʈ
	EGAMEOBJ_MINIDARK//�̴ϸ� ������Ʈ
};

class CGameObjMgr : public CGameObjContainer//���ӿ�����Ʈ �����̳ʷκ��� ���
{
private:
	void OnFrameMove( const vector< CGameObj* >& vecObj, float fElapsedTime );//�����ӹ��� ���
	void OnFrameRender( const vector< CGameObj* >& vecObj );

protected:
	virtual CGameObj* Alloc( int iType );//���ӿ�����Ʈ ����

public:
	CGameObj* pEnemyTower;//���� Ÿ�� ���� ������Ʈ ����
	CGameObj* pFriendTower;//�Ʊ� Ÿ�� ���� ������Ʈ ����

public:
	CGameObjMgr(void);
	virtual ~CGameObjMgr(void);

	void OnFrameMove( float fElapsedTime );
	void OnFrameRender();
	void ListFrameRender();
};

