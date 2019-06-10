#pragma once

class CImgRender : public CRender//Crender 상속 이미지 렌더링 위한 클래스
{
protected:
	int m_iTexture;

	void MakeLocal( D3DXMATRIX &matLocal );

public:
	CImgRender( CGameObj* pGameObj );
	virtual ~CImgRender(void);


	virtual void Load( wstring wFile );
	virtual bool OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();

	virtual void UpdateWorld();
};

