#pragma once

class CAniObj;

class CDirectionAniRender : public CRender//Crender 상속
{
private:
	CAniObj* pAniObj;

private:
	float m_fTrackTime;//Track time
	float m_fTrackSpeed;//Track speed 

	int m_iCurIndex;
	bool m_bLoop;

	CAniEvent m_AniEvent;

	map< int, vector< int >> m_mapAniDirection;	// 에니메이션 목록 

	void MakeLocal( D3DXMATRIX &matLocal );

public:
	CDirectionAniRender( CAniObj* pAniObj );
	virtual ~CDirectionAniRender(void);

	virtual void Load( wstring wFile );
	virtual bool OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();

	virtual void UpdateWorld();

	void SetAniIndex( int iIndex );
	int GetAniIndex() { return m_iCurIndex; }
};

