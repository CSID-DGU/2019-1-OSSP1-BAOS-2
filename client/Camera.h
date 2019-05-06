#pragma once

class CICameraObj
{
public:
	CICameraObj() {}
	virtual ~CICameraObj() {}

	virtual const D3DXVECTOR2* GetPos() = 0;
};

class CCamera
{
private:
	CICameraObj* m_pObj;

	int m_iWidth;
	int m_iHeight;

	D3DXVECTOR2  m_vPos;
	bool m_bUse;

public:
	bool IsUse() { return m_bUse; }
	void SetUse( bool bUse ) { m_bUse = bUse; }

	int GetWidth() { return m_iWidth; }
	int GetHeight() { return m_iHeight; }

	D3DXVECTOR2 GetCameraPos(){ return m_vPos; }

public:
	CCamera(void);
	virtual ~CCamera(void);

	void InitSize( int iWidth, int iHeight );
	void OnFrameMove( float fElapsedTime );
	void OnUpdateScreen( float fElapsedTime );
	void SetCameraObj( CICameraObj* pObj ) { m_pObj = pObj; }
	void GetTransform( D3DXMATRIX * pmatTrans );
};

