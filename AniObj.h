#pragma once

class CGameObjController;

class CAniObj : public CGameObj 
{
protected:
	int m_iAniCategory;
	map< int, CRender* > m_mapAniRender;

	CGameObjController* m_pController;

	bool m_bChangeNextAni;

protected:
	virtual void OnEndAni();

public:
	CAniObj(void);
	virtual ~CAniObj(void);

	virtual void Load( wstring wFile );
	virtual void UnLoad();

	virtual void OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();

	CGameObjController* GetController() { return m_pController; }

	void OnChangeAni( int iAni );
	int GetAniCategory() { return m_iAniCategory; }
};

