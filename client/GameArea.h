#pragma once

class CGameStage;

class CGameArea
{
protected:
	CGameStage* m_pGameStage;

	int m_iNextArea;
public:
	CGameArea( CGameStage* pGameStage );
	virtual ~CGameArea(void);

	virtual void Load() {}
	virtual void OnFrameMove( float fElapsedTime ) {};
};

