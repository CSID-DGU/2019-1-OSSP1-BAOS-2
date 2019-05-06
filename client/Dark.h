#pragma once

class CDark : public CGameObj
{
private:
	int m_iViewID;

public:
	CDark(void);
	virtual ~CDark(void);

	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );
};

