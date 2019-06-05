#pragma once

class CImgRender : public CRender//Render에서 상속
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

