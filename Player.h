#pragma once

class CGameTileMgr;

class CPlayer : public CAniObj 
{
public:
	CPlayer(void);
	virtual ~CPlayer(void);

	float m_fTime;

	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );
};

