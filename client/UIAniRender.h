#pragma once

class CAniObj;

class CUIAniRender : public CRender
{
protected:
	float m_fTrackTime;
	float m_fTrackSpeed;

	int m_iCurIndex;
	bool m_bLoop;
	
	vector< int > m_vecTexture;
	
public:
	CUIAniRender( CAniObj* pGameObj  );
	virtual ~CUIAniRender(void);

	virtual void Load( wstring wFile );
	virtual bool OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();

	virtual void UpdateWorld();
	virtual void SetImgSize();

	void SetAniIndex( int iIndex );
	int GetAniIndex() { return m_iCurIndex; }
};

