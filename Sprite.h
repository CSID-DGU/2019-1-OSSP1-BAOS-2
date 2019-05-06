#pragma once

class CSprite
{
private:
	LPD3DXSPRITE m_pSprite;

public:
	CSprite(void);
	virtual ~CSprite(void);

	LPD3DXSPRITE GetSprite() { return m_pSprite; }

	void OnResetDevice();
	void OnLostDevice();

	void OnBegin();
	void OnEnd();

	void SetTransform( D3DXMATRIX *pmatTrans );
	void OnDraw( LPDIRECT3DTEXTURE9 pTexture
		, const RECT* pRect
		, float fX
		, float fY );
};

