#pragma once

class CCreature : public CAniObj//�ִϿ�����Ʈ ��ӹ޾� Creature ����
{
public:
	CCreature(void);
	virtual ~CCreature(void);

	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );

	virtual void OnDamage( int iDamage, CGameObj* pObj );
};

