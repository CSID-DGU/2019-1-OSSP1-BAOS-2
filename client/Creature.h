#pragma once

class CCreature : public CAniObj//애니오브젝트 상속받아 Creature 생성
{
public:
	CCreature(void);
	virtual ~CCreature(void);

	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );

	virtual void OnDamage( int iDamage, CGameObj* pObj );
};

