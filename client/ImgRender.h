#pragma once

class CImgRender : public CRender
{
private:
	int m_iTexture;

	void MakeLocal( D3DXMATRIX &matLocal );

private:
	CGameObj* m_pGameObj;

public:
	CImgRender( CGameObj* pGameObj );
	virtual ~CImgRender(void);

	virtual void SetDarkMode( D3DXVECTOR2 vPos, int iTexture );

	virtual void Load( wstring wFile );
	virtual bool OnFrameMove( float fElapsedTime );
	virtual void OnFrameRender();

	virtual void UpdateWorld();
};

