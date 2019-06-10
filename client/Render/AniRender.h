#pragma once

class CAniObj;

class CAniRender : public CRender//render���� ���
{
private:
	float m_fTrackSpeed; // �̹��� �ӵ�
	float m_fTrackTime; // �̹��� ������ �ð�

	int m_iCurIndex;	// �̹��� ���
	bool m_bLoop;		// �ݺ�
	
	vector< int > m_vecTexture;		// �ؽ��� �迭
	CAniEvent m_AniEvent;

	void MakeLocal( D3DXMATRIX& matLocal );	// ���ϸ��̼� ���

public:
	CAniRender( CAniObj* pAniObj );	
	virtual ~CAniRender(void);

	virtual void Load( wstring wFile );

	virtual bool OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();

	virtual void UpdateWorld();

	void SetAniIndex( int iIndex );	// ���ϸ��̼� ���
	int GetAniIndex() { return m_iCurIndex; }	// ���ϸ��̼� ��� ���ϱ�
};


