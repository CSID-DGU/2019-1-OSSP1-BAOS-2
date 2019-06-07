#pragma once

class CDark : public CGameObj
{
private:
	int m_iViewID;

private:
	float m_fDarkUpdateTimer;
	float m_fDarkResetTimer;

public:
	CDark(void);
	virtual ~CDark(void);

	void UpdateDark();
	void ResetDark();

	virtual void Load( wstring wFile );
	virtual void OnFrameMove( float fElapsedTime );
};

