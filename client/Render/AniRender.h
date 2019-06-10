#pragma once

class CAniObj;

class CAniRender : public CRender//render에서 상속
{
private:
	float m_fTrackSpeed; // 이미지 속도
	float m_fTrackTime; // 이미지 돌리는 시간

	int m_iCurIndex;	// 이미지 장수
	bool m_bLoop;		// 반복
	
	vector< int > m_vecTexture;		// 텍스쳐 배열
	CAniEvent m_AniEvent;

	void MakeLocal( D3DXMATRIX& matLocal );	// 에니메이션 행렬

public:
	CAniRender( CAniObj* pAniObj );	
	virtual ~CAniRender(void);

	virtual void Load( wstring wFile );

	virtual bool OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();

	virtual void UpdateWorld();

	void SetAniIndex( int iIndex );	// 에니메이션 장수
	int GetAniIndex() { return m_iCurIndex; }	// 에니메이션 장수 구하기
};


