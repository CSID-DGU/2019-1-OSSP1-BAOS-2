#pragma once

class CGameTileMgr;

class CPlayer : public CAniObj //애니오브젝트 상속
{
	//플레이어 오브젝트
public:
	CPlayer(void);
	virtual ~CPlayer(void);

	float m_fTime;

	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );
	virtual void OnDamage(int iDamage, CGameObj* pGameObj);
};

