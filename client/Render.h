#pragma once

class CGameObj;

class CRender
{
protected:
	CGameObj* m_pGameObj;

	D3DXMATRIX m_matWorld;

protected:
	void MakeRot( D3DXMATRIX& matRot );
	void MakeTrans( D3DXMATRIX& matTrans );
	void MakeScale( D3DXMATRIX& matScale );

	void MakeAlpha( DWORD* pDark, DWORD* pView, D3DXVECTOR2 vPos, const STextureInfo* pDarkInfo, const STextureInfo* pViewInfo );

public:
	CRender( CGameObj* m_pGameObj );
	virtual ~CRender(void);

	virtual void Load( wstring wFile ) {}
	virtual bool OnFrameMove( float fElapsedTime ) { return true; }
	virtual void OnFrameRender() {}

	virtual void SetDarkMode( D3DXVECTOR2 vPos, int iTexture ) {}
	virtual void UpdateWorld() {}

	const D3DXMATRIX & GetWorld() { return m_matWorld; }
};