#pragma once

class CHealth : public CGameObj
{
private:
	CGameObj* m_pPlayer;
		
public:
	CHealth(void);
	virtual ~CHealth(void);

	void SetPlayer( CGameObj* pObj ) { m_pPlayer = pObj; }

	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );
};

